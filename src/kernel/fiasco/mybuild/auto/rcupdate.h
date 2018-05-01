// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef rcupdate_h
#define rcupdate_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"

#include "cpu_mask.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
#include "per_cpu_data.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
#include "spin_lock.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
#include <cxx/slist>
#line 149 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"

#include "tb_entry.h"

//
// INTERFACE definition follows 
//

#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"

class Rcu_glbl;
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
class Rcu_data;
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"

/**
 * \brief Encapsulation of RCU batch number.
 */
class Rcu_batch
{
  friend class Jdb_rcupdate;
public:
  /// create uninitialized batch.
  Rcu_batch() {}
  /// create a btach initialized with \a b.
  Rcu_batch(long b) : _b(b) {}

  /// less than comparison.
  bool operator < (Rcu_batch const &o) const { return (_b - o._b) < 0; }
  /// greater than comparison.
  bool operator > (Rcu_batch const &o) const { return (_b - o._b) > 0; }
  /// greater than comparison.
  bool operator >= (Rcu_batch const &o) const { return (_b - o._b) >= 0; }
  /// equelity check.
  bool operator == (Rcu_batch const &o) const { return _b == o._b; }
  /// inequality test.
  bool operator != (Rcu_batch const &o) const { return _b != o._b; }
  /// increment batch.
  Rcu_batch &operator ++ () { ++_b; return *this; }
  /// increase batch with \a r.
  Rcu_batch operator + (long r) { return Rcu_batch(_b + r); }


private:
  long _b;
};
#line 42 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"

/**
 * \brief Item that can bequeued for the next grace period.
 *
 * An RCU item is basically a pointer to a callback which is called
 * after one grace period.
 */
class Rcu_item : public cxx::S_list_item
{
  friend class Rcu_data;
  friend class Rcu;
  friend class Jdb_rcupdate;

private:
  bool (*_call_back)(Rcu_item *);
};
#line 58 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"


/**
 * \brief List of Rcu_items.
 *
 * RCU lists are used a lot of times in the RCU implementation and are
 * implemented as single linked lists with FIFO semantics.
 *
 * \note Concurrent access to the list is not synchronized.
 */
class Rcu_list : public cxx::S_list_tail<Rcu_item>
{
private:
  typedef cxx::S_list_tail<Rcu_item> Base;
public:
  Rcu_list() {}
  Rcu_list(Rcu_list &&o) : Base(static_cast<Base &&>(o)) {}
  Rcu_list &operator = (Rcu_list &&o)
  {
    Base::operator = (static_cast<Base &&>(o));
    return *this;
  }

private:
  friend class Jdb_rcupdate;

public:  
#line 235 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  /**
   * \brief Enqueue Rcu_item into the list (at the tail).
   * \prarm i the RCU item to enqueue.
   */
  inline void enqueue(Rcu_item *i);
};
#line 84 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"

/**
 * \brief CPU local data structure for RCU.
 */
class Rcu_data
{
  friend class Jdb_rcupdate;
public:

  Rcu_batch _q_batch;   ///< batch nr. for grace period
  bool _q_passed;       ///< quiescent state passed?
  bool _pending;        ///< wait for quiescent state
  bool _idle;

  Rcu_batch _batch;
  Rcu_list _n;
  long _len;
  Rcu_list _c;
  Rcu_list _d;
  Cpu_number _cpu;

public:  
#line 229 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  Rcu_data(Cpu_number cpu);
  
#line 241 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  /**
   * \pre must run under cpu lock
   */
  
  inline void
  enqueue(Rcu_item *i);
  
#line 297 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  void
  enter_idle(Rcu_glbl *rgp);
  
#line 410 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  ~Rcu_data();
  
#line 430 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  bool FIASCO_WARN_RESULT
  process_callbacks(Rcu_glbl *rgp);
  
#line 470 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  inline bool
  pending(Rcu_glbl *rgp) const;

private:  
#line 253 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  inline bool
  do_batch();
  
#line 353 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  void
  check_quiescent_state(Rcu_glbl *rgp);
  
#line 401 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  void
  move_batch(Rcu_list &l);
};
#line 105 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"


/**
 * \brief Global RCU data structure.
 */
class Rcu_glbl
{
  friend class Rcu_data;
  friend class Rcu;
  friend class Jdb_rcupdate;

private:
  Rcu_batch _current;      ///< current batch
  Rcu_batch _completed;    ///< last completed batch
  bool _next_pending;      ///< next batch already pending?
  Spin_lock<> _lock;
  Cpu_mask _cpus;

  Cpu_mask _active_cpus;


public:  
#line 223 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  Rcu_glbl();

private:  
#line 283 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  inline void
  start_batch();
  
#line 341 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  inline void
  cpu_quiet(Cpu_number cpu);
};
#line 126 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"

/**
 * \brief encapsulation of RCU implementation.
 *
 * This class aggregates per CPU data structures as well as the global
 * data structure for RCU and provides a common RCU interface.
 */
