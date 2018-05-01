// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "timeslice_timeout.h"
#include "timeslice_timeout_i.h"

#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timeslice_timeout.cpp"

/* Initialize global valiable timeslice_timeout */
DEFINE_PER_CPU Per_cpu<Timeout *> timeslice_timeout;
#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timeslice_timeout.cpp"
DEFINE_PER_CPU static Per_cpu<Timeslice_timeout> the_timeslice_timeout(Per_cpu_data::Cpu_num);

#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timeslice_timeout.cpp"


Timeslice_timeout::Timeslice_timeout(Cpu_number cpu)
{
  timeslice_timeout.cpu(cpu) = this;
}

#line 26 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timeslice_timeout.cpp"


/**
 * Timeout expiration callback function
 * @return true to force a reschedule
 */

bool
Timeslice_timeout::expired()
{
  Sched_context::Ready_queue &rq = Sched_context::rq.current();
  Sched_context *sched = rq.current_sched();

  if (sched)
    {
#if 0
      Context *owner = sched->owner();

      // Ensure sched is owner's current timeslice
      assert (owner->sched() == sched);
#endif
      sched->replenish();
      rq.requeue(sched);
      rq.invalidate_sched();

//      owner->switch_sched(sched);
    }

  return true;				// Force reschedule
}
