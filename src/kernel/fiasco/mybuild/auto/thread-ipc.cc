// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "thread.h"
#include "thread_i.h"

#line 94 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"

// IPC setup, and handling of ``short IPC'' and page-fault IPC

// IDEAS for enhancing this implementation: 

// Volkmar has suggested a possible optimization for
// short-flexpage-to-long-message-buffer transfers: Currently, we have
// to resort to long IPC in that case because the message buffer might
// contain a receive-flexpage option.  An easy optimization would be
// to cache the receive-flexpage option in the TCB for that case.
// This would save us the long-IPC setup because we wouldn't have to
// touch the receiver's user memory in that case.  Volkmar argues that
// cases like that are quite common -- for example, imagine a pager
// which at the same time is also a server for ``normal'' requests.

// The handling of cancel and timeout conditions could be improved as
// follows: Cancel and Timeout should not reset the ipc_in_progress
// flag.  Instead, they should just set and/or reset a flag of their
// own that is checked every time an (IPC) system call wants to go to
// sleep.  That would mean that IPCs that do not block are not
// cancelled or aborted.
//-
#line 1224 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"

//---------------------------------------------------------------------------


#line 1120 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"


inline bool
Thread::remote_ipc_send(Ipc_remote_request *rq)
{

#if 0
  LOG_MSG_3VAL(this, "rsend", (Mword)src, 0, 0);
  printf("CPU[%u]: remote IPC send ...\n"
         "  partner=%p [%u]\n"
         "  sender =%p [%u] regs=%p\n"
         "  timeout=%u\n",
         current_cpu(),
         rq->partner, rq->partner->cpu(),
         src, src->cpu(),
         rq->regs,
         rq->timeout);
#endif

  switch (expect(rq->partner->check_sender(this, rq->timeout), Check_sender::Ok))
    {
    case Check_sender::Failed:
      xcpu_state_change(~Thread_ipc_mask, 0);
      rq->result = Check_sender::Failed;
      return false;
    case Check_sender::Queued:
      rq->result = Check_sender::Queued;
      return false;
    default:
      break;
    }

  if ((rq->tag.transfer_fpu() && rq->partner->_utcb_handler)
      || rq->partner->utcb().access()->inherit_fpu())
    rq->partner->spill_fpu_if_owner();

  // trigger remote_ipc_receiver_ready path, because we may need to grab locks
  // and this is forbidden in a DRQ handler. So transfer the IPC in usual
  // thread code. However, this induces a overhead of two extra IPIs.
  if (rq->tag.items())
    {
      //LOG_MSG_3VAL(rq->partner, "pull", dbg_id(), 0, 0);
      xcpu_state_change(~Thread_send_wait, Thread_ready);
      rq->partner->state_change_dirty(~(Thread_ipc_mask | Thread_ready), Thread_ipc_transfer);
      rq->result = Check_sender::Ok;
      return true;
    }
  bool success = transfer_msg(rq->tag, rq->partner, rq->regs, _ipc_send_rights);
  if (success && rq->have_rcv)
    xcpu_state_change(~Thread_send_wait, Thread_receive_wait);
  else
    xcpu_state_change(~Thread_ipc_mask, 0);

  rq->result = success ? Check_sender::Done : Check_sender::Failed;
  rq->partner->state_change_dirty(~Thread_ipc_mask, Thread_ready);
  if (rq->partner->home_cpu() == current_cpu() && current() != rq->partner)
    Sched_context::rq.current().ready_enqueue(rq->partner->sched());

  return true;
}

#line 131 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"


void
Thread::ipc_receiver_aborted() 
{
  assert (cpu_lock.test());
  assert (wait_queue());
  set_wait_queue(0);

  if (xcpu_state_change(~0UL, Thread_canceled | Thread_ready, true))
    current()->switch_to_locked(this);
}

#line 143 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"


void
Thread::ipc_send_msg(Receiver *recv) 
{
  Syscall_frame *regs = _snd_regs;
  bool success = transfer_msg(regs->tag(), nonull_static_cast<Thread*>(recv), regs,
                              _ipc_send_rights);
  sender_dequeue(recv->sender_list());
  recv->vcpu_update_state();
  //printf("  done\n");
  regs->tag(L4_msg_tag(regs->tag(), success ? 0 : L4_msg_tag::Error));

  Mword state_del = Thread_ipc_mask | Thread_ipc_transfer;
  Mword state_add = Thread_ready;
  if (Receiver::prepared())
    // same as in Receiver::prepare_receive_dirty_2
    state_add |= Thread_receive_wait;

  if (xcpu_state_change(~state_del, state_add, true))
    recv->switch_to_locked(this);
}

