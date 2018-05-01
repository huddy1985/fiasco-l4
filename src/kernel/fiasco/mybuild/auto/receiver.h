// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef receiver_h
#define receiver_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"

#include "context.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
#include "l4_error.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
#include "member_offs.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
#include "timeout.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
#include "prio_list.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
#include "ref_obj.h"

//
// INTERFACE definition follows 
//

#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"

class Syscall_frame;
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
class Sender;
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"


/** A receiver.  This is a role class, and real receiver's must inherit from 
    it.  The protected interface is intended for the receiver, and the public
    interface is intended for the sender.

    The only reason this class inherits from Context is to force a specific 
    layout for Thread.  Otherwise, Receiver could just embed or reference
    a Context.
 */
class Receiver : public Context,  public Ref_cnt_obj
{
  MEMBER_OFFSET();

public:
  enum Rcv_state
  {
    Rs_not_receiving = false,
    Rs_ipc_receive   = true,
    Rs_irq_receive   = true + 1
  };

  enum Abort_state
  {
    Abt_ipc_done,
    Abt_ipc_cancel,
    Abt_ipc_in_progress,
  };

  Rcv_state sender_ok(const Sender* sender) const;

  virtual ~Receiver() = 0;

private:
  // DATA
  Sender const *_partner;         // IPC partner I'm waiting for/involved with
  Syscall_frame *_rcv_regs; // registers used for receive
  Mword _caller;
  Iteratable_prio_list _sender_list;

public:  
#line 83 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
  inline Receiver *
  caller() const;
  
#line 88 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
  inline L4_fpage::Rights
  caller_rights() const;
  
#line 94 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
  inline void
  set_caller(Receiver *caller, L4_fpage::Rights rights);
  
#line 111 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
  // Interface for senders
  
  /** Return a reference to receiver's IPC registers.
      Senders call this function to poke values into the receiver's register set.
      @pre state() & Thread_ipc_receiving_mask
      @return pointer to receiver's IPC registers.
   */
  
  inline Syscall_frame*
  rcv_regs() const;
  
#line 127 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
  /** Head of sender list.
      @return a reference to the receiver's list of senders
   */
  
  inline Iteratable_prio_list *
  sender_list();
  
#line 147 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
  inline void
  set_timeout(Timeout *t);
  
#line 154 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
  inline void
  set_timeout(Timeout *t, Unsigned64 tval);
  
#line 162 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
  inline void
  dequeue_timeout();
  
#line 170 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
  inline void
  enqueue_timeout_again();
  
#line 178 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
  inline void
  reset_timeout();
  
#line 199 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
  /** Set the IPC partner (sender).
      @param partner IPC partner
   */
  
  inline void
  set_partner(Sender* partner);
  
#line 210 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
  inline bool
  in_ipc(Sender *sender);
  
#line 287 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
  inline void
  reset_caller();
  
#line 295 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
  inline void
  vcpu_update_state();
  
#line 333 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
  Receiver::Abort_state
  abort_send(Sender *sender);

protected:  
#line 78 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
  /** Constructor.
      @param thread_lock the lock used for synchronizing access to this receiver
      @param space_context the space context 
   */
  
  inline Receiver();
  
#line 107 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
  /** IPC partner (sender).
      @return sender of ongoing or previous IPC operation
   */
  
  inline Sender const *
  partner() const;
  
#line 137 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
  // MANIPULATORS
  
  
  inline void
  set_rcv_regs(Syscall_frame* regs);
  
#line 189 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
  inline void prepare_receive(Sender *partner, Syscall_frame *regs);
  
#line 196 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
  inline bool prepared() const;

private:  
#line 247 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
  //-----------------------------------------------------------------------------
  // VCPU code:
  
  
  inline Receiver::Rcv_state
  vcpu_async_ipc(Sender const *sender) const;
  
#line 316 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
  static Context::Drq::Result
  handle_remote_abort_send(Drq *, Context *, void *_rq);
};
#line 52 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"

typedef Context_ptr_base<Receiver> Receiver_ptr;

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 58 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
#include <cassert>
#line 64 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
#include "sender.h"
#line 67 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
#include "std_macros.h"
#line 68 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
#include "thread_state.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 81 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"


inline Receiver *
Receiver::caller() const
{ return reinterpret_cast<Receiver*>(_caller & ~0x03UL); }

#line 86 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"


inline L4_fpage::Rights
Receiver::caller_rights() const
{ return L4_fpage::Rights(_caller & 0x3); }

#line 91 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"



inline void
Receiver::set_caller(Receiver *caller, L4_fpage::Rights rights)
{
  Mword nv = Mword(caller) | (cxx::int_value<L4_fpage::Rights>(rights) & 0x3);
  reinterpret_cast<Mword volatile &>(_caller) = nv;
}

#line 109 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"


// Interface for senders

/** Return a reference to receiver's IPC registers.
    Senders call this function to poke values into the receiver's register set.
    @pre state() & Thread_ipc_receiving_mask
    @return pointer to receiver's IPC registers.
 */

inline Syscall_frame*
Receiver::rcv_regs() const
{
  //assert (state () & Thread_ipc_receiving_mask);

  return _rcv_regs;
}

