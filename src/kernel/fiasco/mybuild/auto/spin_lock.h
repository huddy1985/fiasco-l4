// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef spin_lock_h
#define spin_lock_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/spin_lock.cpp"

#include "cpu_lock.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/spin_lock.cpp"
#include "types.h"

//
// INTERFACE definition follows 
//

#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/spin_lock.cpp"

class Spin_lock_base : protected Cpu_lock
{
public:
  enum Lock_init { Unlocked = 0 };
};
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/spin_lock.cpp"

/**
 * \brief Basic spin lock.
 *
 * Also disables lock IRQs for the time the lock is held.
 * In the UP case it is in fact just the Cpu_lock.
 */
template<typename Lock_t = Small_atomic_int>
class Spin_lock : public Spin_lock_base
{

#line 25 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/spin_lock.cpp"
private:

public:
  Spin_lock() {}
  explicit Spin_lock(Lock_init) {}
  void init() {}

  using Cpu_lock::Status;
  using Cpu_lock::test;
  using Cpu_lock::lock;
  using Cpu_lock::clear;
  using Cpu_lock::test_and_set;
  using Cpu_lock::set;

};
#line 22 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/spin_lock.cpp"

//--------------------------------------------------------------------------

#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/spin_lock.cpp"

/**
 * \brief Version of a spin lock that is colocated with another value.
 */
template< typename T >
class Spin_lock_coloc : public Spin_lock<Mword>
{
private:
  enum { Arch_lock = 1 };
  Mword _lock;

public:  
#line 81 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/spin_lock.cpp"
  inline Spin_lock_coloc();
  
#line 85 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/spin_lock.cpp"
  inline Spin_lock_coloc(Lock_init i);
  
#line 89 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/spin_lock.cpp"
  inline T
  get_unused() const;
  
#line 95 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/spin_lock.cpp"
  inline void
  set_unused(T val);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 78 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/spin_lock.cpp"



template< typename T > inline Spin_lock_coloc<T>::Spin_lock_coloc() {}

#line 82 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/spin_lock.cpp"



template< typename T > inline Spin_lock_coloc<T>::Spin_lock_coloc(Lock_init i) : Spin_lock<Mword>(i) {}

#line 86 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/spin_lock.cpp"



template< typename T > inline T
Spin_lock_coloc<T>::get_unused() const
{ return (T)(_lock & ~Arch_lock); }

#line 92 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/spin_lock.cpp"



template< typename T > inline void
Spin_lock_coloc<T>::set_unused(T val)
{ _lock = (_lock & Arch_lock) | (Mword)val; }

#endif // spin_lock_h