#line 165 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"


void
Thread::modify_label(Mword const *todo, int cnt) 
{
  assert (_snd_regs);
  Mword l = _snd_regs->from_spec();
  for (int i = 0; i < cnt*4; i += 4)
    {
      Mword const test_mask = todo[i];
      Mword const test      = todo[i+1];
      if ((l & test_mask) == test)
        {
          Mword const del_mask = todo[i+2];
          Mword const add_mask = todo[i+3];

          l = (l & ~del_mask) | add_mask;
          _snd_regs->from(l);
          return;
        }
    }
}

#line 192 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"


/** Page fault handler.
    This handler suspends any ongoing IPC, then sets up page-fault IPC.
    Finally, the ongoing IPC's state (if any) is restored.
    @param pfa page-fault virtual address
    @param error_code page-fault error code.
 */

bool
Thread::handle_page_fault_pager(Thread_ptr const &_pager,
                                Address pfa, Mword error_code,
                                L4_msg_tag::Protocol protocol)
{
  if (EXPECT_FALSE((state() & Thread_alien)))
    return false;

  auto guard = lock_guard(cpu_lock);

  L4_fpage::Rights rights;
  Kobject_iface *pager = _pager.ptr(space(), &rights);

  if (!pager)
    {
      WARN("CPU%u: Pager of %lx is invalid (pfa=" L4_PTR_FMT
           ", errorcode=" L4_PTR_FMT ") to %lx (pc=%lx)\n",
           cxx::int_value<Cpu_number>(current_cpu()), dbg_id(), pfa,
           error_code, cxx::int_value<Cap_index>(_pager.raw()), regs()->ip());


      LOG_TRACE("Page fault invalid pager", "ipfh", this, Log_pf_invalid,
                l->cap_idx = _pager.raw();
                l->err     = error_code;
                l->pfa     = pfa);

      halt();
      return true;
    }

  // set up a register block used as an IPC parameter block for the
  // page fault IPC
  Syscall_frame r;

  // save the UTCB fields affected by PF IPC
  Mword vcpu_irqs = vcpu_disable_irqs();
  Mem::barrier();
  Utcb *utcb = this->utcb().access(true);
  Pf_msg_utcb_saver saved_utcb_fields(utcb);


  utcb->buf_desc = L4_buf_desc(0, 0, 0, L4_buf_desc::Inherit_fpu);
  utcb->buffers[0] = L4_msg_item::map(0).raw();
  utcb->buffers[1] = L4_fpage::all_spaces().raw();

  utcb->values[0] = PF::addr_to_msgword0(pfa, error_code);
  utcb->values[1] = regs()->ip(); //PF::pc_to_msgword1 (regs()->ip(), error_code));

  L4_timeout_pair timeout(L4_timeout::Never, L4_timeout::Never);

  L4_msg_tag tag(2, 0, 0, protocol);

  r.timeout(timeout);
  r.tag(tag);
  r.from(0);
  r.ref(L4_obj_ref(_pager.raw(), L4_obj_ref::Ipc_call_ipc));
  pager->invoke(r.ref(), rights, &r, utcb);


  bool success = true;

  if (EXPECT_FALSE(r.tag().has_error()))
    {
      if (utcb->error.snd_phase()
          && (utcb->error.error() == L4_error::Not_existent)
          && PF::is_usermode_error(error_code)
          && !(state() & Thread_cancel))
        {
          success = false;
        }
    }
  else // no error
    {
      // If the pager rejects the mapping, it replies -1 in msg.w0
      if (EXPECT_FALSE (utcb->values[0] == Mword(-1)))
        success = false;
    }

  // restore previous IPC state

  saved_utcb_fields.restore(utcb);
  Mem::barrier();
  vcpu_restore_irqs(vcpu_irqs);
  return success;
}

#line 449 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"

/**
 * Send an IPC message.
 *        Block until we can send the message or the timeout hits.
 * @param partner the receiver of our message
 * @param t a timeout specifier
 * @param regs sender's IPC registers
 * @pre cpu_lock must be held
 * @return sender's IPC error code
 *
 * @todo review closed wait handling of sender during possible
 *       quiescent states and blocking.
 */

