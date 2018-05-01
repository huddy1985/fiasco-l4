// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "thread.h"
#include "thread_i.h"

#line 182 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"

JDB_DEFINE_TYPENAME(Thread,  "\033[32mThread\033[m");
#line 184 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
DEFINE_PER_CPU Per_cpu<unsigned long> Thread::nested_trap_recover;
#line 316 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"

Del_irq_chip Del_irq_chip::chip;
#line 784 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"

//---------------------------------------------------------------------------

#line 1008 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"

//----------------------------------------------------------------------------


#line 997 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


inline void
Thread::force_to_invalid_cpu()
{
  // make sure this thread really never runs again by migrating it
  // to the 'invalid' CPU forcefully and then switching to the kernel
  // thread for doing the last bits.
  set_home_cpu(Cpu::invalid());
  handle_drq();
}

#line 185 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


Thread::Dbg_stack::Dbg_stack()
{
  stack_top = Kmem_alloc::allocator()->unaligned_alloc(Stack_size); 
  if (stack_top)
    stack_top = (char *)stack_top + Stack_size;
  //printf("JDB STACK start= %p - %p\n", (char *)stack_top - Stack_size, (char *)stack_top);
}

#line 206 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


bool
Thread::bind(Task *t, User<Utcb>::Ptr utcb)
{
  // _utcb == 0 for all kernel threads
  Space::Ku_mem const *u = t->find_ku_mem(utcb, sizeof(Utcb));

  // kernel thread?
  if (EXPECT_FALSE(utcb && !u))
    return false;

  auto guard = lock_guard(_space.lock());
  if (_space.space() != Kernel_task::kernel_task())
    return false;

  _space.space(t);
  t->inc_ref();

  if (u)
    {
      _utcb.set(utcb, u->kern_addr(utcb));
      arch_setup_utcb_ptr();
    }

  return true;
}

#line 284 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


/** Destructor.  Reestablish the Context constructor's precondition.
    @pre current() == thread_lock()->lock_owner()
         && state() == Thread_dead
    @pre lock_cnt() == 0
    @post (_kernel_sp == 0)  &&  (* (stack end) == 0)  &&  !exists()
 */

Thread::~Thread()		// To be called in locked state.
{

  unsigned long *init_sp = reinterpret_cast<unsigned long*>
    (reinterpret_cast<unsigned long>(this) + Size - sizeof(Entry_frame));

  _kernel_sp = 0;
  *--init_sp = 0;
  Fpu_alloc::free_state(fpu_state());
}

#line 342 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


void
Thread::register_delete_irq(Irq_base *irq)
{
  irq->unbind();
  Del_irq_chip::chip.bind(irq, (Mword)this);
  _del_observer = irq;
}

#line 351 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


void
Thread::remove_delete_irq()
{
  if (!_del_observer)
    return;

  Irq_base *tmp = _del_observer;
  _del_observer = 0;
  tmp->unbind();
}

#line 412 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"



void
Thread::halt()
{
  // Cancel must be cleared on all kernel entry paths. See slowtraps for
  // why we delay doing it until here.
  state_del(Thread_cancel);

  // we haven't been re-initialized (cancel was not set) -- so sleep
  if (state_change_safely(~Thread_ready, Thread_cancel | Thread_dead))
    while (! (state() & Thread_ready))
      schedule();
}

#line 427 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


void
Thread::halt_current()
{
  for (;;)
    {
      current_thread()->halt();
      kdb_ke("Thread not halted");
    }
}

#line 454 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


void
Thread::leave_and_kill_myself()
{
  current_thread()->do_kill();
#ifdef CONFIG_JDB
  WARN("dead thread scheduled: %lx\n", current_thread()->dbg_id());
#endif
  kdb_ke("DEAD SCHED");
}

#line 465 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


Context::Drq::Result
Thread::handle_kill_helper(Drq *src, Context *, void *)
{
  Thread *to_delete = static_cast<Thread*>(static_cast<Kernel_drq*>(src)->src);
  assert (!to_delete->in_ready_list());
  if (to_delete->dec_ref() == 0)
    delete to_delete;

  return Drq::no_answer_resched();
}

#line 477 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


void
Thread::put_n_reap(Kobject ***reap_list)
{
  if (dec_ref() == 0)
    {
      // we need to re-add the reference
      // that is released during Reap_list::del
      inc_ref();
      initiate_deletion(reap_list);
    }
}

#line 490 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"



