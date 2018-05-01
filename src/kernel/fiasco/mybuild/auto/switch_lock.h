// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef switch_lock_h
#define switch_lock_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"

#include "member_offs.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
#include <types.h>

//
// INTERFACE definition follows 
//

#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"

class Context;
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"

#ifdef NO_INSTRUMENT
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
#undef NO_INSTRUMENT
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
#endif
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
#define NO_INSTRUMENT __attribute__((no_instrument_function))
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"


/** A lock that implements priority inheritance.
 *
 * The lock uses a validity checker (VALID) for doing an existence check
 * before the lock is actually acquired. With this mechanism the lock itself
 * may disappear while it is locked (see clear_no_switch_dirty() and 
 * switch_dirty()), even if it is under contention. When the lock no longer
 * exists VALID::valid(void const *lock) must return false, true if it
 * exists (see Switch_lock_valid). This mechanism is used in Thread_lock
 * when thread control blocks are deallocated.
 *
 * The operations lock(), lock_dirty(), try_lock(), test(), test_and_set(),
 * and test_and_set_dirty() may return #Invalid if the lock does 
 * no longer exist.
 *
 * The operations initialize(), lock_owner(), clear(), clear_dirty(), and
 * clear_no_switch_dirty() must not be called on any invalid lock,
 * thus the lock itself must be held for using these operations. 
 * (Except initialize(), which is only useful for locks that are always 
 * valid.)
 * 
 * @param VALID must be set to a validity checker for the lock.
 * 
 * The validity checker is used while acquiring the lock to test
 * if the lock itself exists. We assume that a lock may disappear
 * while we are blocked on it.
 */
class Switch_lock
{
  MEMBER_OFFSET();

private:
  // Warning: This lock's member variables must not need a
  // constructor.  Switch_lock instances must assume
  // zero-initialization or be initialized using the initialize()
  // member function.
  // Reason: to avoid overwriting the lock in the thread-ctor
  Address _lock_owner;

public:
  /**
   * @brief The result type of lock operations.
   */
  enum Status 
  {
    Not_locked, ///< The lock was formerly not acquired and -- we got it
    Locked,     ///< The lock was already acquired by ourselves
    Invalid     ///< The lock does not exist (is invalid)
  };

  /**
   * Stores the context of the lock for a later switch.
   * (see clear_no_switch_dirty(), switch_dirty())
   */
  struct Lock_context
  {
    Context *owner;
  };

public:  
#line 89 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
  // 
  // Switch_lock inlines 
  //
  
  /**
   * Test if the lock is valid (uses the validity checker).
   * @return true if the lock really exists, false if not.
   */
  
  
  inline bool NO_INSTRUMENT
  valid() const;
  
#line 103 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
  /** Initialize Switch_lock.  Call this function if you cannot
      guarantee that your Switch_lock instance is allocated from
      zero-initialized memory. */
  
  
  inline void NO_INSTRUMENT
  initialize();
  
#line 114 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
  /** Lock owner. 
   *  @pre The lock must be valid (see valid()).
   *  @return current owner of the lock.  0 if there is no owner.
   */
  
  
  inline Context * NO_INSTRUMENT
  lock_owner() const;
  
#line 127 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
  /** Is lock set?.
      @return #Locked if lock is set, #Not_locked if not locked, and #Invalid if 
              the lock does not exist (see valid()).
   */
  
  
  inline Switch_lock::Status NO_INSTRUMENT
  test() const;
  
#line 168 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
  /** Acquire the lock with priority inheritance.
   *  If the lock is occupied, enqueue in list of helpers and lend CPU 
   *  to current lock owner until we are the lock owner.
   *  @return #Locked if the lock was already locked by the current context.
   *          #Not_locked if the current context got the lock (the usual case).
   *          #Invalid if the lock does not exist (see valid()).
   */
  
  Switch_lock::Status NO_INSTRUMENT
  lock();
  
#line 196 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
  /** Acquire the lock with priority inheritance.
   *  If the lock is occupied, enqueue in list of helpers and lend CPU 
   *  to current lock owner until we are the lock owner (see lock()).
   *  @pre caller holds cpu lock
   *  @return #Locked if the lock was already locked by the current context.
   *          #Not_locked if the current context got the lock (the usual case).
   *          #Invalid if the lock does not exist (see valid()).
   */
  
  
  inline Switch_lock::Status NO_INSTRUMENT
  lock_dirty();
  
#line 240 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
  /** Acquire the lock with priority inheritance.
   *  @return #Locked if we owned the lock already.  #Not_locked otherwise.
   *          #Invalid is returned if the lock does not exist (see valid()).
   */
  
  
  inline Switch_lock::Status NO_INSTRUMENT
  test_and_set();
  
#line 252 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
  /** Acquire the lock with priority inheritance (see test_and_set()).
   *  @return #Locked if we owned the lock already.  #Not_locked otherwise.
   *          #Invalid is returned if the lock does not exist (see valid()).
   *          @pre caller holds cpu lock
   */
  
  
  inline Switch_lock::Status NO_INSTRUMENT
  test_and_set_dirty();
  
#line 415 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
  /** Free the lock.  
      Return the CPU to helper if there is one, since it had to have a
      higher priority to be able to help (priority may be its own, it
      may run on a donated timeslice or round robin scheduling may have
      selected a thread on the same priority level as me)
  
      @pre The lock must be valid (see valid()).
   */
  
