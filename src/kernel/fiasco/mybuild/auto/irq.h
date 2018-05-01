// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef irq_h
#define irq_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"

#include "ipc_sender.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
#include "irq_chip.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
#include "kobject_helper.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
#include "member_offs.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
#include "sender.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
#include "context.h"

//
// INTERFACE definition follows 
//

#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"

class Ram_quota;
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
class Thread;
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


/** Hardware interrupts.  This class encapsulates handware IRQs.  Also,
    it provides a registry that ensures that only one receiver can sign up
    to receive interrupt IPC messages.
 */
class Irq : public Irq_base, public cxx::Dyn_castable<Irq, Kobject>
{
  MEMBER_OFFSET();
  typedef Slab_cache Allocator;

public:
  enum Op
  {
    Op_eoi_1      = 0, // Irq_sender + Irq_semaphore
    Op_compat_attach     = 1,
    Op_trigger    = 2, // Irq_sender + Irq_mux + Irq_semaphore
    Op_compat_chain      = 3,
    Op_eoi_2      = 4, // Icu + Irq_sender + Irq_semaphore
    Op_compat_detach     = 5,
  };

protected:
  Ram_quota *_q;
  Context::Drq _drq;

public:  
#line 795 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  inline void *
  operator new (size_t, void *p);
  
#line 800 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  void
  operator delete (void *_l);
  
#line 812 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  template<typename T> static inline T*
  allocate(Ram_quota *q);
  
#line 824 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  explicit inline Irq(Ram_quota *q = 0);
  
#line 827 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  void
  destroy(Kobject ***rl);

protected:  
#line 141 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  inline int
  get_irq_opcode(L4_msg_tag tag, Utcb const *utcb);
  
#line 153 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  inline L4_msg_tag
  dispatch_irq_proto(Unsigned16 op, bool may_unmask);

private:  
#line 790 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  static Irq::Allocator *
  allocator();
};
#line 38 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


/**
 * IRQ Kobject to send IPC messages to a receiving thread.
 */
class Irq_sender
: public Kobject_h<Irq_sender, Irq>,
  public Ipc_sender<Irq_sender>
{
public:
  enum Op {
    Op_attach = 0,
    Op_detach = 1,
    Op_bind     = 0x10,
  };

protected:
  static Thread *detach_in_progress()
  { return reinterpret_cast<Thread *>(1); }

  static bool is_valid_thread(Thread const *t)
  { return t > detach_in_progress(); }

  Smword _queued;
  Thread *_irq_thread;

private:
  Mword _irq_id;

public:  
#line 348 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  /**
   * Bind a receiver to this device interrupt.
   * \param t           the receiver that wants to receive IPC messages for this
   *                    IRQ
   * \param rl[in,out]  the list of objects that have to be destroyed. The
   *                    operation might append objects to this list if it is in
   *                    charge of deleting the old receiver that used to be
   *                    attached to this IRQ.
   *
   * \retval 0        on success, `t` is the new IRQ handler thread
   * \retval -EINVAL  if `t` is not a valid thread.
   * \retval -EBUSY   if another detach operation is in progress.
   */
  
  inline int
  alloc(Thread *t, Kobject ***rl);
  
#line 422 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  Receiver *
  owner() const;
  
#line 471 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  explicit Irq_sender(Ram_quota *q = 0);
  
#line 478 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  void
  switch_mode(bool is_edge_triggered);
  
#line 485 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  void
  destroy(Kobject ***rl);
  
#line 517 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  inline int
  queued();
  
#line 524 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  /**
   * Predicate used to figure out if the sender shall be enqueued
   * for sending a second message after sending the first.
   */
  
  inline bool
  requeue_sender();
  
#line 533 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  /**
   * Predicate used to figure out if the sender shall be deqeued after
   * sending the request.
   */
  
  inline bool
  dequeue_sender();
  
#line 543 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  inline Syscall_frame *
  transfer_msg(Receiver *recv);
  
#line 557 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  void
  modify_label(Mword const *todo, int cnt);
  
#line 624 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  inline void
  _hit_level_irq(Upstream_irq const *ui);
  
#line 649 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  inline void
  _hit_edge_irq(Upstream_irq const *ui);
  
#line 735 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  L4_msg_tag
  kinvoke(L4_obj_ref, L4_fpage::Rights /*rights*/, Syscall_frame *f,
                      Utcb const *utcb, Utcb *);
  
#line 778 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  Mword
  obj_id() const;

private:  
#line 425 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  /**
   * Release an interrupt.
   * \param rl[in,out]  The list of objects that have to be destroyed.
   *                    The operation might append objects to this list if it is
   *                    in charge of deleting the receiver that used to be
   *                    attached to this IRQ.
   *
   * \retval 0        on success.
   * \retval -ENOENT  if there was no receiver attached.
   * \retval -EBUSY   when there is another detach operation in progress.
   */
  
  int
  free(Kobject ***rl);
  
#line 494 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  /** Consume one interrupt.
      @return number of IRQs that are still pending.
   */
  
  inline Smword
  consume();
  
#line 577 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  static Context::Drq::Result
  handle_remote_hit(Context::Drq *, Context *target, void *arg);
  
#line 596 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  inline Smword
  queue();
  
#line 608 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  inline void
  send();
  
#line 644 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  static void
  hit_level_irq(Irq_base *i, Upstream_irq const *ui);
  
#line 678 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  static void
  hit_edge_irq(Irq_base *i, Upstream_irq const *ui);
  
#line 684 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  L4_msg_tag
  sys_attach(L4_msg_tag tag, Utcb const *utcb,
                         Syscall_frame *);
  
#line 721 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  L4_msg_tag
  sys_detach();
};
#line 67 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


