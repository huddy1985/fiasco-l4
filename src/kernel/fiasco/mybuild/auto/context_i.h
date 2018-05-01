// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef context_i_h
#define context_i_h
#line 429 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"

#include <cassert>
#line 432 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"
#include "cpu.h"
#line 433 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"
#include "cpu_lock.h"
#line 435 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"
#include "fpu.h"
#line 436 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"
#include "globals.h"		// current()
#line 437 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"
#include "lock_guard.h"
#line 440 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"
#include "mem_layout.h"
#line 441 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"
#include "processor.h"
#line 442 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"
#include "space.h"
#line 443 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"
#include "std_macros.h"
#line 444 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"
#include "thread_state.h"
#line 445 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"
#include "timer.h"
#line 446 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"
#include "timeout.h"
#line 460 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"



#include <cstdio>
#line 1712 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"
#include "warn.h"
#line 2391 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"

#include "kobject_dbg.h"
#line 2393 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"
#include "string_buffer.h"
#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/context-ia32.cpp"

#include <cassert>
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/context-ia32.cpp"

#include "cpu.h"
#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/context-ia32.cpp"
#include "kmem.h"
#line 160 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context-vcpu.cpp"

#include "kobject_dbg.h"
#line 162 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context-vcpu.cpp"
#include "string_buffer.h"

//
// IMPLEMENTATION of inline functions follows
//


#line 911 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"

/**
 * Enqueue current() if ready to fix up ready-list invariant.
 */

inline void
Context::update_ready_list()
{
  assert (this == current());

  if ((state() & Thread_ready_mask) && sched()->left())
    Sched_context::rq.current().ready_enqueue(sched());
}

#line 1093 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"


/**
 * Switch execution context while not running under CPU lock.
 */


inline Context *
Context::handle_helping(Context *t)
{
  // XXX: maybe we do not need this on MP, because we have no helping there
  assert (current() == this);
  // Time-slice lending: if t is locked, switch to its locker
  // instead, this is transitive
  while (t->donatee() &&		// target thread locked
         t->donatee() != t)		// not by itself
    {
      // Special case for Thread::kill(): If the locker is
      // current(), switch to the locked thread to allow it to
      // release other locks.  Do this only when the target thread
      // actually owns locks.
      if (t->donatee() == this)
        {
          if (t->lock_cnt() > 0)
            break;

          return this;
        }

      t = t->donatee();
    }
  return t;
}

#line 1713 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"


inline void
Context::handle_lock_holder_preemption()
{}

#line 1737 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"


inline bool
Context::running_on_different_cpu()
{ return false; }

#line 1742 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context.cpp"


inline bool
Context::need_help(Mword const *, Mword)
{ return true; }

#endif // context_i_h