void
Thread::do_ipc(L4_msg_tag const &tag, bool have_send, Thread *partner,
               bool have_receive, Sender *sender,
               L4_timeout_pair t, Syscall_frame *regs,
               L4_fpage::Rights rights)
{
  assert (cpu_lock.test());
  assert (this == current());

  bool do_switch = false;

  assert (!(state() & Thread_ipc_mask));

  prepare_receive(sender, have_receive ? regs : 0);
  bool activate_partner = false;
  Cpu_number current_cpu = ::current_cpu();

  if (have_send)
    {
      assert(!in_sender_list());
      do_switch = tag.do_switch();

      bool ok;
      Check_sender result;

      set_ipc_send_rights(rights);

      if (EXPECT_TRUE(current_cpu == partner->home_cpu()))
        result = handshake_receiver(partner, t.snd);
      else
        {
          // we have either per se X-CPU IPC or we ran into a
          // IPC during migration (indicated by the pending DRQ)
          do_switch = false;
          result = remote_handshake_receiver(tag, partner, have_receive, t.snd,
                                             regs, rights);

          // this may block, so we could have been migrated here
          current_cpu = ::current_cpu();
        }

      switch (expect(result, Check_sender::Ok))
        {
        case Check_sender::Done:
          ok = true;
          break;

        case Check_sender::Queued:
          // set _snd_regs, to enable active receiving
          snd_regs(regs);
          ok = do_send_wait(partner, t.snd); // --- blocking point ---
          current_cpu = ::current_cpu();
          break;

        case Check_sender::Failed:
          state_del_dirty(Thread_ipc_mask);
          ok = false;
          break;

        default:
          // mmh, we can reset the receivers timeout
          // ping pong with timeouts will profit from it, because
          // it will require much less sorting overhead
          // if we dont reset the timeout, the possibility is very high
          // that the receiver timeout is in the timeout queue
          if (EXPECT_TRUE(current_cpu == partner->home_cpu()))
            partner->reset_timeout();

          ok = transfer_msg(tag, partner, regs, rights);

          // transfer is also a possible migration point
          current_cpu = ::current_cpu();

          // switch to receiving state
          state_del_dirty(Thread_ipc_mask);
          if (ok && have_receive)
            state_add_dirty(Thread_receive_wait);

          activate_partner = partner != this;
          break;
        }

      if (EXPECT_FALSE(!ok))
        {
          // send failed, so do not switch to receiver directly and skip receive phase
          regs->tag(L4_msg_tag(0, 0, L4_msg_tag::Error, 0));
        }
    }
  else
    {
      assert (have_receive);
      state_add_dirty(Thread_receive_wait);
    }

  // only do direct switch on closed wait (call) or if we run on a foreign
  // scheduling context
  Sender *next = 0;

  have_receive = state() & Thread_receive_wait;

  if (have_receive)
    {
      assert (!in_sender_list());
      assert (!(state() & Thread_send_wait));
      next = get_next_sender(sender);
    }

  if (activate_partner
      && activate_ipc_partner(partner, current_cpu, do_switch && !next,
                              have_receive && sender))
    {
      // blocked so might have a new sender queued
      have_receive = state() & Thread_receive_wait;
      if (have_receive && !next)
        next = get_next_sender(sender);
    }

  if (next)
    {
      state_change_dirty(~Thread_ipc_mask, Thread_receive_in_progress);
      next->ipc_send_msg(this);
      state_del_dirty(Thread_ipc_mask);
    }
  else if (have_receive)
    {
      if ((state() & Thread_full_ipc_mask) == Thread_receive_wait)
        goto_sleep(t.rcv, sender, utcb().access(true));

      if (sender && sender == partner && partner->caller() == this)
        partner->reset_caller();
    }

  Mword state = this->state();

  if (EXPECT_TRUE (!(state & Thread_full_ipc_mask)))
    return;

  while (EXPECT_FALSE(state & Thread_ipc_transfer))
    {
      state_del_dirty(Thread_ready);
      schedule();
      state = this->state();
   }

  if (EXPECT_TRUE (!(state & Thread_full_ipc_mask)))
    return;

  if (state & Thread_ipc_mask)
    {
      Utcb *utcb = this->utcb().access(true);
      // the IPC has not been finished.  could be timeout or cancel
      // XXX should only modify the error-code part of the status code

      if (EXPECT_FALSE(state & Thread_cancel))
        {
          // we've presumably been reset!
          regs->tag(commit_error(utcb, L4_error::R_canceled, regs->tag()));
        }
      else
        regs->tag(commit_error(utcb, L4_error::R_timeout, regs->tag()));
    }
  state_del(Thread_full_ipc_mask);
}

#line 681 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"