bool
Thread::do_kill()
{
  if (is_invalid())
    return false;

  //
  // Kill this thread
  //

  // But first prevent it from being woken up by asynchronous events

  {
    auto guard = lock_guard(cpu_lock);

    // if IPC timeout active, reset it
    if (_timeout)
      _timeout->reset();

    Sched_context::Ready_queue &rq = Sched_context::rq.current();

    // Switch to time-sharing scheduling context
    if (sched() != sched_context())
      switch_sched(sched_context(), &rq);

    if (!rq.current_sched() || rq.current_sched()->context() == this)
      rq.set_current_sched(current()->sched());
  }

  // if other threads want to send me IPC messages, abort these
  // operations
  {
    auto guard = lock_guard(cpu_lock);
    while (Sender *s = Sender::cast(sender_list()->first()))
      {
        s->sender_dequeue(sender_list());
        s->ipc_receiver_aborted();
        Proc::preemption_point();
      }
  }

  // if engaged in IPC operation, stop it
  if (in_sender_list())
    {
      while (Locked_prio_list *q = wait_queue())
        {
          auto g = lock_guard(q->lock());
          if (wait_queue() == q)
            {
              sender_dequeue(q);
              set_wait_queue(0);
              break;
            }
        }
    }

  release_fpu_if_owner();

  vcpu_update_state();

  unbind();
  vcpu_set_user_space(0);

  cpu_lock.lock();

  arch_vcpu_ext_shutdown();

  state_change_dirty(0, Thread_dead);

  // dequeue from system queues
  Sched_context::rq.current().ready_dequeue(sched());

  if (_del_observer)
    {
      _del_observer->unbind();
      _del_observer = 0;
    }

  rcu_wait();

  state_del_dirty(Thread_ready_mask);

  Sched_context::rq.current().ready_dequeue(sched());

  // make sure this thread really never runs again by migrating it
  // to the 'invalid' CPU forcefully and then switching to the kernel
  // thread for doing the last bits.
  force_to_invalid_cpu();
  kernel_context_drq(handle_kill_helper, 0);
  kdb_ke("Im dead");
  return true;
}

#line 585 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


Context::Drq::Result
Thread::handle_remote_kill(Drq *, Context *self, void *)
{
  Thread *c = nonull_static_cast<Thread*>(self);
  c->state_add_dirty(Thread_cancel | Thread_ready);
  c->_exc_cont.restore(c->regs());
  c->do_trigger_exception(c->regs(), (void*)&Thread::leave_and_kill_myself);
  return Drq::done();
}

#line 596 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"



bool
Thread::kill() 
{
  auto guard = lock_guard(cpu_lock);
  inc_ref();


  if (home_cpu() == current_cpu())
    {
      state_add_dirty(Thread_cancel | Thread_ready);
      Sched_context::rq.current().deblock(sched(), current()->sched());
      _exc_cont.restore(regs()); // overwrite an already triggered exception
      do_trigger_exception(regs(), (void*)&Thread::leave_and_kill_myself);
      return true;
    }

  drq(Thread::handle_remote_kill, 0, Drq::Any_ctxt);

  return true;
}

#line 619 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"



void
Thread::set_sched_params(L4_sched_param const *p)
{
  Sched_context *sc = sched_context();

  // this can actually access the ready queue of a CPU that is offline remotely
  Sched_context::Ready_queue &rq = Sched_context::rq.cpu(home_cpu());
  rq.ready_dequeue(sched());

  sc->set(p);
  sc->replenish();

  if (sc == rq.current_sched())
    rq.set_current_sched(sc);

  if (state() & Thread_ready_mask) // maybe we could ommit enqueueing current
    rq.ready_enqueue(sched());
}

#line 640 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


long
Thread::control(Thread_ptr const &pager, Thread_ptr const &exc_handler)
{
  if (pager.is_valid())
    _pager = pager;

  if (exc_handler.is_valid())
    _exc_handler = exc_handler;

  return 0;
}

#line 702 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


Context::Drq::Result
Thread::handle_migration_helper(Drq *rq, Context *, void *p)
{
  Migration *inf = reinterpret_cast<Migration *>(p);
  Thread *v = static_cast<Thread*>(static_cast<Kernel_drq*>(rq)->src);
  Cpu_number target_cpu = access_once(&inf->cpu);
  v->migrate_away(inf, false);
  v->migrate_to(target_cpu, false);
  return Drq::no_answer_resched();
}

#line 737 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


bool
Thread::do_migration()
{
  Migration *inf = start_migration();

  if ((Mword)inf & 3)
    return (Mword)inf & 1; // already migrated, nothing to do

  spill_fpu_if_owner();

  if (current() == this)
    {
      assert (current_cpu() == home_cpu());
      return kernel_context_drq(handle_migration_helper, inf);
    }
  else
    {
      Cpu_number target_cpu = access_once(&inf->cpu);
      bool resched = migrate_away(inf, false);
      resched |= migrate_to(target_cpu, false);
      return resched; // we already are chosen by the scheduler...
    }
}

#line 762 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"

bool
Thread::initiate_migration() 
{
  assert (current() != this);
  Migration *inf = start_migration();

  if ((Mword)inf & 3)
    return (Mword)inf & 1;

  spill_fpu_if_owner();

  Cpu_number target_cpu = access_once(&inf->cpu);
  bool resched = migrate_away(inf, false);
  resched |= migrate_to(target_cpu, false);
  return resched;
}

#line 779 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


void
Thread::finish_migration() 
{ enqueue_timeout_again(); }

#line 980 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


void
Thread::migrate(Migration *info)
{
  assert (cpu_lock.test());

  LOG_TRACE("Thread migration", "mig", this, Migration_log,
      l->state = state(false);
      l->src_cpu = home_cpu();
      l->target_cpu = info->cpu;
      l->user_ip = regs()->ip();
  );

  _migration = info;
  current()->schedule_if(do_migration());
}

#line 1296 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


void FIASCO_NORETURN
Thread::system_abort()
{
  if (nested_trap_handler)
    kdb_ke("abort");

  terminate(EXIT_FAILURE);
}

#line 1306 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


void
Thread::Migration_log::print(String_buffer *buf) const
{
  buf->printf("migrate from %u to %u (state=%lx user ip=%lx)",
              cxx::int_value<Cpu_number>(src_cpu),
              cxx::int_value<Cpu_number>(target_cpu), state, user_ip);
}
