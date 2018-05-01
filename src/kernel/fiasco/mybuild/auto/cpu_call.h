// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef cpu_call_h
#define cpu_call_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_call.cpp"

#include "mem.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_call.cpp"
#include "cpu_mask.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_call.cpp"
#include "queue.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_call.cpp"
#include "queue_item.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_call.cpp"
#include "per_cpu_data.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_call.cpp"
#include "processor.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_call.cpp"
#include <cxx/function>

//
// INTERFACE definition follows 
//

#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_call.cpp"

class Cpu_call_queue;
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_call.cpp"

class Cpu_call : private Queue_item
{
  friend class Cpu_call_queue;

private:
  cxx::functor<bool (Cpu_number cpu)> _func;
  Mword _wait;

public:
  template< typename Functor >
  Cpu_call(Functor &&f)
  : _func(f), _wait(false) {}

  Cpu_call(cxx::functor<bool (Cpu_number)> &&f)
  : _func(f), _wait(false) {}

  Cpu_call() : _func(), _wait(false) {}

  void set(cxx::functor<bool (Cpu_number)> &f)
  { _func = f; }

  void set_queued()
  { _wait = true; }

  void done()
  {
    Mem::mp_mb();
    write_now(&_wait, (Mword)false);
  }

  bool run(Cpu_number cpu, bool done = true)
  {
    bool res = _func(cpu);
    if (done)
      this->done();
    return res;
  }

  bool is_done(bool async) const
  {
    if (!async)
      return !access_once(&_wait);

    Mem::mp_mb();
    return !queued();
  }

  bool remote_call(Cpu_number cpu, bool async);

public:  
#line 172 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_call.cpp"
  static inline bool
  cpu_call_many(Cpu_mask const &m,
                          cxx::functor<bool (Cpu_number)> &&func,
                          bool = false);
  
#line 182 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_call.cpp"
  static bool handle_global_requests();
};
#line 62 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_call.cpp"

template<unsigned MAX>
class Cpu_calls
{
  Cpu_calls(Cpu_calls const &) = delete;
  Cpu_calls &operator = (Cpu_calls const &) = delete;

public:
  enum { Max = Config::Max_num_cpus < MAX ?  Config::Max_num_cpus : MAX };
  Cpu_calls() : _used(0) {}

  Cpu_call *next()
  {
    if (_used < Max)
      return &_cs[_used++];
    return 0;
  }

  Cpu_call *find_done(bool async)
  {
    for (unsigned i = 0; i < _used; ++i)
      if (_cs[i].is_done(async))
        return &_cs[i];

    return 0;
  }

  void wait_all(bool async)
  {
    for (unsigned i = 0; i < _used; ++i)
      while (!_cs[i].is_done(async))
        Proc::pause();
  }

  unsigned char used() const { return _used; }

private:
  Cpu_call _cs[Max];
  unsigned char _used;
};
#line 102 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_call.cpp"

class Cpu_call_queue : public Queue
{
public:
  void enq(Cpu_call *rq);
  bool dequeue(Cpu_call *drq, Queue_item::Status reason);
  bool handle_requests();
  bool execute_request(Cpu_call *r);
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 114 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_call.cpp"

#include "assert.h"
#line 116 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_call.cpp"
#include "globals.h"
#line 117 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_call.cpp"
#include "lock_guard.h"
#line 118 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_call.cpp"
#include "mem.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 170 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_call.cpp"


inline bool
Cpu_call::cpu_call_many(Cpu_mask const &m,
                        cxx::functor<bool (Cpu_number)> &&func,
                        bool)
{
  if (m.get(current_cpu()))
    func(current_cpu());
  return true;
}

#line 119 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_call.cpp"


inline void
Cpu_call_queue::enq(Cpu_call *rq)
{
  assert(cpu_lock.test());
  auto guard = lock_guard(q_lock());
  enqueue(rq);
}

#line 128 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_call.cpp"


inline bool
Cpu_call_queue::execute_request(Cpu_call *r)
{
  return r->run(current_cpu(), true);
}

#line 135 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_call.cpp"


inline bool
Cpu_call_queue::dequeue(Cpu_call *r, Queue_item::Status reason)
{
  auto guard = lock_guard(q_lock());
  if (!r->queued())
    return false;
  return Queue::dequeue(r, reason);
}

#line 145 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_call.cpp"


inline bool
Cpu_call_queue::handle_requests()
{
  bool need_resched = false;
  while (1)
    {
      Queue_item *qi;
        {
          auto guard = lock_guard(q_lock());
          qi = first();
          if (!qi)
            return need_resched;

          check (Queue::dequeue(qi, Queue_item::Ok));
        }

      Cpu_call *r = static_cast<Cpu_call*>(qi);
      need_resched |= execute_request(r);
    }
}

#endif // cpu_call_h