/**
 * \pre must run with local IRQs disabled (CPU lock held)
 * to ensure that handler does not dissapear meanwhile.
 */

bool
Thread::exception(Kobject_iface *handler, Trap_state *ts, L4_fpage::Rights rights)
{
  Syscall_frame r;
  L4_timeout_pair timeout(L4_timeout::Never, L4_timeout::Never);

  CNT_EXC_IPC;

  Mword vcpu_irqs = vcpu_disable_irqs();
  Mem::barrier();

  void *old_utcb_handler = _utcb_handler;
  _utcb_handler = ts;

  // fill registers for IPC
  Utcb *utcb = this->utcb().access(true);
  Buf_utcb_saver saved_state(utcb);

  utcb->buf_desc = L4_buf_desc(0, 0, 0, L4_buf_desc::Inherit_fpu);
  utcb->buffers[0] = L4_msg_item::map(0).raw();
  utcb->buffers[1] = L4_fpage::all_spaces().raw();

  // clear regs
  L4_msg_tag tag(L4_exception_ipc::Msg_size, 0, L4_msg_tag::Transfer_fpu,
                 L4_msg_tag::Label_exception);

  r.tag(tag);
  r.timeout(timeout);
  r.from(0);
  r.ref(L4_obj_ref(_exc_handler.raw(), L4_obj_ref::Ipc_call_ipc));
  spill_user_state();
  handler->invoke(r.ref(), rights, &r, utcb);
  fill_user_state();

  saved_state.restore(utcb);

  state_del(Thread_in_exception);
  if (!r.tag().has_error()
      && r.tag().proto() == L4_msg_tag::Label_allow_syscall)
    state_add(Thread_dis_alien);

  // restore original utcb_handler
  _utcb_handler = old_utcb_handler;
  Mem::barrier();
  vcpu_restore_irqs(vcpu_irqs);

  // FIXME: handle not existing pager properly
  // for now, just ignore any errors
  return 1;
}

#line 818 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"


bool
Thread::try_transfer_local_id(L4_buf_iter::Item const *const buf,
                              L4_fpage sfp, Mword *rcv_word, Thread* snd,
                              Thread *rcv)
{
  if (buf->b.is_rcv_id())
    {
      if (snd->space() == rcv->space())
        {
          rcv_word[-2] |= 6;
          rcv_word[-1] = sfp.raw();
          return true;
        }
      else
        {
          Obj_space::Capability cap = snd->space()->lookup(sfp.obj_index());
          Kobject_iface *o = cap.obj();
          if (EXPECT_TRUE(o && o->is_local(rcv->space())))
            {
              Mword rights = cap.rights()
                             & cxx::int_value<L4_fpage::Rights>(sfp.rights());
              rcv_word[-2] |= 4;
              rcv_word[-1] = o->obj_id() | rights;
              return true;
            }
        }
    }
  return false;
}

#line 893 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"


