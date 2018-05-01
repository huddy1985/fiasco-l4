// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef cpu_lock_h
#define cpu_lock_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_lock.cpp"

#include "types.h"

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_lock.cpp"

/** 
 * Global CPU lock. When held, irqs are disabled on the current CPU 
 * (preventing nested irq handling, and preventing the current 
 * thread from being preempted).  It must only be held for very short
 * amounts of time.
 *
 * A generic (cli, sti) implementation of the lock can be found in 
 * cpu_lock-generic.cpp.
 */
class Cpu_lock
{
public:
  /// The return type of test methods
  typedef Mword Status;

  enum { Locked = 1, Not_locked = 0 };

  /// ctor.
  inline Cpu_lock();

  /**
   * Test if the lock is already held.
   * @return 0 if the lock is not held, not 0 if it already is held.
   */
  Status test() const;

  /**
   * Acquire the CPU lock.
   * The CPU lock disables IRQ's it should be held only for a very
   * short amount of time.
   */
  void lock();

  /**
   * Release the CPU lock.
   */
  void clear();

  /**
   * Acquire the CPU lock and return the old status.
   * @return something else than 0 if the lock was already held and
   *   0 if it was not held.
   */
  Status test_and_set();

  /**
   * Set the CPU lock according to the given status.
   * @param state the state to set (0 clear, else lock).
   */
  void set(Status state);

private:
  /// Default copy constructor not implemented.
  Cpu_lock (const Cpu_lock&);
};
#line 60 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_lock.cpp"

/**
 * The global CPU lock, contains the locking data necessary for some
 * special implementations.
 */
extern Cpu_lock cpu_lock;

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_lock-generic.cpp"

#include "processor.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 72 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_lock.cpp"

//NEEDS [Cpu_lock::lock, Cpu_lock::test]
inline Cpu_lock::Status Cpu_lock::test_and_set()
{
  Status ret = test();
  lock();
  return ret;
}

#line 80 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_lock.cpp"

//NEEDS [Cpu_lock::lock, Cpu_lock::clear]
inline void Cpu_lock::set(Cpu_lock::Status state)
{
  if (state)
    lock();
  else
    clear();
}

#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_lock-generic.cpp"


inline Cpu_lock::Cpu_lock()
{}

#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_lock-generic.cpp"


inline void Cpu_lock::lock()
{
  Proc::cli();
}

#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_lock-generic.cpp"


inline void
Cpu_lock::clear()
{
  Proc::sti();
}

#line 26 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_lock-generic.cpp"


inline Cpu_lock::Status Cpu_lock::test() const
{
  return !Proc::interrupts();
}

#endif // cpu_lock_h