/**
 * IRQ Kobject to broadcast IRQs to multiple other IRQ objects.
 *
 * This is useful for PCI shared IRQs.
 */
class Irq_muxer : public Kobject_h<Irq_muxer, Irq>, private Irq_chip
{
public:
  enum Ops {
    Op_chain = 0
  };

  int set_mode(Mword, Irq_chip::Mode) { return 0; }
  bool is_edge_triggered(Mword) const { return false; }
  void switch_mode(bool)
  {
    // the irq object is assumed to be always handled as
    // level triggered
  }

  void set_cpu(Mword, Cpu_number)
  {
    // don't know what to do here, may be multiple targets on different
    // CPUs!
  }

  void ack(Mword) {}

  char const *chip_type() const { return "Bcast"; }

private:
  Smword _mask_cnt;
  Spin_lock<> _mux_lock;

public:  
#line 175 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  void
  unmask(Mword);
  
#line 189 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  void
  mask(Mword);
  
#line 203 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  void
  unbind(Irq_base *irq);
  
#line 227 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  void
  mask_and_ack(Mword);
  
#line 232 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  inline void
  handle(Upstream_irq const *ui);
  
#line 266 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  explicit Irq_muxer(Ram_quota *q = 0);
  
#line 274 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  void
  destroy(Kobject ***rl);
  
#line 318 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  L4_msg_tag
  kinvoke(L4_obj_ref, L4_fpage::Rights /*rights*/, Syscall_frame *f,
                     Utcb const *utcb, Utcb *);

private:  
#line 288 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
  L4_msg_tag
  sys_attach(L4_msg_tag tag, Utcb const *utcb, Syscall_frame *);
};
#line 103 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"

//-----------------------------------------------------------------------------


//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 108 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
#include "atomic.h"
#line 110 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
#include "cpu_lock.h"
#line 116 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"
#include "lock_guard.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 793 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


inline void *
Irq::operator new (size_t, void *p)
{ return p; }

#line 809 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"

 

template<typename T> inline T*
Irq::allocate(Ram_quota *q)
{
  void *nq =allocator()->q_alloc(q);
  if (nq)
    return new (nq) T(q);

  return 0;
}

#line 821 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"



inline Irq::Irq(Ram_quota *q) : _q(q) {}

#line 139 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


inline int
Irq::get_irq_opcode(L4_msg_tag tag, Utcb const *utcb)
{
  if (tag.proto() == L4_msg_tag::Label_irq && tag.words() == 0)
    return Op_trigger;
  if (EXPECT_FALSE(tag.words() < 1))
    return -1;

  return access_once(utcb->values) & 0xffff;
}

#line 151 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


inline L4_msg_tag
Irq::dispatch_irq_proto(Unsigned16 op, bool may_unmask)
{
  switch (op)
    {
    case Op_eoi_1:
    case Op_eoi_2:
      if (may_unmask)
        unmask();
      return L4_msg_tag(L4_msg_tag::Schedule); // no reply

    case Op_trigger:
      log();
      hit(0);
      return L4_msg_tag(L4_msg_tag::Schedule); // no reply

    default:
      return commit_result(-L4_err::ENosys);
    }
}

#line 347 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"

/**
 * Bind a receiver to this device interrupt.
 * \param t           the receiver that wants to receive IPC messages for this
 *                    IRQ
 * \param rl[in,out]  the list of objects that have to be destroyed. The
 *                    operation might append objects to this list if it is in
 *                    charge of deleting the old receiver that used to be
 *                    attached to this IRQ.
 *
 * \retval 0        on success, `t` is the new IRQ handler thread
 * \retval -EINVAL  if `t` is not a valid thread.
 * \retval -EBUSY   if another detach operation is in progress.
 */

