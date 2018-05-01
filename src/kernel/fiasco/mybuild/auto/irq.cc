// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "irq.h"
#include "irq_i.h"

#line 123 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"

JDB_DEFINE_TYPENAME(Irq_sender, "\033[37mIRQ ipc\033[m");
#line 125 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
JDB_DEFINE_TYPENAME(Irq_muxer,  "\033[37mIRQ mux\033[m");
#line 126 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"

namespace {
static Irq_base *irq_base_dcast(Kobject_iface *o)
{ return cxx::dyn_cast<Irq*>(o); }

struct Irq_base_cast
{
  Irq_base_cast()
  { Irq_base::dcast = &irq_base_dcast; }
};

static Irq_base_cast register_irq_base_cast;
}
#line 781 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"



 // Irq implementation

static Kmem_slab _irq_allocator(max(sizeof (Irq_sender), sizeof(Irq_muxer)),
                                __alignof__ (Irq), "Irq");
#line 833 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"

namespace {
static Kobject_iface * FIASCO_FLATTEN
irq_sender_factory(Ram_quota *q, Space *,
                   L4_msg_tag, Utcb const *,
                   int *err)
{
  *err = L4_err::ENomem;
  return Irq::allocate<Irq_sender>(q);
}

static Kobject_iface * FIASCO_FLATTEN
irq_mux_factory(Ram_quota *q, Space *,
                L4_msg_tag, Utcb const *,
                int *err)
{
  *err = L4_err::ENomem;
  return Irq::allocate<Irq_muxer>(q);
}

static inline void __attribute__((constructor)) FIASCO_INIT
register_factory()
{
  Kobject_iface::set_factory(L4_msg_tag::Label_irq_sender, irq_sender_factory);
  Kobject_iface::set_factory(L4_msg_tag::Label_irq_mux, irq_mux_factory);
}
}

#line 173 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


void
Irq_muxer::unmask(Mword)
{
  Smword old;
  do
    old = _mask_cnt;
  while (!mp_cas(&_mask_cnt, old, old - 1));

  if (old == 1)
    Irq_base::unmask();
}

#line 186 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"



void
Irq_muxer::mask(Mword)
{
  Smword old;
  do
    old = _mask_cnt;
  while (!mp_cas(&_mask_cnt, old, old + 1));

  if (old == 0)
    Irq_base::mask();
}

#line 200 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"



void
Irq_muxer::unbind(Irq_base *irq)
{
  Irq_base *n;
    {
      auto g = lock_guard(_mux_lock);
      for (n = this; n->_next && n->_next != irq; n = n->_next)
        ;

      if (n->_next != irq)
        return; // someone else was faster

      // dequeue
      n->_next = n->_next->_next;
    }

  if (irq->masked())
    static_cast<Irq_chip&>(*this).unmask(0);

  Irq_chip::unbind(irq);
}

#line 224 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"



void
Irq_muxer::mask_and_ack(Mword)
{}

#line 264 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


Irq_muxer::Irq_muxer(Ram_quota *q)
: Kobject_h<Irq_muxer, Irq>(q), _mask_cnt(0),
  _mux_lock(Spin_lock<>::Unlocked)
{
  hit_func = &handler_wrapper<Irq_muxer>;
}

#line 272 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


void
Irq_muxer::destroy(Kobject ***rl)
{
  while (Irq_base *n = Irq_base::_next)
    {
      auto g  = lock_guard(n->irq_lock());
      if (n->chip() == this)
        unbind(n);
    }

  Irq::destroy(rl);
}

#line 286 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


