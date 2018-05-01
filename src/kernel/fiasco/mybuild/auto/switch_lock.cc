// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "switch_lock.h"
#include "switch_lock_i.h"


#line 167 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"

/** Acquire the lock with priority inheritance.
 *  If the lock is occupied, enqueue in list of helpers and lend CPU 
 *  to current lock owner until we are the lock owner.
 *  @return #Locked if the lock was already locked by the current context.
 *          #Not_locked if the current context got the lock (the usual case).
 *          #Invalid if the lock does not exist (see valid()).
 */

Switch_lock::Status NO_INSTRUMENT
Switch_lock::lock()
{
  auto guard = lock_guard(cpu_lock);
  return lock_dirty();
}

#line 182 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"


void NO_INSTRUMENT
Switch_lock::help(Context *curr, Context *owner, Address owner_id)
{
  auto s = curr->switch_exec_helping(owner, &_lock_owner, owner_id);
  if (s == Context::Switch::Failed)
    {
      Proc::preemption_point();
      if (curr->home_cpu() != current_cpu())
        curr->schedule();
    }
}

#line 414 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"

/** Free the lock.  
    Return the CPU to helper if there is one, since it had to have a
    higher priority to be able to help (priority may be its own, it
    may run on a donated timeslice or round robin scheduling may have
    selected a thread on the same priority level as me)

    @pre The lock must be valid (see valid()).
 */

void NO_INSTRUMENT
Switch_lock::clear()
{
  auto guard = lock_guard(cpu_lock);

  switch_dirty(clear_no_switch_dirty());
}

#line 431 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"


void NO_INSTRUMENT
Switch_lock::set(Status s)
{
  if (s == Not_locked)
    clear();
}

#line 467 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"


void NO_INSTRUMENT
Switch_lock::wait_free()
{
  auto guard = lock_guard(cpu_lock);
  Context *c = current();

  assert (!valid());

  if ((_lock_owner & ~1UL) == (Address)c)
    {
      clear_lock_owner();
      c->dec_lock_cnt();
      return;
    }

  for(;;)
    {
      assert(cpu_lock.test());

      Address _owner = access_once(&_lock_owner);
      Context *owner = (Context *)(_owner & ~1UL);
      if (!owner)
        break;

      help(c, owner, _owner);
    }
}
