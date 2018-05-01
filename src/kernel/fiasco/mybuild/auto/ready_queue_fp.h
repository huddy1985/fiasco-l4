// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef ready_queue_fp_h
#define ready_queue_fp_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ready_queue_fp.cpp"

#include "config.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ready_queue_fp.cpp"
#include <cxx/dlist>
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ready_queue_fp.cpp"
#include "member_offs.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ready_queue_fp.cpp"
#include "types.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ready_queue_fp.cpp"
#include "globals.h"

//
// INTERFACE definition follows 
//

#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ready_queue_fp.cpp"


struct L4_sched_param_fixed_prio : public L4_sched_param
{
  enum : Smword { Class = -1 };
  Mword quantum;
  unsigned short prio;
};
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ready_queue_fp.cpp"

template<typename E>
class Ready_queue_fp
{
  friend class Jdb_thread_list;
  template<typename T>
  friend struct Jdb_thread_list_policy;

private:
  typedef typename E::Fp_list List;
  unsigned prio_highest;
  List prio_next[256];

public:
  void set_idle(E *sc)
  { sc->_prio = Config::Kernel_prio; }

  void enqueue(E *, bool);
  void dequeue(E *);
  E *next_to_run() const;

public:  
#line 101 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ready_queue_fp.cpp"
  inline void
  requeue(E *i);
  
#line 112 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ready_queue_fp.cpp"
  inline void
  deblock_refill(E *);
};
#line 37 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ready_queue_fp.cpp"


// ---------------------------------------------------------------------------


//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ready_queue_fp.cpp"

#include <cassert>
#line 43 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ready_queue_fp.cpp"
#include "cpu_lock.h"
#line 44 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ready_queue_fp.cpp"
#include "std_macros.h"
#line 45 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ready_queue_fp.cpp"
#include "config.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 97 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ready_queue_fp.cpp"




template<typename E> inline void
Ready_queue_fp<E>::requeue(E *i)
{
  if (!i->in_ready_list())
    enqueue(i, false);
  else
    prio_next[i->prio()].rotate_to(*++List::iter(i));
}

#line 109 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ready_queue_fp.cpp"


 
template<typename E> inline void
Ready_queue_fp<E>::deblock_refill(E *)
{}

#line 46 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ready_queue_fp.cpp"




template<typename E> inline E *
Ready_queue_fp<E>::next_to_run() const
{ return prio_next[prio_highest].front(); }

#line 75 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ready_queue_fp.cpp"

/**
 * Remove context from ready-list.
 */


template<typename E> inline void
Ready_queue_fp<E>::dequeue(E *i)
{
  assert (cpu_lock.test());

  // Don't dequeue threads which aren't enqueued
  if (EXPECT_FALSE (!i->in_ready_list()))
    return;

  unsigned short prio = i->prio();

  prio_next[prio].remove(i);

  while (prio_next[prio_highest].empty() && prio_highest)
    prio_highest--;
}

//
// IMPLEMENTATION of function templates
//


#line 53 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ready_queue_fp.cpp"

/**
 * Enqueue context in ready-list.
 */


template<typename E> void
Ready_queue_fp<E>::enqueue(E *i, bool is_current_sched)
{
  assert(cpu_lock.test());

  // Don't enqueue threads which are already enqueued
  if (EXPECT_FALSE (i->in_ready_list()))
    return;

  unsigned short prio = i->prio();

  if (prio > prio_highest)
    prio_highest = prio;

  prio_next[prio].push(i, is_current_sched ? List::Front : List::Back);
}

#endif // ready_queue_fp_h