L4_msg_tag
Irq_muxer::sys_attach(L4_msg_tag tag, Utcb const *utcb, Syscall_frame *)
{
  Ko::Rights rights;
  Irq *irq = Ko::deref<Irq>(&tag, utcb, &rights);
  if (!irq)
    return tag;

  auto g = lock_guard(irq->irq_lock());
  irq->unbind();

  if (!irq->masked())
    {
      Smword old;
      do
        old = _mask_cnt;
      while (!mp_cas(&_mask_cnt, old, old + 1));
    }

  Mem::mp_acquire();
  bind(irq, 0);

  auto mg = lock_guard(_mux_lock);
  irq->Irq_base::_next = Irq_base::_next;
  Irq_base::_next = irq;

  return commit_result(0);
}

#line 316 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


L4_msg_tag
Irq_muxer::kinvoke(L4_obj_ref, L4_fpage::Rights /*rights*/, Syscall_frame *f,
                   Utcb const *utcb, Utcb *)
{
  L4_msg_tag tag = f->tag();
  int op = get_irq_opcode(tag, utcb);

  if (EXPECT_FALSE(op < 0))
    return commit_result(-L4_err::EInval);

  switch (tag.proto())
    {
    case L4_msg_tag::Label_irq:
      return dispatch_irq_proto(op, false);

    case L4_msg_tag::Label_irq_mux:
      switch (op)
        {
        case Op_chain:
          return sys_attach(tag, utcb, f);

        default:
          return commit_result(-L4_err::ENosys);
        }

    default:
      return commit_result(-L4_err::EBadproto);
    }
}

#line 420 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


Receiver *
Irq_sender::owner() const { return _irq_thread; }

#line 424 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"

/**
 * Release an interrupt.
 * \param rl[in,out]  The list of objects that have to be destroyed.
 *                    The operation might append objects to this list if it is
 *                    in charge of deleting the receiver that used to be
 *                    attached to this IRQ.
 *
 * \retval 0        on success.
 * \retval -ENOENT  if there was no receiver attached.
 * \retval -EBUSY   when there is another detach operation in progress.
 */

int
Irq_sender::free(Kobject ***rl)
{
  Mem::mp_release();
  Thread *t;
  for (;;)
    {
      t = access_once(&_irq_thread);

      if (t == detach_in_progress())
        return -L4_err::EBusy;

      if (t == nullptr)
        return -L4_err::ENoent;

      if (EXPECT_TRUE(mp_cas(&_irq_thread, t, detach_in_progress())))
        break;
    }

  auto guard = lock_guard(cpu_lock);
  mask();

  t->Receiver::abort_send(this);

  Mem::mp_release();
  write_now(&_irq_thread, nullptr);
  // release cpu-lock early, actually before delete
  guard.reset();

  t->put_n_reap(rl);
  return 0;
}

#line 469 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


Irq_sender::Irq_sender(Ram_quota *q)
: Kobject_h<Irq_sender, Irq>(q), _queued(0), _irq_thread(0), _irq_id(~0UL)
{
  hit_func = &hit_level_irq;
}

#line 476 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


void
Irq_sender::switch_mode(bool is_edge_triggered)
{
  hit_func = is_edge_triggered ? &hit_edge_irq : &hit_level_irq;
}

#line 483 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


void
Irq_sender::destroy(Kobject ***rl)
{
  auto g = lock_guard(cpu_lock);
  (void)free(rl);
  Irq::destroy(rl);
}

#line 556 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"

void
Irq_sender::modify_label(Mword const *todo, int cnt)
{
  for (int i = 0; i < cnt*4; i += 4)
    {
      Mword const test_mask = todo[i];
      Mword const test      = todo[i+1];
      if ((_irq_id & test_mask) == test)
	{
	  Mword const set_mask = todo[i+2];
	  Mword const set      = todo[i+3];

	  _irq_id = (_irq_id & ~set_mask) | set;
	  return;
	}
    }
}

#line 574 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"