bool
Thread::transfer_msg_items(L4_msg_tag const &tag, Thread* snd, Utcb *snd_utcb,
                           Thread *rcv, Utcb *rcv_utcb,
                           L4_fpage::Rights rights)
{
  // LOG_MSG_3VAL(current(), "map bd=", rcv_utcb->buf_desc.raw(), 0, 0);
  Ref_ptr<Task> rcv_t(nonull_static_cast<Task*>(rcv->space()));
  L4_buf_iter mem_buffer(rcv_utcb, rcv_utcb->buf_desc.mem());
  L4_buf_iter io_buffer(rcv_utcb, rcv_utcb->buf_desc.io());
  L4_buf_iter obj_buffer(rcv_utcb, rcv_utcb->buf_desc.obj());
  L4_snd_item_iter snd_item(snd_utcb, tag.words());
  int items = tag.items();
  Mword *rcv_word = rcv_utcb->values + tag.words();

  // XXX: damn X-CPU state modification
  // snd->prepare_long_ipc(rcv);
  Reap_list rl;

  for (;items > 0 && snd_item.more();)
    {
      if (EXPECT_FALSE(!snd_item.next()))
        {
          snd->set_ipc_error(L4_error::Overflow, rcv);
          return false;
        }

      L4_snd_item_iter::Item const *const item = snd_item.get();

      if (item->b.is_void())
        { // XXX: not sure if void fpages are needed
          // skip send item and current rcv_buffer
          --items;
          *rcv_word = 0;
          rcv_word += 2;
          continue;
        }

      L4_buf_iter *buf_iter = 0;

      switch (item->b.type())
        {
        case L4_msg_item::Map:
          switch (L4_fpage(item->d).type())
            {
            case L4_fpage::Memory: buf_iter = &mem_buffer; break;
            case L4_fpage::Io:     buf_iter = &io_buffer; break;
            case L4_fpage::Obj:    buf_iter = &obj_buffer; break;
            default: break;
            }
          break;
        default:
          break;
        }

      if (EXPECT_FALSE(!buf_iter))
        {
          // LOG_MSG_3VAL(snd, "lIPCm0", 0, 0, 0);
          snd->set_ipc_error(L4_error::Overflow, rcv);
          return false;
        }

      L4_buf_iter::Item const *const buf = buf_iter->get();

      if (EXPECT_FALSE(buf->b.is_void() || buf->b.type() != item->b.type()))
        {
          // LOG_MSG_3VAL(snd, "lIPCm1", buf->b.raw(), item->b.raw(), 0);
          snd->set_ipc_error(L4_error::Overflow, rcv);
          return false;
        }

        {
          assert (item->b.type() == L4_msg_item::Map);
          L4_fpage sfp(item->d);
          *rcv_word = (item->b.raw() & ~0x0ff6) | (sfp.raw() & 0x0ff0);

          rcv_word += 2;

          // diminish when sending via restricted ipc gates
          if (sfp.type() == L4_fpage::Obj)
            sfp.mask_rights(rights | L4_fpage::Rights::CRW() | L4_fpage::Rights::CD());

          if (!try_transfer_local_id(buf, sfp, rcv_word, snd, rcv))
            {
              // we need to do a real mapping
              L4_error err;

                {
                  // We take the existence_lock for syncronizing maps...
                  // This is kind of coarse grained
                  auto sp_lock = lock_guard_dont_lock(rcv_t->existence_lock);
                  if (!sp_lock.check_and_lock(&rcv_t->existence_lock))
                    {
                      snd->set_ipc_error(L4_error::Overflow, rcv);
                      return false;
                    }

                  auto c_lock = lock_guard<Lock_guard_inverse_policy>(cpu_lock);
                  err = fpage_map(snd->space(), sfp,
                                  rcv_t.get(), L4_fpage(buf->d), item->b, &rl);
                }

              if (EXPECT_FALSE(!err.ok()))
                {
                  snd->set_ipc_error(err, rcv);
                  return false;
                }
            }
        }

      --items;

      if (!item->b.compound())
        buf_iter->next();
    }

  if (EXPECT_FALSE(items))
    {
      snd->set_ipc_error(L4_error::Overflow, rcv);
      return false;
    }

  return true;
}

#line 1180 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"


Context::Drq::Result
Thread::handle_remote_ipc_send(Drq *src, Context *, void *_rq)
{
  Ipc_remote_request *rq = (Ipc_remote_request*)_rq;
  bool r = nonull_static_cast<Thread*>(src->context())->remote_ipc_send(rq);
  //LOG_MSG_3VAL(src, "rse<", current_cpu(), (Mword)src, r);
  return r ? Drq::need_resched() : Drq::done();
}

#line 1190 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"

/**
 * \pre Runs on the sender CPU
 */
//inline NEEDS ["mp_request.h"]
Thread::Check_sender
Thread::remote_handshake_receiver(L4_msg_tag const &tag, Thread *partner,
                                  bool have_receive,
                                  L4_timeout snd_t, Syscall_frame *regs,
                                  L4_fpage::Rights rights)
{
  // Flag that there must be no switch in the receive path.
  // This flag also prevents the receive path from accessing
  // the thread state of a remote sender.
  Ipc_remote_request rq;
  rq.tag = tag;
  rq.have_rcv = have_receive;
  rq.partner = partner;
  rq.timeout = !snd_t.is_zero();
  rq.regs = regs;
  rq.rights = rights;
  _snd_regs = regs;

  set_wait_queue(partner->sender_list());

  state_add_dirty(Thread_send_wait);

  if (tag.transfer_fpu())
    spill_fpu_if_owner();

  partner->drq(handle_remote_ipc_send, &rq);

  return rq.result;
}

#line 1229 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"


void
Thread::Log_pf_invalid::print(String_buffer *buf) const
{
  buf->printf("InvCap C:%lx pfa=%lx err=%lx",
              cxx::int_value<Cap_index>(cap_idx), pfa, err);
}

#line 1237 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"


void
Thread::Log_exc_invalid::print(String_buffer *buf) const
{
  buf->printf("InvCap C:%lx", cxx::int_value<Cap_index>(cap_idx));
}