  void NO_INSTRUMENT
  clear();
  
#line 433 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
  void NO_INSTRUMENT
  set(Status s);
  
#line 440 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
  /** Free the lock.
      Return the CPU to helper if there is one, since it had to have a
      higher priority to be able to help (priority may be its own, it
      may run on a donated timeslice or round robin scheduling may have
      selected a thread on the same priority level as me).
      If _lock_owner is 0, then this is a no op
  
      @pre The lock must be valid (see valid())
      @pre caller holds cpu lock
   */
  
  
  inline void NO_INSTRUMENT
  clear_dirty();
  
#line 461 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
  inline void NO_INSTRUMENT
  invalidate();
  
#line 469 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
  void NO_INSTRUMENT
  wait_free();

protected:  
#line 354 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
  /**
   * Clear the lock, however do not switch to a potential helper yet.
   * This function is used when the lock must be cleared and the object
   * containing the lock will be deallocated atomically. We have to do the
   * switch later using switch_dirty(Lock_context).
   * @return the context for a later switch_dirty()
   * @pre The lock must be valid (see valid()).
   * @pre caller hold cpu lock
   * @post switch_dirty() must be called in the same atomical section
   */
  
  
  inline Switch_lock::Lock_context NO_INSTRUMENT
  clear_no_switch_dirty();
  
#line 377 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
  /**
   * Do the switch part of clear() after a clear_no_switch_dirty().
   * This function does not touch the lock itself (may be called on 
   * an invalid lock).
   * @param c the context returned by a former clear_no_switch_dirty().
   * @pre must be called atomically with clear_no_switch_dirty(),
   *      under the same cpu lock
   */
  
  
  static inline void NO_INSTRUMENT
  switch_dirty(Lock_context const &c);

private:  
#line 143 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
  /** Try to acquire the lock.
      @return #Locked if successful: current context is now the owner of the lock.
              #Not_locked if lock has previously been set.  Returns Not_locked
  	    even if the current context is already the lock owner.
  	    The result is #Invalid if the lock does not exist (see valid()).
   */
  
  
  inline Switch_lock::Status NO_INSTRUMENT
  try_lock();
  
#line 184 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
  void NO_INSTRUMENT
  help(Context *curr, Context *owner, Address owner_id);
  
#line 268 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
  inline void NO_INSTRUMENT
  clear_lock_owner();
  
#line 275 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
  inline bool NO_INSTRUMENT
  set_lock_owner(Context *o);
  
#line 283 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
  static inline void
  schedule(Context *curr);
};
#line 72 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"

#undef NO_INSTRUMENT
#line 74 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
#define NO_INSTRUMENT 

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 80 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"

#include "atomic.h"
#line 84 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
#include "context.h"
#line 85 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
#include "globals.h"
#line 86 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"
#include "processor.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 87 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"


// 
// Switch_lock inlines 
//

/**
 * Test if the lock is valid (uses the validity checker).
 * @return true if the lock really exists, false if not.
 */


inline bool NO_INSTRUMENT
Switch_lock::valid() const
{ return (_lock_owner & 1) == 0; }

#line 102 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"

/** Initialize Switch_lock.  Call this function if you cannot
    guarantee that your Switch_lock instance is allocated from
    zero-initialized memory. */


inline void NO_INSTRUMENT
Switch_lock::initialize()
{
  _lock_owner = 0;
}

#line 113 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"

/** Lock owner. 
 *  @pre The lock must be valid (see valid()).
 *  @return current owner of the lock.  0 if there is no owner.
 */


inline Context * NO_INSTRUMENT
Switch_lock::lock_owner() const
{
  auto guard = lock_guard(cpu_lock);
  return (Context*)(_lock_owner & ~1UL);
}

#line 126 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"

/** Is lock set?.
    @return #Locked if lock is set, #Not_locked if not locked, and #Invalid if 
            the lock does not exist (see valid()).
 */


inline Switch_lock::Status NO_INSTRUMENT
Switch_lock::test() const
{
  auto guard = lock_guard(cpu_lock);
  Address o = access_once(&_lock_owner);
  if (EXPECT_FALSE(o & 1))
    return Invalid;
  return o ? Locked : Not_locked;
}

#line 273 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"


inline bool NO_INSTRUMENT
Switch_lock::set_lock_owner(Context *o)
{
  _lock_owner = Address(o) | (_lock_owner & 1);
  return true;
}