inline int
Irq_sender::alloc(Thread *t, Kobject ***rl)
{
  if (t == nullptr)
    return -L4_err::EInval;

  Thread *old;
  for (;;)
    {
      old = access_once(&_irq_thread);

      if (old == t)
        return 0;

      if (EXPECT_FALSE(old == detach_in_progress()))
        return -L4_err::EBusy;

      if (mp_cas(&_irq_thread, old, t))
        break;
    }

  Mem::mp_acquire();

  auto g = lock_guard(cpu_lock);
  bool reinject = false;

  if (is_valid_thread(old))
    {
      switch (old->Receiver::abort_send(this))
        {
        case Receiver::Abt_ipc_done:
          break; // was not queued

        case Receiver::Abt_ipc_cancel:
          reinject = true;
          break;

        default:
          // this must not happen as this is only the case
          // for IPC including message items and an IRQ never
          // sends message items.
          panic("IRQ IPC flagged as in progress");
        }

      old->put_n_reap(rl);
    }

  t->inc_ref();
  if (Cpu::online(t->home_cpu()))
    _chip->set_cpu(pin(), t->home_cpu());

  if (old == nullptr)
    _queued = 0;
  else if (reinject)
    send();

  return 0;
}

#line 515 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


inline int
Irq_sender::queued()
{
  return _queued;
}

#line 492 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


/** Consume one interrupt.
    @return number of IRQs that are still pending.
 */

inline Smword
Irq_sender::consume()
{
  Smword old;

  do
    {
      old = _queued;
    }
  while (!mp_cas (&_queued, old, old - 1));
  Mem::mp_acquire();

  if (old == 2 && hit_func == &hit_edge_irq)
    unmask();

  return old - 1;
}

#line 522 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


/**
 * Predicate used to figure out if the sender shall be enqueued
 * for sending a second message after sending the first.
 */

inline bool
Irq_sender::requeue_sender()
{ return consume() > 0; }

#line 532 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"

/**
 * Predicate used to figure out if the sender shall be deqeued after
 * sending the request.
 */

inline bool
Irq_sender::dequeue_sender()
{ return consume() < 1; }

#line 541 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


inline Syscall_frame *
Irq_sender::transfer_msg(Receiver *recv)
{
  Syscall_frame* dst_regs = recv->rcv_regs();

  // set ipc return value: OK
  dst_regs->tag(L4_msg_tag(0));

  // set ipc source thread id
  dst_regs->from(_irq_id);

  return dst_regs;
}

#line 605 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"



inline void
Irq_sender::send()
{
  auto t = access_once(&_irq_thread);
  if (EXPECT_FALSE(!is_valid_thread(t)))
    return;

  if (EXPECT_FALSE(t->home_cpu() != current_cpu()))
    t->drq(&_drq, handle_remote_hit, this,
           Context::Drq::Target_ctxt, Context::Drq::No_wait);
  else
    send_msg(t, true);
}

#line 594 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


inline Smword
Irq_sender::queue()
{
  Smword old;
  do
    old = _queued;
  while (!mp_cas(&_queued, old, old + 1));
  return old;
}

#line 621 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"



inline void
Irq_sender::_hit_level_irq(Upstream_irq const *ui)
{
  // We're entered holding the kernel lock, which also means irqs are
  // disabled on this CPU (XXX always correct?).  We never enable irqs
  // in this stack frame (except maybe in a nonnested invocation of
  // switch_exec() -> switchin_context()) -- they will be re-enabled
  // once we return from it (iret in entry.S:all_irqs) or we switch to
  // a different thread.

  // LOG_MSG_3VAL(current(), "IRQ", dbg_id(), 0, _queued);

  assert (cpu_lock.test());
  mask_and_ack();
  ui->ack();
  if (queue() == 0)
    send();
}

#line 647 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


inline void
Irq_sender::_hit_edge_irq(Upstream_irq const *ui)
{
  // We're entered holding the kernel lock, which also means irqs are
  // disabled on this CPU (XXX always correct?).  We never enable irqs
  // in this stack frame (except maybe in a nonnested invocation of
  // switch_exec() -> switchin_context()) -- they will be re-enabled
  // once we return from it (iret in entry.S:all_irqs) or we switch to
  // a different thread.

  // LOG_MSG_3VAL(current(), "IRQ", dbg_id(), 0, _queued);

  assert (cpu_lock.test());
  Smword q = queue();

  // if we get a second edge triggered IRQ before the first is
  // handled we can mask the IRQ.  The consume function will
  // unmask the IRQ when the last IRQ is dequeued.
  if (!q)
    ack();
  else
    mask_and_ack();

  ui->ack();
  if (q == 0)
    send();
}

#line 230 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq.cpp"


inline void
Irq_muxer::handle(Upstream_irq const *ui)
{
  assert (cpu_lock.test());
  Irq_base::mask_and_ack();
  ui->ack();

  if (EXPECT_FALSE (!Irq_base::_next))
    return;

  int irqs = 0;
  for (Irq_base *n = Irq_base::_next; n;)
    {
      ++irqs;
      n->__mask();
      n = n->Irq_base::_next;
    }

    {
      Smword old;
      do
	old = _mask_cnt;
      while (!mp_cas(&_mask_cnt, old, old + irqs));
    }

  for (Irq_base *n = Irq_base::_next; n;)
    {
      Irq *i = nonull_static_cast<Irq*>(n);
      i->hit(0);
      n = i->Irq_base::_next;
    }
}

#endif // irq_h