Context::Drq::Result
Irq_sender::handle_remote_hit(Context::Drq *, Context *target, void *arg)
{
  Irq_sender *irq = (Irq_sender*)arg;
  irq->set_cpu(current_cpu());
  auto t = access_once(&irq->_irq_thread);
  if (EXPECT_TRUE(t == target))
    {
      if (EXPECT_TRUE(irq->send_msg(t, false)))
        return Context::Drq::no_answer_resched();
    }
  else
    t->drq(&irq->_drq, handle_remote_hit, irq,
           Context::Drq::Target_ctxt, Context::Drq::No_wait);

  return Context::Drq::no_answer();
}

#line 642 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


void
Irq_sender::hit_level_irq(Irq_base *i, Upstream_irq const *ui)
{ nonull_static_cast<Irq_sender*>(i)->_hit_level_irq(ui); }

#line 676 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


void
Irq_sender::hit_edge_irq(Irq_base *i, Upstream_irq const *ui)
{ nonull_static_cast<Irq_sender*>(i)->_hit_edge_irq(ui); }

#line 681 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"



L4_msg_tag
Irq_sender::sys_attach(L4_msg_tag tag, Utcb const *utcb,
                       Syscall_frame *)
{
  Thread *thread;

  if (tag.items())
    {
      Ko::Rights rights;
      thread = Ko::deref<Thread>(&tag, utcb, &rights);
      if (!thread)
        return tag;

      if (EXPECT_FALSE(!(rights & L4_fpage::Rights::CS())))
        return commit_result(-L4_err::EPerm);
    }
  else
    thread = current_thread();

  Reap_list rl;
  int res = alloc(thread, rl.list());

  // note: this is a possible race on user-land
  // where the label of an IRQ might become inconsistent with the attached
  // thread. The user is responsible to synchronize Irq::attach calls to prevent
  // this.
  if (res == 0)
    _irq_id = access_once(&utcb->values[1]);

  cpu_lock.clear();
  rl.del();
  cpu_lock.lock();

  return commit_result(res);
}

#line 719 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


L4_msg_tag
Irq_sender::sys_detach()
{
  Reap_list rl;
  auto res = free(rl.list());
  _irq_id = ~0UL;
  cpu_lock.clear();
  rl.del();
  cpu_lock.lock();
  return commit_result(res);
}

#line 732 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"



L4_msg_tag
Irq_sender::kinvoke(L4_obj_ref, L4_fpage::Rights /*rights*/, Syscall_frame *f,
                    Utcb const *utcb, Utcb *)
{
  L4_msg_tag tag = f->tag();
  int op = get_irq_opcode(tag, utcb);

  if (EXPECT_FALSE(op < 0))
    return commit_result(-L4_err::EInval);

  switch (tag.proto())
    {
    case L4_msg_tag::Label_kobject:
      switch (op)
        {
        case Op_bind: // the Rcv_endpoint opcode (equal to Ipc_gate::bind_thread
          return sys_attach(tag, utcb, f);
        default:
          return commit_result(-L4_err::ENosys);
        }

    case L4_msg_tag::Label_irq:
      return dispatch_irq_proto(op, _queued < 1);

    case L4_msg_tag::Label_irq_sender:
      switch (op)
        {
        case Op_attach:
          WARN("Irq_sender::attach is deprecated, please use Rcv_endpoint::bind_thread.\n");
          return sys_attach(tag, utcb, f);

        case Op_detach:
          return sys_detach();

        default:
          return commit_result(-L4_err::ENosys);
        }
    default:
      return commit_result(-L4_err::EBadproto);
    }
}

#line 776 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


Mword
Irq_sender::obj_id() const
{ return _irq_id; }

#line 788 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


Irq::Allocator *
Irq::allocator()
{ return &_irq_allocator; }

#line 798 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


void
Irq::operator delete (void *_l)
{
  Irq *l = reinterpret_cast<Irq*>(_l);
  if (l->_q)
    allocator()->q_free(l->_q, l);
  else
    allocator()->free(l);
}

#line 825 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


void
Irq::destroy(Kobject ***rl)
{
  Irq_base::destroy();
  Kobject::destroy(rl);
}