class Rcu
{
  friend class Rcu_data;
  friend class Jdb_rcupdate;

public:
  /// The lock to prevent a quiescent state.
  typedef Cpu_lock Lock;
  static Rcu_glbl *rcu() { return &_rcu; }
private:
  static Rcu_glbl _rcu;
  static Per_cpu<Rcu_data> _rcu_data;

#line 151 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
private:

public:
  struct Log_rcu : public Tb_entry
  {
    Cpu_number cpu;
    Rcu_item *item;
    void *cb;
    unsigned char event;
    void print(String_buffer *buf) const;
  };

  enum Rcu_events
  {
    Rcu_call = 0,
    Rcu_process = 1,
  };

public:  
#line 318 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  static inline void
  enter_idle(Cpu_number cpu);
  
#line 326 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  static inline void
  leave_idle(Cpu_number cpu);
  
#line 383 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  //inline NEEDS["cpu_lock.h", "globals.h", "lock_guard.h", "logdefs.h"]
  static void
  call(Rcu_item *i, bool (*cb)(Rcu_item *));
  
#line 496 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  static inline bool FIASCO_WARN_RESULT
  process_callbacks();
  
#line 501 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  static inline bool FIASCO_WARN_RESULT
  process_callbacks(Cpu_number cpu);
  
#line 506 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  static inline bool
  pending(Cpu_number cpu);
  
#line 513 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  static inline bool
  idle(Cpu_number cpu);
  
#line 521 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  static inline void
  inc_q_cnt(Cpu_number cpu);
  
#line 526 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  static void
  schedule_callbacks(Cpu_number cpu, Unsigned64 clock);
  
#line 535 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  static inline Rcu::Lock *
  lock();
  
#line 541 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  static inline bool
  do_pending_work(Cpu_number cpu);
};
#line 146 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"

// ------------------------------------------------------------------------

#line 170 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"


// --------------------------------------------------------------------------

#line 177 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 192 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
#include "cpu_lock.h"
#line 193 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
#include "globals.h"
#line 194 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
#include "lock_guard.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 233 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"


/**
 * \brief Enqueue Rcu_item into the list (at the tail).
 * \prarm i the RCU item to enqueue.
 */
inline void Rcu_list::enqueue(Rcu_item *i){ push_back(i); }

#line 240 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"

/**
 * \pre must run under cpu lock
 */

inline void
Rcu_data::enqueue(Rcu_item *i)
{
  _n.enqueue(i);
  ++_len;
}

#line 468 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"


inline bool
Rcu_data::pending(Rcu_glbl *rgp) const
{
  // The CPU has pending RCU callbacks and the grace period for them
  // has been completed.
  if (!_c.empty() && rgp->_completed >= _batch)
    return 1;

  // The CPU has no pending RCU callbacks, however there are new callbacks
  if (_c.empty() && !_n.empty())
    return 1;

  // The CPU has callbacks to be invoked finally
  if (!_d.empty())
    return 1;

  // RCU waits for a quiescent state from the CPU
  if ((_q_batch != rgp->_current) || _pending)
    return 1;

  // OK, no RCU work to do
  return 0;

}

#line 316 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"


inline void
Rcu::enter_idle(Cpu_number cpu)
{
  Rcu_data *rdp = &_rcu_data.cpu(cpu);
  rdp->enter_idle(rcu());
}

#line 324 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"


inline void
Rcu::leave_idle(Cpu_number cpu)
{
  Rcu_data *rdp = &_rcu_data.cpu(cpu);
  if (EXPECT_FALSE(rdp->_idle))
    {
      rdp->_idle = false;
      auto guard = lock_guard(rcu()->_lock);
      rcu()->_active_cpus.set(cpu);
      rdp->_q_batch = Rcu::rcu()->_current;
    }
}

#line 494 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"


inline bool FIASCO_WARN_RESULT
Rcu::process_callbacks()
{ return _rcu_data.current().process_callbacks(&_rcu); }

#line 499 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"


inline bool FIASCO_WARN_RESULT
Rcu::process_callbacks(Cpu_number cpu)
{ return _rcu_data.cpu(cpu).process_callbacks(&_rcu); }

#line 504 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"


inline bool
Rcu::pending(Cpu_number cpu)
{
  return _rcu_data.cpu(cpu).pending(&_rcu);
}

#line 511 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"


inline bool
Rcu::idle(Cpu_number cpu)
{
  Rcu_data const *d = &_rcu_data.cpu(cpu);
  return d->_c.empty() && !d->pending(&_rcu);
}

#line 519 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"


inline void
Rcu::inc_q_cnt(Cpu_number cpu)
{ _rcu_data.cpu(cpu)._q_passed = 1; }

#line 533 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"


inline Rcu::Lock *
Rcu::lock()
{ return &cpu_lock; }

#line 538 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"



inline bool
Rcu::do_pending_work(Cpu_number cpu)
{
  if (pending(cpu))
    {
      inc_q_cnt(cpu);
      return process_callbacks(cpu);
    }
  return false;
}

#endif // rcupdate_h