#line 126 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"

/** Head of sender list.
    @return a reference to the receiver's list of senders
 */

inline Iteratable_prio_list *
Receiver::sender_list()
{
  return &_sender_list;
}

#line 145 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"


inline void
Receiver::set_timeout(Timeout *t)
{
  _timeout = t;
}

#line 152 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"


inline void
Receiver::set_timeout(Timeout *t, Unsigned64 tval)
{
  _timeout = t;
  t->set(tval, home_cpu());
}

#line 160 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"


inline void
Receiver::dequeue_timeout()
{
  if (_timeout)
    _timeout->dequeue(_timeout->has_hit());
}

#line 168 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"


inline void
Receiver::enqueue_timeout_again()
{
  if (_timeout && Cpu::online(home_cpu()))
    _timeout->set_again(home_cpu());
}

#line 176 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"


inline void
Receiver::reset_timeout()
{
  if (EXPECT_TRUE(!_timeout))
    return;

  _timeout->reset();
  _timeout = 0;
}

#line 198 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"

/** Set the IPC partner (sender).
    @param partner IPC partner
 */

inline void
Receiver::set_partner(Sender* partner)
{
  _partner = partner;
}

#line 208 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"


inline bool
Receiver::in_ipc(Sender *sender)
{
  return (state() & Thread_receive_in_progress) && (partner() == sender);
}

#line 285 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"


inline void
Receiver::reset_caller()
{
  if (_caller)
    _caller = 0;
}

#line 293 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"


inline void
Receiver::vcpu_update_state()
{
  if (EXPECT_TRUE(!(state() & Thread_vcpu_enabled)))
    return;

  if (sender_list()->empty())
    vcpu_state().access()->sticky_flags &= ~Vcpu_state::Sf_irq_pending;
}

#line 73 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
/** Constructor.
    @param thread_lock the lock used for synchronizing access to this receiver
    @param space_context the space context 
 */

inline Receiver::Receiver()
: Context(), _caller(0)
{}

#line 100 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
/** IPC partner (sender).
    @return sender of ongoing or previous IPC operation
 */

inline Sender const *
Receiver::partner() const
{
  return _partner;
}

#line 136 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"

// MANIPULATORS


inline void
Receiver::set_rcv_regs(Syscall_frame* regs)
{
  _rcv_regs = regs;
}

#line 187 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"


inline void Receiver::prepare_receive(Sender *partner, Syscall_frame *regs)
{
  set_rcv_regs(regs);  // message should be poked in here
  set_partner(partner);
}

#line 194 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"


inline bool Receiver::prepared() const
{ return _rcv_regs; }

#line 69 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"

// Interface for receivers

inline Receiver::~Receiver() {}

#line 246 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"

//-----------------------------------------------------------------------------
// VCPU code:


inline Receiver::Rcv_state
Receiver::vcpu_async_ipc(Sender const *sender) const
{
  if (EXPECT_FALSE(state() & Thread_ipc_mask))
    return Rs_not_receiving;

  Vcpu_state *vcpu = vcpu_state().access();

  if (EXPECT_FALSE(!vcpu_irqs_enabled(vcpu)))
    return Rs_not_receiving;

  Receiver *self = const_cast<Receiver*>(this);

  if (this == current())
    self->spill_user_state();

  if (self->vcpu_enter_kernel_mode(vcpu))
    vcpu = vcpu_state().access();

  LOG_TRACE("VCPU events", "vcpu", this, Vcpu_log,
      l->type = 1;
      l->state = vcpu->_saved_state;
      l->ip = Mword(sender);
      l->sp = regs()->sp();
      l->space = ~0; //vcpu_user_space() ? static_cast<Task*>(vcpu_user_space())->dbg_id() : ~0;
      );

  self->_rcv_regs = &vcpu->_ipc_regs;
  vcpu->_regs.set_ipc_upcall();
  self->set_partner(const_cast<Sender*>(sender));
  self->state_add_dirty(Thread_receive_wait);
  self->vcpu_save_state_and_upcall();
  return Rs_irq_receive;
}

#line 215 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"


/** Return whether the receiver is ready to accept a message from the
    given sender.
    @param sender thread that wants to send a message to this receiver
    @return true if receiver is in correct state to accept a message 
                 right now (open wait, or closed wait and waiting for sender).
 */


inline Receiver::Rcv_state
Receiver::sender_ok(const Sender *sender) const
{
  unsigned ipc_state = state() & Thread_ipc_mask;

  // If Thread_send_in_progress is still set, we're still in the send phase
  if (EXPECT_FALSE(ipc_state != Thread_receive_wait))
    return vcpu_async_ipc(sender);

  // Check open wait; test if this sender is really the first in queue
  if (EXPECT_TRUE(!partner()
                  && (_sender_list.empty()
		    || sender->is_head_of(&_sender_list))))
    return Rs_ipc_receive;

  // Check closed wait; test if this sender is really who we specified
  if (EXPECT_TRUE(sender == partner()))
    return Rs_ipc_receive;

  return Rs_not_receiving;
}

#endif // receiver_h
