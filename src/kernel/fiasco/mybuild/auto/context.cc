// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "context.h"
#include "context_i.h"

#line 447 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"

DEFINE_PER_CPU Per_cpu<Clock> Context::_clock(Per_cpu_data::Cpu_num);
#line 449 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"
DEFINE_PER_CPU Per_cpu<Context *> Context::_kernel_ctxt;
#line 450 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"
DEFINE_PER_CPU Per_cpu<Context::Kernel_drq> Context::_kernel_drq;
#line 585 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"


/** @name State manipulation */
//@{
//-
#line 727 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"

//@}
//-
#line 906 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"

// queue operations

// XXX for now, synchronize with global kernel lock
//-
#line 1707 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"

//----------------------------------------------------------------------------


#line 1783 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"



inline void
Context::shutdown_drqs()
{ _drq_q.handle_requests(Drq_q::Drop); }

#line 516 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"


void
Context::spill_current_fpu(Cpu_number cpu)
{
  (void)cpu;
  assert (cpu == current_cpu());
  Fpu &f = Fpu::fpu.current();
  if (f.owner())
    {
      f.enable();
      f.owner()->spill_fpu();
      f.set_owner(0);
      f.disable();
    }
}

#line 546 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"

/** Destroy context.
 */

Context::~Context()
{}

#line 762 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"

/**
 * Switch active timeslice of this Context.
 * @param next Sched_context to switch to
 */

void
Context::switch_sched(Sched_context *next, Sched_context::Ready_queue *queue)
{
  queue->switch_sched(sched(), next);
  set_sched(next);
}

#line 774 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"

/**
 * Select a different context for running and activate it.
 */

void
Context::schedule()
{
  auto guard = lock_guard(cpu_lock);
  assert (!Sched_context::rq.current().schedule_in_progress);

  // we give up the CPU as a helpee, so we have no helper anymore
  if (EXPECT_FALSE(helper() != 0))
    set_helper(Not_Helping);

  // if we are a thread on a foreign CPU we must ask the kernel context to
  // schedule for us
  Cpu_number current_cpu = ::current_cpu();
  while (EXPECT_FALSE(current_cpu != access_once(&_home_cpu)))
    {
      Context *kc = Context::kernel_context(current_cpu);
      assert (this != kc);

      // flag that we need to schedule
      kc->state_add_dirty(Thread_need_resched);
      switch (switch_exec_locked(kc, Ignore_Helping))
        {
        case Switch::Ok:
          return;
        case Switch::Resched:
          current_cpu = ::current_cpu();
          continue;
        case Switch::Failed:
          assert (false);
          continue;
        }
    }

  // now, we are sure that a thread on its home CPU calls schedule.
  CNT_SCHEDULE;

  // Ensure only the current thread calls schedule
  assert (this == current());

  Sched_context::Ready_queue *rq = &Sched_context::rq.current();

  // Enqueue current thread into ready-list to schedule correctly
  update_ready_list();

  // Select a thread for scheduling.
  Context *next_to_run;

  for (;;)
    {
      next_to_run = rq->next_to_run()->context();

      // Ensure ready-list sanity
      assert (next_to_run);

      if (EXPECT_FALSE(!(next_to_run->state() & Thread_ready_mask)))
        rq->ready_dequeue(next_to_run->sched());
      else switch (schedule_switch_to_locked(next_to_run))
        {
        default:
        case Switch::Ok:      return;   // ok worked well
        case Switch::Failed:  break;    // not migrated, need preemption point
        case Switch::Resched:
          {
            Cpu_number n = ::current_cpu();
            if (n != current_cpu)
              {
                current_cpu = n;
                rq = &Sched_context::rq.current();
              }
          }
          continue; // may have been migrated...
        }

      rq->schedule_in_progress = this;
      Proc::preemption_point();
      if (EXPECT_TRUE(current_cpu == ::current_cpu()))
        rq->schedule_in_progress = 0;
      else
        return; // we got migrated and selected on our new CPU, so we may run
    }
}

#line 935 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"


/**
 * \brief Activate a newly created thread.
 *
 * This function sets a new thread onto the ready list and switches to
 * the thread if it can preempt the currently running thread.
 */

void
Context::activate()
{
  auto guard = lock_guard(cpu_lock);
  if (xcpu_state_change(~0UL, Thread_ready, true))
    current()->switch_to_locked(this);
}

#line 1126 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"