#line 195 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"

/** Acquire the lock with priority inheritance.
 *  If the lock is occupied, enqueue in list of helpers and lend CPU 
 *  to current lock owner until we are the lock owner (see lock()).
 *  @pre caller holds cpu lock
 *  @return #Locked if the lock was already locked by the current context.
 *          #Not_locked if the current context got the lock (the usual case).
 *          #Invalid if the lock does not exist (see valid()).
 */


inline Switch_lock::Status NO_INSTRUMENT
Switch_lock::lock_dirty()
{
  assert(cpu_lock.test());

  Mword o = access_once(&_lock_owner);
  if (EXPECT_FALSE(o & 1))
    return Invalid;

  Context *c = current();
  if (o == Address(c))
    return Locked;

  do
    {
      for (;;)
        {
          Mword o = access_once(&_lock_owner);
          if (o & 1)
            return Invalid;

          if (!o)
            break;

          help(c, (Context *)o, o);
        }
    }
  while (!set_lock_owner(c));
  Mem::mp_wmb();
  c->inc_lock_cnt();   // Do not lose this lock if current is deleted
  return Not_locked;
}

#line 238 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"


/** Acquire the lock with priority inheritance.
 *  @return #Locked if we owned the lock already.  #Not_locked otherwise.
 *          #Invalid is returned if the lock does not exist (see valid()).
 */


inline Switch_lock::Status NO_INSTRUMENT
Switch_lock::test_and_set()
{
  return lock();
}

#line 251 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"

/** Acquire the lock with priority inheritance (see test_and_set()).
 *  @return #Locked if we owned the lock already.  #Not_locked otherwise.
 *          #Invalid is returned if the lock does not exist (see valid()).
 *          @pre caller holds cpu lock
 */


inline Switch_lock::Status NO_INSTRUMENT
Switch_lock::test_and_set_dirty()
{
  return lock_dirty();
}

#line 439 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"

/** Free the lock.
    Return the CPU to helper if there is one, since it had to have a
    higher priority to be able to help (priority may be its own, it
    may run on a donated timeslice or round robin scheduling may have
    selected a thread on the same priority level as me).
    If _lock_owner is 0, then this is a no op

    @pre The lock must be valid (see valid())
    @pre caller holds cpu lock
 */


inline void NO_INSTRUMENT
Switch_lock::clear_dirty()
{
  assert(cpu_lock.test());

  switch_dirty(clear_no_switch_dirty());
}

#line 459 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"


inline void NO_INSTRUMENT
Switch_lock::invalidate()
{
  auto guard = lock_guard(cpu_lock);
  atomic_mp_or(&_lock_owner, 1);
}

#line 266 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"


inline void NO_INSTRUMENT
Switch_lock::clear_lock_owner()
{
  _lock_owner &= 1;
}

#line 353 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"

/**
 * Clear the lock, however do not switch to a potential helper yet.
 * This function is used when the lock must be cleared and the object
 * containing the lock will be deallocated atomically. We have to do the
 * switch later using switch_dirty(Lock_context).
 * @return the context for a later switch_dirty()
 * @pre The lock must be valid (see valid()).
 * @pre caller hold cpu lock
 * @post switch_dirty() must be called in the same atomical section
 */


inline Switch_lock::Lock_context NO_INSTRUMENT
Switch_lock::clear_no_switch_dirty()
{
  Mem::mp_wmb();
  Lock_context c;
  c.owner = lock_owner();
  clear_lock_owner();
  c.owner->dec_lock_cnt();
  return c;
}

#line 281 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"


inline void
Switch_lock::schedule(Context *curr)
{ curr->schedule(); }

#line 376 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/switch_lock.cpp"

/**
 * Do the switch part of clear() after a clear_no_switch_dirty().
 * This function does not touch the lock itself (may be called on 
 * an invalid lock).
 * @param c the context returned by a former clear_no_switch_dirty().
 * @pre must be called atomically with clear_no_switch_dirty(),
 *      under the same cpu lock
 */


inline void NO_INSTRUMENT
Switch_lock::switch_dirty(Lock_context const &c)
{
  assert (current() == c.owner);

  Context *curr = c.owner;
  Context *h = curr->helper();

  /*
   * If someone helped us by lending its time slice to us.
   * Just switch back to the helper without changing its helping state.
   */
  bool need_sched = false;

  if (h != curr)
    if (   EXPECT_FALSE(h->home_cpu() != current_cpu())
        || EXPECT_FALSE((long)curr->switch_exec_locked(h, Context::Ignore_Helping)))
      need_sched = true;

  if (!need_sched)
    need_sched = (   curr->lock_cnt() == 0
                  && (   curr->home_cpu() != current_cpu()
                      || curr->donatee()));

  if (EXPECT_FALSE(need_sched))
    schedule(curr);
}

#endif // switch_lock_h
