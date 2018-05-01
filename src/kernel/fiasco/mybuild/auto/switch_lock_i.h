// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef switch_lock_i_h
#define switch_lock_i_h
#line 78 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"

#include <cassert>
#line 82 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
#include "cpu_lock.h"
#line 83 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
#include "lock_guard.h"

//
// IMPLEMENTATION of inline functions follows
//


#line 142 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"

/** Try to acquire the lock.
    @return #Locked if successful: current context is now the owner of the lock.
            #Not_locked if lock has previously been set.  Returns Not_locked
	    even if the current context is already the lock owner.
	    The result is #Invalid if the lock does not exist (see valid()).
 */


inline Switch_lock::Status NO_INSTRUMENT
Switch_lock::try_lock()
{
  auto guard = lock_guard(cpu_lock);

  if (EXPECT_FALSE(!valid()))
    return Invalid;

  Context *c = current();
  bool ret = set_lock_owner(c);

  if (ret)
    c->inc_lock_cnt();	// Do not lose this lock if current is deleted

  return ret ? Locked : Not_locked;
}

#endif // switch_lock_i_h