/**
 * Switch to a specific different execution context.
 *        If that context is currently locked, switch to its locker instead
 *        (except if current() is the locker)
 * @pre current() == this  &&  current() != t
 * @param t thread that shall be activated.
 * @param mode helping mode; we either help, don't help or leave the
 *             helping state unchanged
 */

Context::Switch FIASCO_WARN_RESULT //L4_IPC_CODE
Context::switch_exec_locked(Context *t, enum Helping_mode mode)
{
  // Must be called with CPU lock held
  assert (t);
  assert (cpu_lock.test());
  assert (current() != t);
  assert (current() == this);

  // only for logging
  Context *t_orig = t;
  (void)t_orig;

  // Time-slice lending: if t is locked, switch to its locker
  // instead, this is transitive
  //
  // For the Thread_lock case only, so skip this
  // t = handle_helping(t);
  Context *ret = handle_helping(t);
  assert(ret == t);
  (void)ret;

  if (EXPECT_FALSE(t->running_on_different_cpu()))
    {
      if (!t->in_ready_list())
        Sched_context::rq.current().ready_enqueue(t->sched());
      return Switch::Failed;
    }


  LOG_CONTEXT_SWITCH;
  CNT_CONTEXT_SWITCH;

  // Can only switch to ready threads!
  // do not consider CPU locality here t can be temporarily migrated
  if (EXPECT_FALSE (!(t->state(false) & Thread_ready_mask)))
    {
      assert (state(false) & Thread_ready_mask);
      return Switch::Failed;
    }


  // Ensure kernel stack pointer is non-null if thread is ready
  assert (t->_kernel_sp);

  t->set_helper(mode);

  if (EXPECT_TRUE(current_cpu() == home_cpu()))
    update_ready_list();

  t->set_current_cpu(get_current_cpu());
  switch_fpu(t);
  switch_cpu(t);

  return switch_handle_drq();
}

#line 1194 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"


Context::Switch
Context::switch_exec_helping(Context *t, Mword const *lock, Mword val)
{
  // Must be called with CPU lock held
  assert (t);
  assert (cpu_lock.test());
  assert (current() != t);
  assert (current() == this);

  // only for logging
  Context *t_orig = t;
  (void)t_orig;

  // Time-slice lending: if t is locked, switch to its locker
  // instead, this is transitive
  //
  // For the Thread_lock case only, so skip this
  // t = handle_helping(t);

  // we actually hold locks
  if (!t->need_help(lock, val))
    return Switch::Failed;

  LOG_CONTEXT_SWITCH;

  // Can only switch to ready threads!
  // do not consider CPU locality here t can be temporarily migrated
  if (EXPECT_FALSE (!(t->state(false) & Thread_ready_mask)))
    {
      assert (state(false) & Thread_ready_mask);
      return Switch::Failed;
    }


  // Ensure kernel stack pointer is non-null if thread is ready
  assert (t->_kernel_sp);

  if (EXPECT_TRUE(get_current_cpu() == home_cpu()))
    update_ready_list();

  t->set_helper(Helping);
  t->set_current_cpu(get_current_cpu());
  switch_fpu(t);
  switch_cpu(t);
  return switch_handle_drq();
}

#line 1359 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"

/**
 * \brief Forced dequeue from lock wait queue, or DRQ queue.
 */

void
Context::force_dequeue()
{
  Queue_item *const qi = queue_item();

  if (qi->queued())
    {
      // we're waiting for a lock or have a DRQ pending
      Queue *const q = qi->queue();
        {
          auto guard = lock_guard(q->q_lock());
          // check again, with the queue lock held.
          // NOTE: we may be already removed from the queue on another CPU
          if (qi->queued() && qi->queue())
            {
              // we must never be taken from one queue to another on a
              // different CPU
              assert(q == qi->queue());
              // pull myself out of the queue, mark reason as invalidation
              q->dequeue(qi, Queue_item::Invalid);
            }
        }
    }
}

#line 1388 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"

/**
 * \brief Dequeue from lock and DRQ queues, abort pending DRQs
 */

void
Context::shutdown_queues()
{
  force_dequeue();
  shutdown_drqs();
}

#line 1420 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"


/**
 * \brief Handle all pending DRQs.
 * \pre cpu_lock.test() (The CPU lock must be held).
 * \pre current() == this (only the currently running context is allowed to
 *      call this function).
 * \return true if re-scheduling is needed (ready queue has changed),
 *         false if not.
 */
