// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef queue_item_h
#define queue_item_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue_item.cpp"

#include <cxx/dlist>

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue_item.cpp"

class Queue;
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue_item.cpp"

class Queue_item : public cxx::D_list_item
{
  friend class Queue;
public:
  enum Status { Ok, Retry, Invalid };

private:
  Queue *_q;

public:  
#line 24 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue_item.cpp"
  inline bool
  queued() const;
  
#line 29 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue_item.cpp"
  inline Queue *
  queue() const;
  
#line 37 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue_item.cpp"
  inline Queue_item::Status
  status() const;
} __attribute__((aligned(16)));
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue_item.cpp"


//--------------------------------------------------------------------------


//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue_item.cpp"

#include "assert.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 22 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue_item.cpp"


inline bool
Queue_item::queued() const
{ return cxx::D_list_cyclic<Queue_item>::in_list(this); }

#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue_item.cpp"


inline Queue *
Queue_item::queue() const
{
  assert (queued());
  return _q;
}

#line 35 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/queue_item.cpp"


inline Queue_item::Status
Queue_item::status() const
{
  assert (!queued());
  return Status((unsigned long)_q);
}

#endif // queue_item_h
