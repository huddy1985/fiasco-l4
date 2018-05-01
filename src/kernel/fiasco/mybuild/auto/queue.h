// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef queue_h
#define queue_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"

#include "spin_lock.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"
#include "queue_item.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"
#include "assert.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"
#include <cxx/dlist>

//
// INTERFACE definition follows 
//

#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"

class Queue
{
public:
  typedef Spin_lock_coloc<Mword> Inner_lock;

private:
  class Lock_n_ptr : public Inner_lock
  {
  public:
    Queue_item *item() const
    { return reinterpret_cast<Queue_item*>(get_unused() & ~5UL); }

    void set_item(Queue_item *i)
    {
      assert (!(Mword(i) & 5));
      set_unused((Mword)i | (get_unused() & 5));
    }

    bool blocked() const
    { return get_unused() & 1; }

    void block()
    { return set_unused(get_unused() | 1); }

    void unblock()
    { set_unused(get_unused() & ~1); }

    bool invalid() const
    { return get_unused() & 4; }

    void invalidate()
    { set_unused(get_unused() | 4); }
  };

  struct Queue_head_policy
  {
    typedef Lock_n_ptr Head_type;
    static Queue_item *head(Head_type const &h) { return h.item(); }
    static void set_head(Head_type &h, Queue_item *v) { h.set_item(v); }
  };

  typedef cxx::Sd_list<Queue_item, cxx::D_list_item_policy, Queue_head_policy> List;

  List _m;

public:  
#line 62 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"
  inline Queue();
  
#line 66 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"
  inline Queue::Inner_lock *
  q_lock();
  
#line 71 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"
  inline void
  enqueue(Queue_item *i);
  
#line 82 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"
  inline bool
  dequeue(Queue_item *i, Queue_item::Status reason);
  
#line 97 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"
  inline Queue_item *
  first() const;
  
#line 102 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"
  inline bool
  blocked() const;
  
#line 107 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"
  inline void
  block();
  
#line 115 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"
  inline void
  unblock();
  
#line 123 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"
  inline bool
  invalid() const;
  
#line 131 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"
  inline void
  invalidate();
};
#line 53 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"


//--------------------------------------------------------------------------


//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 57 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"

#include "assert.h"
#line 59 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"
#include "std_macros.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 60 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"


inline Queue::Queue()
{ _m.head().init(); }

#line 64 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"


inline Queue::Inner_lock *
Queue::q_lock()
{ return &_m.head(); }

#line 69 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"


inline void
Queue::enqueue(Queue_item *i)
{
  // Queue i at the end of the list
  assert (i && !i->queued());
  assert (_m.head().test());
  i->_q = this;
  _m.push_back(i);
}

#line 80 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"


inline bool
Queue::dequeue(Queue_item *i, Queue_item::Status reason)
{
  assert (_m.head().test());
  assert (i->queued());

  if (EXPECT_FALSE(i->_q != this))
    return false;

  _m.remove(i);
  i->_q = (Queue*)reason;
  return true;
}

#line 95 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"


inline Queue_item *
Queue::first() const
{ return _m.front(); }

#line 100 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"


inline bool
Queue::blocked() const
{ return _m.head().blocked(); }

#line 105 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"


inline void
Queue::block()
{
  assert (_m.head().test());
  _m.head().block();
}

#line 113 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"


inline void
Queue::unblock()
{
  assert (_m.head().test());
  _m.head().unblock();
}

#line 121 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"


inline bool
Queue::invalid() const
{
  assert (_m.head().test());
  return _m.head().invalid();
}

#line 129 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue.cpp"


inline void
Queue::invalidate()
{
  assert (_m.head().test());
  _m.head().invalidate();
}

#endif // queue_h