//inline
bool
Context::handle_drq()
{

  assert (check_for_current_cpu());
  assert (cpu_lock.test());

  bool resched = false;
  Mword st = state();
  if (EXPECT_FALSE(st & Thread_switch_hazards))
    {
      state_del_dirty(Thread_switch_hazards);
      if (st & Thread_finish_migration)
        finish_migration();

      if (st & Thread_need_resched)
        resched = true;
    }

  if (EXPECT_TRUE(!drq_pending()))
    return resched;

  Mem::barrier();
  resched |= _drq_q.handle_requests();
  state_del_dirty(Thread_drq_ready);

  //LOG_MSG_3VAL(this, "xdrq", state(), 0, cpu_lock.test());

  /*
   * When the context is marked as dead (Thread_dead) then we must not execute
   * any usual context code, however DRQ handlers may run.
   */
  if (state() & Thread_dead)
    state_del_dirty(Thread_ready_mask);

  return resched || !(state() & Thread_ready_mask);
}

#line 1630 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"


bool
Context::kernel_context_drq(Drq::Request_func *func, void *arg)
{
  if (EXPECT_TRUE(home_cpu() == get_current_cpu()))
    update_ready_list();

  Context *kc = kernel_context(current_cpu());
  if (current() == kc)
    return func(0, kc, arg).need_resched();

  Kernel_drq *mdrq = new (&_kernel_drq.current()) Kernel_drq;

  mdrq->src = this;
  mdrq->func  = func;
  mdrq->arg   = arg;
  kc->_drq_q.enq(mdrq);
  return schedule_switch_to_locked(kc) != Switch::Ok;
}

#line 1657 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"


bool
Context::rcu_unblock(Rcu_item *i)
{
  assert(cpu_lock.test());
  return static_cast<Context*>(i)->xcpu_state_change(~Thread_waiting, Thread_ready);
}

#line 1670 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"


void
Context::xcpu_tlb_flush(...)
{
  // This should always be optimized away
  assert(0);
}

#line 1756 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"


bool
Context::enqueue_drq(Drq *rq, Drq::Exec_mode /*exec*/)
{
  assert (cpu_lock.test());

  LOG_TRACE("DRQ handling", "drq", current(), Drq_log,
      l->type = rq->context() == this
                                 ? Drq_log::Type::Send_reply
                                 : Drq_log::Type::Do_send;
      l->func = (void*)rq->func;
      l->thread = this;
      l->target_cpu = home_cpu();
      l->wait = 0;
      l->rq = rq;
  );

  bool do_sched = _drq_q.execute_request(rq, Drq_q::No_drop, true);
  if (   access_once(&_home_cpu) == current_cpu()
      && (state() & Thread_ready_mask) && !in_ready_list())
    {
      Sched_context::rq.current().ready_enqueue(sched());
      return true;
    }
  return do_sched;
}

#line 2401 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"


void
Context::Drq_log::print(String_buffer *buf) const
{
  static char const *const _types[] =
    { "send", "do send", "do request", "send reply", "do reply", "done" };

  char const *t = "unk";
  if ((unsigned)type < sizeof(_types)/sizeof(_types[0]))
    t = _types[(unsigned)type];

  buf->printf("%s(%s) rq=%p to ctxt=%lx/%p (func=%p) cpu=%u",
      t, wait ? "wait" : "no-wait", rq, Kobject_dbg::pointer_to_id(thread),
      thread, func, cxx::int_value<Cpu_number>(target_cpu));
}

#line 2417 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"

// context switch

void
Tb_entry_ctx_sw::print(String_buffer *buf) const
{
  Context *sctx = 0;
  Mword sctxid = ~0UL;
  Mword dst;
  Mword dst_orig;

  sctx = from_sched->context();
  sctxid = Kobject_dbg::pointer_to_id(sctx);

  dst = Kobject_dbg::pointer_to_id(this->dst);
  dst_orig = Kobject_dbg::pointer_to_id(this->dst_orig);

  if (sctx != ctx())
    buf->printf("(%lx)", sctxid);

  buf->printf(" ==> %lx ", dst);

  if (dst != dst_orig || lock_cnt)
    buf->printf("(");

  if (dst != dst_orig)
    buf->printf("want %lx", dst_orig);

  if (dst != dst_orig && lock_cnt)
    buf->printf(" ");

  if (lock_cnt)
    buf->printf("lck %lu", lock_cnt);

  if (dst != dst_orig || lock_cnt)
    buf->printf(") ");

  buf->printf(" krnl " L4_PTR_FMT " @ " L4_PTR_FMT, kernel_ip, _ip);
}
