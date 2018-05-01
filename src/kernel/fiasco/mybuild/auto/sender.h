// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef sender_h
#define sender_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"

#include "l4_types.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"
#include "prio_list.h"

//
// INTERFACE definition follows 
//

#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"

class Receiver;
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"

/** A sender.  This is a role class, so real senders need to inherit from it.
 */
class Sender : private Prio_list_elem
{
  MEMBER_OFFSET();
public:
  /** Receiver-ready callback.  Receivers make sure to call this
      function on waiting senders when they get ready to receive a
      message from that sender.  Senders need to overwrite this interface. */
  virtual void ipc_send_msg(Receiver *) = 0;
  virtual void ipc_receiver_aborted() = 0;
  virtual void modify_label(Mword const *todo, int cnt) = 0;

protected:
  Iteratable_prio_list *_wq;

private:

  friend class Jdb;
  friend class Jdb_thread_list;

public:  
#line 58 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"
  /** Current receiver.
      @return receiver this sender is currently trying to send a message to.
   */
  
  inline Iteratable_prio_list *
  wait_queue() const;
  
#line 66 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"
  /** Set current receiver.
      @param receiver the receiver we're going to send a message to
   */
  
  inline void
  set_wait_queue(Iteratable_prio_list *wq);
  
#line 77 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"
  inline unsigned short sender_prio();
  
#line 82 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"
  /** Sender in a queue of senders?.
      @return true if sender has enqueued in a receiver's list of waiting 
              senders
   */
  
  inline bool
  in_sender_list() const;
  
#line 94 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"
  inline bool
  is_head_of(Prio_list const *l) const;
  
#line 100 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"
  static inline Sender *
  cast(Prio_list_elem *e);
  
#line 106 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"
  //PROTECTED inline NEEDS [<cassert>, "cpu_lock.h", "lock_guard.h",
  //                      Sender::replace_node, Sender::tree_insert]
  void sender_enqueue(Prio_list *head, unsigned short prio);
  
#line 116 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"
  //PUBLIC inline NEEDS [<cassert>, "cpu_lock.h", "lock_guard.h",
  //                   Sender::remove_tree_elem, Sender::remove_head]
  
  template< typename P_LIST > void sender_dequeue(P_LIST list);
  
#line 129 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"
  // An special version, only to remove the head
  // this is neccessary if the receiver removes the old know head
  // after an unsuccessful ipc_receiver_ready.
  
  template< typename P_LIST > void sender_dequeue_head(P_LIST list);

protected:  
#line 40 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"
  //
  // state requests/manipulation
  //
  
  /** Optimized constructor.  This constructor assumes that the object storage
      is zero-initialized.
      @param id user-visible thread ID of the sender
      @param ignored an integer argument.  The value doesn't matter and 
                     is used just to distinguish this constructor from the 
  		   default one.
   */
  
  
  explicit inline Sender (int /*ignored*/);
  
#line 146 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"
  template<typename P_LIST > void sender_update_prio(P_LIST list, unsigned short newprio);
  
#line 160 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"
  /** Constructor.
      @param id user-visible thread ID of the sender
   */
  
  inline Sender();
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 32 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"

#include <cassert>
#line 34 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"

#include "atomic.h"
#line 36 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"
#include "cpu_lock.h"
#line 37 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"
#include "lock_guard.h"
#line 38 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"
#include "mem.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 56 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"


/** Current receiver.
    @return receiver this sender is currently trying to send a message to.
 */

inline Iteratable_prio_list *
Sender::wait_queue() const
{ return _wq; }

#line 65 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"

/** Set current receiver.
    @param receiver the receiver we're going to send a message to
 */

inline void
Sender::set_wait_queue(Iteratable_prio_list *wq)
{
  _wq = wq;
}

#line 75 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"


inline unsigned short Sender::sender_prio()
{
  return Prio_list_elem::prio();
}

#line 81 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"

/** Sender in a queue of senders?.
    @return true if sender has enqueued in a receiver's list of waiting 
            senders
 */

inline bool
Sender::in_sender_list() const
{
  return Prio_list_elem::in_list();
}

#line 92 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"


inline bool
Sender::is_head_of(Prio_list const *l) const
{ return l->first() == this; }

#line 97 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"



inline Sender *
Sender::cast(Prio_list_elem *e)
{ return static_cast<Sender*>(e); }

#line 39 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"

//
// state requests/manipulation
//

/** Optimized constructor.  This constructor assumes that the object storage
    is zero-initialized.
    @param id user-visible thread ID of the sender
    @param ignored an integer argument.  The value doesn't matter and 
                   is used just to distinguish this constructor from the 
		   default one.
 */


inline Sender::Sender (int /*ignored*/)
: _wq(0)
{}

#line 159 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"

/** Constructor.
    @param id user-visible thread ID of the sender
 */

inline Sender::Sender()
{}

//
// IMPLEMENTATION of function templates
//


#line 115 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"

//PUBLIC inline NEEDS [<cassert>, "cpu_lock.h", "lock_guard.h",
//                   Sender::remove_tree_elem, Sender::remove_head]

template< typename P_LIST > void Sender::sender_dequeue(P_LIST list)
{

  if (!in_sender_list())
    return;

  auto guard = lock_guard(cpu_lock);
  list->dequeue(this);
}

#line 128 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"

// An special version, only to remove the head
// this is neccessary if the receiver removes the old know head
// after an unsuccessful ipc_receiver_ready.

template< typename P_LIST > void Sender::sender_dequeue_head(P_LIST list)
{

  if (!in_sender_list())
    return;

  auto guard = lock_guard(cpu_lock);

  if (this == list->head())
    list->dequeue(this);
}

#line 144 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/sender.cpp"


template<typename P_LIST > void Sender::sender_update_prio(P_LIST list, unsigned short newprio)
{
  if(EXPECT_FALSE(sender_prio() == newprio))
    return;

  auto guard = lock_guard(cpu_lock);

  if (!in_sender_list())
    return;

  sender_dequeue(list);
  sender_enqueue(list, newprio);
}

#endif // sender_h
