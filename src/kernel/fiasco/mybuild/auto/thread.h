// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef thread_h
#define thread_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"

#include "l4_types.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "config.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "continuation.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "helping_lock.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "irq_chip.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "kobject.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "mem_layout.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "member_offs.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "receiver.h"
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "ref_obj.h"
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "sender.h"
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "spin_lock.h"
#line 1011 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"

#include "tb_entry.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

#include "trap_state.h"
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"

#include "tb_entry.h"
#line 24 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"

#include "l4_buf_iter.h"
#line 26 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
#include "l4_error.h"
#line 82 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"

#include "tb_entry.h"
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-debug.cpp"

#include "tb_entry.h"

//
// INTERFACE definition follows 
//

#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"

class Return_frame;
#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
class Syscall_frame;
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
class Task;
#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
class Thread;
#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
class Vcpu_state;
#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
class Irq_base;
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

class Idt_entry;
#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"

class Syscall_frame;
#line 22 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"

typedef Context_ptr_base<Thread> Thread_ptr;
#line 24 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"

/** A thread.  This class is the driver class for most kernel functionality.
 */
class Thread :
  public Receiver,
  public Sender,
  public cxx::Dyn_castable<Thread, Kobject>
{
  MEMBER_OFFSET();

  friend class Jdb;
  friend class Jdb_bt;
  friend class Jdb_tcb;
  friend class Jdb_thread;
  friend class Jdb_thread_list;
  friend class Jdb_list_threads;
  friend class Jdb_list_timeouts;
  friend class Jdb_tbuf_show;

public:
  enum Context_mode_kernel { Kernel = 0 };
  enum Operation
  {
    Opcode_mask = 0xffff,
    Op_control = 0,
    Op_ex_regs = 1,
    Op_switch  = 2,
    Op_stats   = 3,
    Op_vcpu_resume = 4,
    Op_register_del_irq = 5,
    Op_modify_senders = 6,
    Op_vcpu_control = 7,
    Op_gdt_x86 = 0x10,
    Op_set_tpidruro_arm = 0x10,
    Op_set_segment_base_amd64 = 0x12,
    Op_segment_info_amd64 = 0x13,
  };

  enum Control_flags
  {
    Ctl_set_pager       = 0x0010000,
    Ctl_bind_task       = 0x0200000,
    Ctl_alien_thread    = 0x0400000,
    Ctl_ux_native       = 0x0800000,
    Ctl_set_exc_handler = 0x1000000,
  };

  enum Ex_regs_flags
  {
    Exr_cancel            = 0x10000,
    Exr_trigger_exception = 0x20000,
  };

  enum Vcpu_ctl_flags
  {
    Vcpu_ctl_extended_vcpu = 0x10000,
  };

  class Dbg_stack
  {
  public:
    enum { Stack_size = Config::PAGE_SIZE };
    void *stack_top;
    Dbg_stack();
  };

  static Per_cpu<Dbg_stack> dbg_stack;

public:
  typedef void (Utcb_copy_func)(Thread *sender, Thread *receiver);

  /**
   * Constructor.
   *
   * @post state() != 0.
   */
  explicit Thread(Ram_quota *);

  int handle_page_fault(Address pfa, Mword error, Mword pc,
                        Return_frame *regs);

private:
  struct Migration_helper_info
  {
    Migration *inf;
    Thread *victim;
  };

  void *operator new(size_t);	///< Default new operator undefined

  bool handle_sigma0_page_fault (Address pfa);

  /**
   * Return to user.
   *
   * This function is the default routine run if a newly
   * initialized context is being switch_exec()'ed.
   */
  static void user_invoke();

public:
  static bool pagein_tcb_request(Return_frame *regs);

  inline Mword user_ip() const;
  inline void user_ip(Mword);

  inline Mword user_sp() const;
  inline void user_sp(Mword);

  inline Mword user_flags() const;

  /** nesting level in debugger (always critical) if >1 */
  static Per_cpu<unsigned long> nested_trap_recover;
  static void handle_remote_requests_irq() asm ("handle_remote_cpu_requests");
  static void handle_global_remote_requests_irq() asm ("ipi_remote_call");

  bool arch_ext_vcpu_enabled();

protected:
  explicit Thread(Ram_quota *, Context_mode_kernel);

  // More ipc state
  Thread_ptr _pager;
  Thread_ptr _exc_handler;

protected:
  Ram_quota *_quota;
  Irq_base *_del_observer;


  // Debugging facilities
  unsigned _magic;
  static const unsigned magic = 0xf001c001;

#line 1013 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
private:

protected:
  struct Migration_log : public Tb_entry
  {
    Mword    state;
    Address  user_ip;
    Cpu_number src_cpu;
    Cpu_number target_cpu;

    void print(String_buffer *) const;
  };

#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
private:

private:
  /**
   * Return code segment used for exception reflection to user mode
   */
  static Mword exception_cs();

protected:
  static Trap_state::Handler nested_trap_handler FIASCO_FASTCALL;

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
private:

protected:
  struct Log_pf_invalid : public Tb_entry
  {
    Mword pfa;
    Cap_index cap_idx;
    Mword err;
    void print(String_buffer *buf) const;
  };

  struct Log_exc_invalid : public Tb_entry
  {
    Cap_index cap_idx;
    void print(String_buffer *buf) const;
  };

#line 29 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
private:

protected:
  enum class Check_sender
  {
    Ok = 0,
    Queued = 2,
    Done = 4,
    Failed = 1,
  };

  struct Ipc_remote_request
  {
    L4_msg_tag tag;
    Thread *partner;
    Syscall_frame *regs;
    L4_fpage::Rights rights;
    bool timeout;
    bool have_rcv;

    Thread::Check_sender result;
  };

  Syscall_frame *_snd_regs;
  L4_fpage::Rights _ipc_send_rights;

#line 84 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
private:

protected:
  static unsigned log_fmt_pf_invalid(Tb_entry *, int max, char *buf) asm ("__fmt_page_fault_invalid_pager");
  static unsigned log_fmt_exc_invalid(Tb_entry *, int max, char *buf) asm ("__fmt_exception_invalid_handler");

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-debug.cpp"
private:

protected:
  struct Log_thread_exregs : public Tb_entry
  {
    Mword       id, ip, sp, op;
    void print(String_buffer *) const;
  };

#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-dbf.cpp"
private:

private:
  static void handle_double_fault (void) asm ("thread_handle_double_fault");

public:
  static bool may_enter_jdb;

#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-vcpu.cpp"
private:

protected:
  void arch_init_vcpu_state(Vcpu_state *vcpu_state, bool ext);

public:  
#line 197 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  inline void *
  operator new(size_t, Ram_quota *q) throw ();
  
#line 208 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  bool
  bind(Task *t, User<Utcb>::Ptr utcb);
  
#line 236 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  inline bool
  unbind();
  
#line 286 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  /** Destructor.  Reestablish the Context constructor's precondition.
      @pre current() == thread_lock()->lock_owner()
           && state() == Thread_dead
      @pre lock_cnt() == 0
      @post (_kernel_sp == 0)  &&  (* (stack end) == 0)  &&  !exists()
   */
  
  virtual ~Thread();		// To be called in locked state.
  
  
#line 334 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  inline void
  ipc_gate_deleted(Mword id);
  
#line 344 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  void
  register_delete_irq(Irq_base *irq);
  
#line 353 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  void
  remove_delete_irq();
  
#line 375 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  inline bool
  exception_triggered() const;
  
#line 380 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  inline bool
  continuation_test_and_restore();
  
#line 389 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  //
  // state requests/manipulation
  //
  
  
  inline void
  handle_timer_interrupt();
  
#line 415 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  void
  halt();
  
#line 429 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  static void
  halt_current();
  
#line 467 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  static Context::Drq::Result
  handle_kill_helper(Drq *src, Context *, void *);
  
#line 479 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  void
  put_n_reap(Kobject ***reap_list);
  
#line 622 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  void
  set_sched_params(L4_sched_param const *p);
  
#line 642 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  long
  control(Thread_ptr const &pager, Thread_ptr const &exc_handler);
  
#line 659 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  // used by UX only
  
  static inline bool
  is_tcb_address(Address a);
  
#line 669 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  static inline void
  assert_irq_entry();
  
#line 676 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  // ---------------------------------------------------------------------------
  
  
  inline bool
  check_sys_ipc(unsigned flags, Thread **partner, Thread **sender,
                        bool *have_recv) const;
  
#line 704 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  static Context::Drq::Result
  handle_migration_helper(Drq *rq, Context *, void *p);
  
#line 763 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  bool
  initiate_migration() override;
  
#line 781 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  void
  finish_migration() override;
  
#line 792 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  /*
   * Handle FPU trap for this context. Assumes disabled interrupts
   */
  
  inline int
  switchin_fpu(bool alloc_new_fpu = true);
  
#line 829 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  inline void
  transfer_fpu(Thread *to); //, Trap_state *trap_state, Utcb *to_utcb)
  
  
#line 982 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  void
  migrate(Migration *info);
  
#line 1298 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  static void FIASCO_NORETURN
  system_abort();
  
#line 161 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
  /**
   * The global trap handler switch.
   * This function handles CPU-exception reflection, int3 debug messages,
   * kernel-debugger invocation, and thread crashes (if a trap cannot be
   * handled).
   * @param state trap state
   * @return 0 if trap has been consumed by handler;
   *          -1 if trap could not be handled.
   */
  
  int
  handle_slow_trap(Trap_state *ts);
  
#line 338 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
  inline bool
  update_local_map(Address, Mword);
  
#line 431 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
  /* return 1 if this exception should be sent, return 0 if not
   */
  
  inline int
  send_exception_arch(Trap_state *ts);
  
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"
  template<typename T> inline void FIASCO_NORETURN
  fast_return_to_user(Mword ip, Mword sp, T arg);
  
#line 48 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"
  inline void
  restore_exc_state();
  
#line 133 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  void
  ipc_receiver_aborted() override;
  
#line 167 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  void
  modify_label(Mword const *todo, int cnt) override;
  
#line 314 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  /**
   * Setup a IPC-like timer for the given timeout.
   * \param timeout  The L4 ABI timeout value that shall be used
   * \param utcb     The UTCB that might contain an absolute timeout
   * \param timer    The timeout/timer object that shall be queued.
   *
   * This function does nothing if the timeout is *never*.
   * Sets Thread_ready and Thread_timeout in the thread state
   * if the timeout is zero or has already hit (is in the past).
   * Or enqueues the given timer object with the finite timeout calculated
   * from `timeout`.
   */
  
  inline void
  setup_timer(L4_timeout timeout, Utcb const *utcb, Timeout *timer);
  
#line 450 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  /**
   * Send an IPC message.
   *        Block until we can send the message or the timeout hits.
   * @param partner the receiver of our message
   * @param t a timeout specifier
   * @param regs sender's IPC registers
   * @pre cpu_lock must be held
   * @return sender's IPC error code
   *
   * @todo review closed wait handling of sender during possible
   *       quiescent states and blocking.
   */
  
  void
  do_ipc(L4_msg_tag const &tag, bool have_send, Thread *partner,
                 bool have_receive, Sender *sender,
                 L4_timeout_pair t, Syscall_frame *regs,
                 L4_fpage::Rights rights);
  
#line 739 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  /* return 1 if exception could be handled
   * return 0 if not for send_exception and halt thread
   */
  
  
  
  inline int
  send_exception(Trap_state *ts);
  
#line 879 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  inline bool FIASCO_WARN_RESULT
  copy_utcb_to(L4_msg_tag tag, Thread* receiver,
                       L4_fpage::Rights rights);
  
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-log.cpp"
  static inline int
  log_page_fault();
  
#line 22 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-vcpu.cpp"
  inline void
  vcpu_set_user_space(Task *t);
  
#line 43 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-vcpu.cpp"
  inline bool
  vcpu_pagefault(Address pfa, Mword err, Mword ip);

protected:  
#line 599 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  bool
  kill() override;
  
#line 516 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
  inline void
  vcpu_resume_user_arch();
  
#line 749 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
  inline int
  sys_control_arch(Utcb *);
  
#line 34 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"
  inline int
  do_trigger_exception(Entry_frame *r, void *ret_handler);
  
#line 275 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"
  inline L4_msg_tag
  invoke_arch(L4_msg_tag tag, Utcb *utcb);

private:  
#line 440 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  static inline void
  user_invoke_generic();
  
#line 456 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  static void
  leave_and_kill_myself();
  
#line 493 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  bool
  do_kill();
  
#line 587 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  static Context::Drq::Result
  handle_remote_kill(Drq *, Context *self, void *);
  
#line 716 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  inline Thread::Migration *
  start_migration();
  
#line 739 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  bool
  do_migration();
  
#line 918 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  inline bool
  migrate_away(Migration *inf, bool remote);
  
#line 963 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  inline bool
  migrate_to(Cpu_number target_cpu, bool);
  
#line 999 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  inline void
  force_to_invalid_cpu();
  
#line 86 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
  static inline Mword
  sanitize_user_flags(Mword flags);
  
#line 155 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
  static void
  print_page_fault_error(Mword e);
  
#line 427 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
  static inline void
  save_fpu_state_to_utcb(Trap_state *, Utcb *);
  
#line 449 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
  inline void _hw_virt_arch_init_vcpu_state(Vcpu_state *);
  
#line 521 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
  inline L4_msg_tag
  sys_gdt_x86(L4_msg_tag tag, Utcb *utcb);
  
#line 615 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
  /**
   * The ia32 specific part of the thread constructor.
   */
  
  inline void
  arch_init();
  
#line 649 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
  inline void
  check_f00f_bug(Trap_state *ts);
  
#line 663 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
  inline unsigned
  check_io_bitmap_delimiter_fault(Trap_state *ts);
  
#line 701 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
  inline bool
  handle_sysenter_trap(Trap_state *ts, Address eip, bool from_user);
  
#line 729 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
  inline int
  handle_not_nested_trap(Trap_state *ts);
  
#line 758 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
  static inline Cpu_number dbg_find_cpu();
  
#line 67 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"
  static inline Return_frame *
  trap_state_to_rf(Trap_state *ts);
  
#line 75 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"
  static inline bool FIASCO_WARN_RESULT
  copy_utcb_to_ts(L4_msg_tag const &tag, Thread *snd, Thread *rcv,
                          L4_fpage::Rights rights);
  
#line 128 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"
  static inline bool FIASCO_WARN_RESULT
  copy_ts_to_utcb(L4_msg_tag const &, Thread *snd, Thread *rcv,
                          L4_fpage::Rights rights);
  
#line 156 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"
  static inline bool
  check_known_inkernel_fault(Trap_state *ts);
  
#line 187 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"
  inline int
  check_trap13_kernel(Trap_state *ts);
  
#line 291 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"
  /** Call the nested trap handler (either Jdb::enter_kdebugger() or the
   * gdb stub. Setup our own stack frame */
  
  static int
  call_nested_trap_handler(Trap_state *ts);
  
#line 145 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  void
  ipc_send_msg(Receiver *recv) override;
  
#line 189 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  inline void
  snd_regs(Syscall_frame *r);
  
#line 194 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  /** Page fault handler.
      This handler suspends any ongoing IPC, then sets up page-fault IPC.
      Finally, the ongoing IPC's state (if any) is restored.
      @param pfa page-fault virtual address
      @param error_code page-fault error code.
   */
  
  bool
  handle_page_fault_pager(Thread_ptr const &_pager,
                                  Address pfa, Mword error_code,
                                  L4_msg_tag::Protocol protocol);
  
#line 288 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  inline Thread::Check_sender
  check_sender(Thread *sender, bool timeout);
  
#line 352 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  inline void goto_sleep(L4_timeout const &t, Sender *sender, Utcb *utcb);
  
#line 371 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  /**
   * @pre cpu_lock must be held
   */
  
  inline Thread::Check_sender
  handshake_receiver(Thread *partner, L4_timeout snd_t);
  
#line 394 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  inline void
  set_ipc_error(L4_error const &e, Thread *rcv);
  
#line 403 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  inline Sender *
  get_next_sender(Sender *sender);
  
#line 427 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  inline bool
  activate_ipc_partner(Thread *partner, Cpu_number current_cpu,
                               bool do_switch, bool closed_wait);
  
#line 629 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  inline bool
  transfer_msg(L4_msg_tag tag, Thread *receiver,
                       Syscall_frame *sender_regs, L4_fpage::Rights rights);
  
#line 683 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  /**
   * \pre must run with local IRQs disabled (CPU lock held)
   * to ensure that handler does not dissapear meanwhile.
   */
  
  bool
  exception(Kobject_iface *handler, Trap_state *ts, L4_fpage::Rights rights);
  
#line 820 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  static bool
  try_transfer_local_id(L4_buf_iter::Item const *const buf,
                                L4_fpage sfp, Mword *rcv_word, Thread* snd,
                                Thread *rcv);
  
#line 851 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  static inline bool FIASCO_WARN_RESULT
  copy_utcb_to_utcb(L4_msg_tag const &tag, Thread *snd, Thread *rcv,
                            L4_fpage::Rights rights);
  
#line 895 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  static bool
  transfer_msg_items(L4_msg_tag const &tag, Thread* snd, Utcb *snd_utcb,
                             Thread *rcv, Utcb *rcv_utcb,
                             L4_fpage::Rights rights);
  
#line 1020 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  /**
   * \pre Runs on the sender CPU
   * \retval true when the IPC was aborted
   * \retval false iff the IPC was already finished
   */
  
  inline bool
  abort_send(L4_error const &e, Thread *partner);
  
#line 1067 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  /**
   * \pre Runs on the sender CPU
   * \retval true iff the IPC was finished during the wait
   * \retval false iff the IPC was aborted with some error
   */
  
  inline bool
  do_send_wait(Thread *partner, L4_timeout snd_t);
  
#line 1115 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  inline void
  set_ipc_send_rights(L4_fpage::Rights c);
  
#line 1122 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  inline bool
  remote_ipc_send(Ipc_remote_request *rq);
  
#line 1182 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  static Context::Drq::Result
  handle_remote_ipc_send(Drq *src, Context *, void *_rq);
  
#line 1191 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
  /**
   * \pre Runs on the sender CPU
   */
  //inline NEEDS ["mp_request.h"]
  Thread::Check_sender
  remote_handshake_receiver(L4_msg_tag const &tag, Thread *partner,
                                    bool have_receive,
                                    L4_timeout snd_t, Syscall_frame *regs,
                                    L4_fpage::Rights rights);
  
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-log.cpp"
  /** Page-fault logging.
   */
  void
  page_fault_log(Address pfa, unsigned error_code, unsigned long eip);
  
#line 215 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-io.cpp"
  inline int
  handle_io_page_fault(Trap_state *ts);
};
#line 185 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#line 1306 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#line 22 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

//----------------------------------------------------------------------------

#line 56 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"

class Buf_utcb_saver
{
public:
  Buf_utcb_saver(Utcb const *u);
  void restore(Utcb *u);
private:
  L4_buf_desc buf_desc;
  Mword buf[2];
};
#line 66 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"

/**
 * Save critical contents of UTCB during nested IPC.
 */
class Pf_msg_utcb_saver : public Buf_utcb_saver
{
public:
  Pf_msg_utcb_saver(Utcb const *u);
  void restore(Utcb *u);
private:
  Mword msg[2];
};
#line 78 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"


// ------------------------------------------------------------------------

#line 91 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"

// ------------------------------------------------------------------------

#line 1229 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
#line 1237 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-debug.cpp"

//--------------------------------------------------------------------------

#line 24 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-debug.cpp"

#line 364 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
// end of: IPC-gate deletion stuff -------------------------------

/** Currently executing thread.
    @return currently executing thread.
 */

inline Thread*
current_thread();

#line 147 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
extern "C" FIASCO_FASTCALL
void
thread_restore_exc_state();

#line 345 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
/**
 * The low-level page fault handler called from entry.S.  We're invoked with
 * interrupts turned off.  Apart from turning on interrupts in almost
 * all cases (except for kernel page faults in TCB area), just forwards
 * the call to Thread::handle_page_fault().
 * @param pfa page-fault virtual address
 * @param error_code CPU error code
 * @return true if page fault could be resolved, false otherwise
 */
extern "C" FIASCO_FASTCALL
int
thread_page_fault(Address pfa, Mword error_code, Address ip, Mword flags,
		  Return_frame *regs);

#line 385 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
/** The catch-all trap entry point.  Called by assembly code when a 
    CPU trap (that's not specially handled, such as system calls) occurs.
    Just forwards the call to Thread::handle_slow_trap().
    @param state trap state
    @return 0 if trap has been consumed by handler;
           -1 if trap could not be handled.
 */
extern "C" FIASCO_FASTCALL
int
thread_handle_trap(Trap_state *ts, unsigned);

#line 635 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
/** A C interface for Context::handle_fpu_trap, callable from assembly code.
    @relates Context
 */
// The "FPU not available" trap entry point
extern "C"
int
thread_handle_fputrap();

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 169 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "irq_chip.h"
#line 177 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "space.h"
#line 181 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "timeout.h"
#line 595 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

#include "fpu.h"
#line 597 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "fpu_alloc.h"
#line 598 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "fpu_state.h"
#line 599 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "gdt.h"
#line 288 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"

#include "kernel_task.h"
#line 129 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
#include "timer.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-pagefault.cpp"
#include "kdb_ke.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-pagefault.cpp"
#include "std_macros.h"
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-pagefault.cpp"
#include "warn.h"
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-pagefault.cpp"
#include "paging.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-log.cpp"
#include "jdb_trace.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-log.cpp"
#include "cpu_lock.h"
#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-debug.cpp"
#include "config.h"
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-dbf.cpp"

#include <cstdio>
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-dbf.cpp"
#include "processor.h"
#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-dbf.cpp"
#include "trap_state.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-vcpu.cpp"

#include "logdefs.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-vcpu.cpp"
#include "task.h"
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-vcpu.cpp"
#include "vcpu.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 194 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"



inline void *
Thread::operator new(size_t, Ram_quota *q) throw ()
{
  void *t = Kmem_alloc::allocator()->q_unaligned_alloc(q, Thread::Size);
  if (t)
    memset(t, 0, sizeof(Thread));

  return t;
}

#line 233 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"



inline bool
Thread::unbind()
{
  Task *old;

    {
      auto guard = lock_guard(_space.lock());

      if (_space.space() == Kernel_task::kernel_task())
        return true;

      old = static_cast<Task*>(_space.space());
      _space.space(Kernel_task::kernel_task());

      // switch to a safe page table
      if (Mem_space::current_mem_space(current_cpu()) == old)
        Kernel_task::kernel_task()->switchin_context(old);

      if (old->dec_ref())
        old = 0;
    }

  if (old)
    {
      current()->rcu_wait();
      delete old;
    }

  return true;
}

#line 331 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"



inline void
Thread::ipc_gate_deleted(Mword id)
{
  (void) id;
  auto g = lock_guard(cpu_lock);
  if (_del_observer)
    _del_observer->hit(0);
}

#line 373 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


inline bool
Thread::exception_triggered() const
{ return _exc_cont.valid(regs()); }

#line 378 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


inline bool
Thread::continuation_test_and_restore()
{
  bool v = _exc_cont.valid(regs());
  if (v)
    _exc_cont.restore(regs());
  return v;
}

#line 388 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"

//
// state requests/manipulation
//


inline void
Thread::handle_timer_interrupt()
{
  Cpu_number _cpu = current_cpu();
  // XXX: This assumes periodic timers (i.e. bogus in one-shot mode)
  if (!Config::Fine_grained_cputime)
    consume_time(Config::Scheduler_granularity);

  bool resched = Rcu::do_pending_work(_cpu);

  // Check if we need to reschedule due to timeouts or wakeups
  if ((Timeout_q::timeout_queue.cpu(_cpu).do_timeouts() || resched)
      && !Sched_context::rq.current().schedule_in_progress)
    {
      schedule();
      assert (timeslice_timeout.cpu(current_cpu())->is_set());	// Coma check
    }
}

#line 658 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"

// used by UX only

inline bool
Thread::is_tcb_address(Address a)
{
  a &= ~(Thread::Size - 1);
  return reinterpret_cast<Thread *>(a)->_magic == magic;
}

#line 667 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


inline void
Thread::assert_irq_entry()
{
  assert(Sched_context::rq.current().schedule_in_progress
             || current_thread()->state() & (Thread_ready_mask | Thread_drq_wait | Thread_waiting | Thread_ipc_transfer));
}

#line 675 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"

// ---------------------------------------------------------------------------


inline bool
Thread::check_sys_ipc(unsigned flags, Thread **partner, Thread **sender,
                      bool *have_recv) const
{
  if (flags & L4_obj_ref::Ipc_recv)
    {
      *sender = flags & L4_obj_ref::Ipc_open_wait ? 0 : const_cast<Thread*>(this);
      *have_recv = true;
    }

  if (flags & L4_obj_ref::Ipc_send)
    *partner = const_cast<Thread*>(this);

  // FIXME: shall be removed flags == 0 is no-op
  if (!flags)
    {
      *sender = const_cast<Thread*>(this);
      *partner = const_cast<Thread*>(this);
      *have_recv = true;
    }

  return *have_recv || ((flags & L4_obj_ref::Ipc_send) && *partner);
}

#line 791 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"

/*
 * Handle FPU trap for this context. Assumes disabled interrupts
 */

inline int
Thread::switchin_fpu(bool alloc_new_fpu)
{
  if (state() & Thread_vcpu_fpu_disabled)
    return 0;

  Fpu &f = Fpu::fpu.current();
  // If we own the FPU, we should never be getting an "FPU unavailable" trap
  assert (f.owner() != this);

  // Allocate FPU state slab if we didn't already have one
  if (!fpu_state()->state_buffer()
      && (EXPECT_FALSE((!alloc_new_fpu
                        || (state() & Thread_alien))
                       || !Fpu_alloc::alloc_state(_quota, fpu_state()))))
    return 0;

  // Enable the FPU before accessing it, otherwise recursive trap
  f.enable();

  // Save the FPU state of the previous FPU owner (lazy) if applicable
  if (f.owner())
    f.owner()->spill_fpu();

  // Become FPU owner and restore own FPU state
  f.restore_state(fpu_state());

  state_add_dirty(Thread_fpu_owner);
  f.set_owner(this);
  return 1;
}

#line 827 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


inline void
Thread::transfer_fpu(Thread *to) //, Trap_state *trap_state, Utcb *to_utcb)
{
  if (to->fpu_state()->state_buffer())
    Fpu_alloc::free_state(to->fpu_state());

  to->fpu_state()->state_buffer(fpu_state()->state_buffer());
  fpu_state()->state_buffer(0);

  if (home_cpu() != to->home_cpu())
    {
      assert (!(to->state() & Thread_fpu_owner));
      assert (!(state() & Thread_fpu_owner));
      return;
    }

  assert (current() == this || current() == to);

  Fpu &f = Fpu::fpu.current();

  f.disable(); // it will be reenabled in switch_fpu

  if (EXPECT_FALSE(f.owner() == to))
    {
      assert (to->state() & Thread_fpu_owner);

      f.set_owner(0);
      to->state_del_dirty(Thread_fpu_owner);
    }
  else if (f.owner() == this)
    {
      assert (state() & Thread_fpu_owner);

      state_del_dirty(Thread_fpu_owner);

      to->state_add_dirty (Thread_fpu_owner);
      f.set_owner(to);
      if (EXPECT_FALSE(current() == to))
        f.enable();
    }
}

#line 336 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


inline bool
Thread::update_local_map(Address, Mword)
{ return false; }

#line 430 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

/* return 1 if this exception should be sent, return 0 if not
 */

inline int
Thread::send_exception_arch(Trap_state *ts)
{
  // Do not send exception IPC but return 'not for us' if thread is a normal
  // thread (not alien) and it's a debug trap,
  // debug traps for aliens are always reflected as exception IPCs
  if (!(state() & Thread_alien) && (ts->_trapno == 1))
    return 0; // we do not handle this

  return 1; // make it an exception
}

#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"

 
template<typename T> inline void FIASCO_NORETURN
Thread::fast_return_to_user(Mword ip, Mword sp, T arg)
{
  assert(cpu_lock.test());
  assert(current() == this);
  assert(Config::Is_ux || (regs()->cs() & 3) == 3);

  regs()->ip(ip);
  regs()->sp(sp);
  regs()->flags(EFLAGS_IF);
  asm volatile
    ("mov %0, %%esp \t\n"
     "iret         \t\n"
     :
     : "r" (static_cast<Return_frame*>(regs())), "a" (arg)
    );
  __builtin_trap();
}

#line 45 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"



inline void
Thread::restore_exc_state()
{
  assert (cpu_lock.test());
  _exc_cont.restore(regs());
#if 0

#ifdef CONFIG_PF_UX
  r->cs (exception_cs() & ~1);
#else
  r->cs (exception_cs());
#endif
  r->ip (_exc_ip);
  r->flags (_exc_flags);
  _exc_ip = ~0UL;
#endif
}

#line 313 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"

/**
 * Setup a IPC-like timer for the given timeout.
 * \param timeout  The L4 ABI timeout value that shall be used
 * \param utcb     The UTCB that might contain an absolute timeout
 * \param timer    The timeout/timer object that shall be queued.
 *
 * This function does nothing if the timeout is *never*.
 * Sets Thread_ready and Thread_timeout in the thread state
 * if the timeout is zero or has already hit (is in the past).
 * Or enqueues the given timer object with the finite timeout calculated
 * from `timeout`.
 */

inline void
Thread::setup_timer(L4_timeout timeout, Utcb const *utcb, Timeout *timer)
{
  if (EXPECT_TRUE(timeout.is_never()))
    return;

  if (EXPECT_FALSE(timeout.is_zero()))
    {
      state_add_dirty(Thread_ready | Thread_timeout);
      return;
    }

  assert (!_timeout);

  Unsigned64 sysclock = Timer::system_clock();
  Unsigned64 tval = timeout.microsecs(sysclock, utcb);

  if (EXPECT_TRUE((tval > sysclock)))
    set_timeout(timer, tval);
  else // timeout already hit
    state_add_dirty(Thread_ready | Thread_timeout);
}

#line 425 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


inline void
Thread::save_fpu_state_to_utcb(Trap_state *, Utcb *)
{}

#line 738 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"

/* return 1 if exception could be handled
 * return 0 if not for send_exception and halt thread
 */



inline int
Thread::send_exception(Trap_state *ts)
{
  assert(cpu_lock.test());

  Vcpu_state *vcpu = vcpu_state().access();

  if (vcpu_exceptions_enabled(vcpu))
    {
      // do not reflect debug exceptions to the VCPU but handle them in
      // Fiasco
      if (EXPECT_FALSE(ts->is_debug_exception()
                       && !(vcpu->state & Vcpu_state::F_debug_exc)))
        return 0;

      if (_exc_cont.valid(ts))
        return 1;

      // before entering kernel mode to have original fpu state before
      // enabling fpu
      save_fpu_state_to_utcb(ts, utcb().access());

      spill_user_state();

      if (vcpu_enter_kernel_mode(vcpu))
        {
          // enter_kernel_mode has switched the address space from user to
          // kernel space, so reevaluate the address of the VCPU state area
          vcpu = vcpu_state().access();
        }

      LOG_TRACE("VCPU events", "vcpu", this, Vcpu_log,
          l->type = 2;
          l->state = vcpu->_saved_state;
          l->ip = ts->ip();
          l->sp = ts->sp();
          l->trap = ts->trapno();
          l->err = ts->error();
          l->space = vcpu_user_space() ? static_cast<Task*>(vcpu_user_space())->dbg_id() : ~0;
          );
      vcpu->_regs.s = *ts;
      fast_return_to_user(vcpu->_entry_ip, vcpu->_sp, vcpu_state().usr().get());
    }

  // local IRQs must be disabled because we dereference a Thread_ptr
  if (EXPECT_FALSE(_exc_handler.is_kernel()))
    return 0;

  if (!send_exception_arch(ts))
    return 0; // do not send exception

  L4_fpage::Rights rights = L4_fpage::Rights(0);
  Kobject_iface *pager = _exc_handler.ptr(space(), &rights);

  if (EXPECT_FALSE(!pager))
    {
      /* no pager (anymore), just ignore the exception, return success */
      LOG_TRACE("Exception invalid handler", "ieh", this, Log_exc_invalid,
                l->cap_idx = _exc_handler.raw());
      if (EXPECT_FALSE(space()->is_sigma0()))
        {
          ts->dump();
          WARNX(Error, "Sigma0 raised an exception --> HALT\n");
          panic("...");
        }

      pager = this; // block on ourselves
    }

  state_change(~Thread_cancel, Thread_in_exception);

  return exception(pager, ts, rights);
}

#line 65 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"


inline Return_frame *
Thread::trap_state_to_rf(Trap_state *ts)
{
  char *im = reinterpret_cast<char*>(ts + 1);
  return reinterpret_cast<Return_frame*>(im)-1;
}

#line 84 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


inline Mword
Thread::sanitize_user_flags(Mword flags)
{ return (flags & ~(EFLAGS_IOPL | EFLAGS_NT)) | EFLAGS_IF; }

#line 73 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"


inline bool FIASCO_WARN_RESULT
Thread::copy_utcb_to_ts(L4_msg_tag const &tag, Thread *snd, Thread *rcv,
                        L4_fpage::Rights rights)
{
  if (EXPECT_FALSE((tag.words() * sizeof(Mword)) < sizeof(Trex)))
    return true;

  Trap_state *ts = (Trap_state*)rcv->_utcb_handler;
  Unsigned32  cs = ts->cs();
  Utcb *snd_utcb = snd->utcb().access();
  Trex const *src = reinterpret_cast<Trex const *>(snd_utcb->values);

  // XXX: check that gs and fs point to valid user_entry only, for gdt and
  // ldt!
  if (EXPECT_FALSE(rcv->exception_triggered()))
    {
      // triggered exception pending, skip ip, cs, flags, and sp
      Mem::memcpy_mwords(ts, &src->s, Ts::Reg_words);
      Continuation::User_return_frame const *urfp
        = reinterpret_cast<Continuation::User_return_frame const *>(
            (char*)&src->s._ip);

      Continuation::User_return_frame urf = access_once(urfp);

      // sanitize flags
      urf.flags(sanitize_user_flags(urf.flags()));
      rcv->_exc_cont.set(trap_state_to_rf(ts), &urf);
    }
  else
    {
      Mem::memcpy_mwords(ts, &src->s, Ts::Words);
      // sanitize flags
      ts->flags(sanitize_user_flags(ts->flags()));
      // don't allow to overwrite the code selector!
      ts->cs(cs);
    }

  // reset segments
  rcv->_gs = rcv->_fs = 0;

  if (rcv == current())
    rcv->load_gdt_user_entries(rcv);

  if (tag.transfer_fpu() && (rights & L4_fpage::Rights::W()))
    snd->transfer_fpu(rcv);

  bool ret = transfer_msg_items(tag, snd, snd_utcb,
                                rcv, rcv->utcb().access(), rights);

  return ret;
}

#line 849 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"


inline bool FIASCO_WARN_RESULT
Thread::copy_utcb_to_utcb(L4_msg_tag const &tag, Thread *snd, Thread *rcv,
                          L4_fpage::Rights rights)
{
  assert (cpu_lock.test());

  Utcb *snd_utcb = snd->utcb().access();
  Utcb *rcv_utcb = rcv->utcb().access();
  Mword s = tag.words();
  Mword r = Utcb::Max_words;

  Mem::memcpy_mwords(rcv_utcb->values, snd_utcb->values, r < s ? r : s);

  bool success = true;
  if (tag.items())
    success = transfer_msg_items(tag, snd, snd_utcb, rcv, rcv_utcb, rights);

  if (success
      && tag.transfer_fpu()
      && rcv_utcb->inherit_fpu()
      && (rights & L4_fpage::Rights::W()))
    snd->transfer_fpu(rcv);

  return success;
}

#line 126 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"


inline bool FIASCO_WARN_RESULT
Thread::copy_ts_to_utcb(L4_msg_tag const &, Thread *snd, Thread *rcv,
                        L4_fpage::Rights rights)
{
  Trap_state *ts = (Trap_state*)snd->_utcb_handler;
  Utcb *rcv_utcb = rcv->utcb().access();
  Trex *dst = reinterpret_cast<Trex *>(rcv_utcb->values);
    {
      auto guard = lock_guard(cpu_lock);
      if (EXPECT_FALSE(snd->exception_triggered()))
        {
          Mem::memcpy_mwords(&dst->s, ts, Ts::Reg_words + Ts::Code_words);
          Continuation::User_return_frame *d
            = reinterpret_cast<Continuation::User_return_frame *>(
                (char*)&dst->s._ip);

          snd->_exc_cont.get(d, trap_state_to_rf(ts));
        }
      else
        Mem::memcpy_mwords(&dst->s, ts, Ts::Words);

      if (rcv_utcb->inherit_fpu() && (rights & L4_fpage::Rights::W()))
        snd->transfer_fpu(rcv);
    }
  return true;
}

#line 876 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"




inline bool FIASCO_WARN_RESULT
Thread::copy_utcb_to(L4_msg_tag tag, Thread* receiver,
                     L4_fpage::Rights rights)
{
  // we cannot copy trap state to trap state!
  assert (!this->_utcb_handler || !receiver->_utcb_handler);
  if (EXPECT_FALSE(this->_utcb_handler != 0))
    return copy_ts_to_utcb(tag, this, receiver, rights);
  else if (EXPECT_FALSE(receiver->_utcb_handler != 0))
    return copy_utcb_to_ts(tag, this, receiver, rights);
  else
    return copy_utcb_to_utcb(tag, this, receiver, rights);
}

#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-log.cpp"


inline int
Thread::log_page_fault()
{
  return Jdb_pf_trace::log();
}

#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-vcpu.cpp"



inline void
Thread::vcpu_set_user_space(Task *t)
{
  assert (current() == this);
  if (t)
    t->inc_ref();

  Task *old = static_cast<Task*>(_space.vcpu_user());
  _space.vcpu_user(t);

  if (old)
    {
      if (!old->dec_ref())
	{
	  rcu_wait();
	  delete old;
	}
    }
}

#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-vcpu.cpp"


inline bool
Thread::vcpu_pagefault(Address pfa, Mword err, Mword ip)
{
  (void)ip;
  Vcpu_state *vcpu = vcpu_state().access();
  if (vcpu_pagefaults_enabled(vcpu))
    {
      spill_user_state();
      vcpu_enter_kernel_mode(vcpu);
      LOG_TRACE("VCPU events", "vcpu", this, Vcpu_log,
	  l->type = 3;
	  l->state = vcpu->_saved_state;
	  l->ip = ip;
	  l->sp = pfa;
          l->err = err;
	  l->space = vcpu_user_space() ? static_cast<Task*>(vcpu_user_space())->dbg_id() : ~0;
	  );
      vcpu->_regs.s.set_pagefault(pfa, err);
      vcpu_save_state_and_upcall();
      return true;
    }

  return false;
}

#line 514 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


inline void
Thread::vcpu_resume_user_arch()
{}

#line 747 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


inline int
Thread::sys_control_arch(Utcb *)
{
  return 0;
}

#line 32 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"


inline int
Thread::do_trigger_exception(Entry_frame *r, void *ret_handler)
{
  if (!exception_triggered())
    {
      _exc_cont.activate(r, ret_handler);
      return 1;
    }
  // else ignore change of IP because triggered exception already pending
  return 0;
}

#line 519 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


inline L4_msg_tag
Thread::sys_gdt_x86(L4_msg_tag tag, Utcb *utcb)
{
  // if no words given then return the first gdt entry
  if (EXPECT_FALSE(tag.words() == 1))
    {
      utcb->values[0] = Gdt::gdt_user_entry1 >> 3;
      return Kobject_iface::commit_result(0, 1);
    }

  unsigned idx = 0;

  for (unsigned entry_number = utcb->values[1];
      entry_number < Gdt_user_entries
      && Utcb::val_idx(Utcb::val64_idx(2) + idx) < tag.words();
      ++idx, ++entry_number)
    {
      Gdt_entry d = access_once((Gdt_entry *)&utcb->val64[Utcb::val64_idx(2) + idx]);
      if (!d.unsafe())
        _gdt_user_entries[entry_number] = d;
    }

  if (this == current_thread())
    load_gdt_user_entries();

  return Kobject_iface::commit_result((utcb->values[1] << 3) + Gdt::gdt_user_entry1 + 3);
}

#line 273 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"


inline L4_msg_tag
Thread::invoke_arch(L4_msg_tag tag, Utcb *utcb)
{
  switch (utcb->values[0] & Opcode_mask)
    {
    case Op_gdt_x86: return sys_gdt_x86(tag, utcb);
    default:
      return commit_result(-L4_err::ENosys);
    };
}

#line 266 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"

/** Cut-down version of Thread constructor; only for kernel threads
    Do only what's necessary to get a kernel thread started --
    skip all fancy stuff, no locking is necessary.
    @param task the address space
    @param id user-visible thread ID of the sender
 */

inline Thread::Thread(Ram_quota *q, Context_mode_kernel)
  : Receiver(), Sender(), _quota(q), _del_observer(0), _magic(magic)
{
  inc_ref();
  _space.space(Kernel_task::kernel_task());

  if (Config::Stack_depth)
    std::memset((char*)this + sizeof(Thread), '5',
                Thread::Size-sizeof(Thread) - 64);
}

#line 653 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


inline bool
Thread::arch_ext_vcpu_enabled()
{ return false; }

#line 74 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


inline Mword
Thread::user_ip() const
{ return exception_triggered()?_exc_cont.ip():regs()->ip(); }

#line 79 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


inline Mword
Thread::user_flags() const
{ return regs()->flags(); }

#line 89 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

/** Check if the pagefault occurred at a special place: At some places in the
    kernel we want to ensure that a specific address is mapped. The regular
    case is "mapped", the exception or slow case is "not mapped". The fastest
    way to check this is to touch into the memory. If there is no mapping for
    the address we get a pagefault. Now the pagefault exception handler can
    recognize that situation by scanning the code. The trick is that the
    assembler instruction "andl $0xffffffff, %ss:(%ecx)" _clears_ the carry
    flag normally (see Intel reference manual). The pager wants to inform the
    code that there was a pagefault and therefore _sets_ the carry flag. So
    the code has only to check if the carry flag is set. If yes, there was
    a pagefault at this instruction.
    @param ip pagefault address */

inline bool
Thread::pagein_tcb_request(Return_frame *regs)
{
  unsigned long new_ip = regs->ip();
  if (*(Unsigned8*)new_ip == 0x48) // REX.W
    new_ip += 1;

  Unsigned16 op = *(Unsigned16*)new_ip;
  //LOG_MSG_3VAL(current(),"TCB", op, new_ip, 0);
  if ((op & 0xc0ff) == 0x8b) // Context::is_tcb_mapped() and Context::state()
    {
      regs->ip(new_ip + 2);
      // stack layout:
      //         user eip
      //         PF error code
      // reg =>  eax/rax
      //         ecx/rcx
      //         edx/rdx
      //         ...
      Mword *reg = ((Mword*)regs) - 2 - Return_frame::Pf_ax_offset;
#if 0
      LOG_MSG_3VAL(current(),"TCB", op, regs->ip(), (Mword)reg);
      LOG_MSG_3VAL(current(),"TCBX", reg[-3], reg[-4], reg[-5]);
      LOG_MSG_3VAL(current(),"TCB0", reg[0], reg[-1], reg[-2]);
      LOG_MSG_3VAL(current(),"TCB1", reg[1], reg[2], reg[3]);
#endif
      assert((op >> 11) <= 2);
      reg[-(op>>11)] = 0; // op==0 => eax, op==1 => ecx, op==2 => edx

      // tell program that a pagefault occured we cannot handle
      regs->flags(regs->flags() | 0x41); // set carry and zero flag in EFLAGS
      return true;
    }
  else if (*(Unsigned32*)regs->ip() == 0xff01f636) // used in shortcut.S
    {
      regs->ip(regs->ip() + 4);
      regs->flags(regs->flags() | 1);  // set carry flag in EFLAGS
      return true;
    }

  return false;
}

#line 398 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


//
// Public services
//


inline bool
Thread::handle_sigma0_page_fault(Address pfa)
{
  Mem_space::Page_order size = mem_space()->largest_page_size(); // take a page size less than 16MB (1<<24)
  auto f = mem_space()->fitting_sizes();
  Virt_addr va = Virt_addr(pfa);

  // Check if mapping a superpage doesn't exceed the size of physical memory
  // Some distributions do not allow to mmap below a certain threshold
  // (like 64k on Ubuntu 8.04) so we cannot map a superpage at 0 if
  // we're Fiasco-UX
  while (Config::Is_ux && (va < (Virt_addr(1) << size)))
    size = f(--size);

  va = cxx::mask_lsb(va, size);

  return mem_space()->v_insert(Mem_space::Phys_addr(va), va, size,
                               Page::Attr(L4_fpage::Rights::URWX()))
    != Mem_space::Insert_err_nomem;
}

#line 448 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

inline void Thread::_hw_virt_arch_init_vcpu_state(Vcpu_state *) {}

#line 476 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


inline void
Thread::arch_init_vcpu_state(Vcpu_state *vcpu_state, bool ext)
{
  vcpu_state->version = Vcpu_arch_version;

  if (ext)
    _hw_virt_arch_init_vcpu_state(vcpu_state);
}

#line 607 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


inline Mword
Thread::exception_cs()
{
  return Gdt::gdt_code_user | Gdt::Selector_user;
}

#line 22 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"


inline Mword
Thread::user_sp() const
{ return regs()->sp(); }

#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"


inline void
Thread::user_sp(Mword sp)
{ regs()->sp(sp); }

#line 174 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"


inline void
Thread::user_ip(Mword ip)
{
  if (exception_triggered())
    _exc_cont.ip(ip);
  else
    regs()->ip(ip);
}

#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-pagefault.cpp"


/** 
 * The global page fault handler switch.
 * Handles page-fault monitoring, classification of page faults based on
 * virtual-memory area they occured in, page-directory updates for kernel
 * faults, IPC-window updates, and invocation of paging function for
 * user-space page faults (handle_page_fault_pager).
 * @param pfa page-fault virtual address
 * @param error_code CPU error code
 * @return true if page fault could be resolved, false otherwise
 * @exception longjmp longjumps to recovery location if page-fault
 *                    handling fails (i.e., return value would be false),
 *                    but recovery location has been installed
 */



inline int Thread::handle_page_fault(Address pfa, Mword error_code, Mword pc,
                              Return_frame *regs)
{
  //if (Config::Log_kernel_page_faults && !PF::is_usermode_error(error_code))
  if (0 && current_cpu() != Cpu_number::boot_cpu())
    {
      auto guard = lock_guard(cpu_lock);
      printf("*KP[cpu=%u, sp=%lx, pfa=%lx, pc=%lx, error=(%lx)",
             cxx::int_value<Cpu_number>(current_cpu()),
             Proc::stack_pointer(), pfa, pc, error_code);
      print_page_fault_error(error_code);
      printf("]\n");
    }

#if 0
  printf("Translation error ? %x\n"
	 "  current space has mapping : %08x\n"
	 "  Kernel space has mapping  : %08x\n",
	 PF::is_translation_error(error_code),
	 current_mem_space()->lookup((void*)pfa),
	 Space::kernel_space()->lookup((void*)pfa));
#endif


  CNT_PAGE_FAULT;

  // TODO: put this into a debug_page_fault_handler
  if (EXPECT_FALSE(log_page_fault()))
    page_fault_log(pfa, error_code, pc);

  L4_msg_tag ipc_code = L4_msg_tag(0, 0, 0, 0);

  // Check for page fault in user memory area
  if (EXPECT_TRUE(!Kmem::is_kmem_page_fault(pfa, error_code)))
    {
      // Make sure that we do not handle page faults that do not
      // belong to this thread.
      //assert (mem_space() == current_mem_space());

      if (EXPECT_FALSE(mem_space()->is_sigma0()))
        {
          // special case: sigma0 can map in anything from the kernel
	  if(handle_sigma0_page_fault(pfa))
            return 1;

          ipc_code.set_error();
          goto error;
        }

      // user mode page fault -- send pager request
      if (handle_page_fault_pager(_pager, pfa, error_code,
                                  L4_msg_tag::Label_page_fault))
        return 1;

      goto error;
    }

  // Check for page fault in kernel memory region caused by user mode
  else if (EXPECT_FALSE(PF::is_usermode_error(error_code)))
    return 0;             // disallow access after mem_user_max

  // Check for page fault in IO bit map or in delimiter byte behind IO bitmap
  // assume it is caused by an input/output instruction and fall through to
  // handle_slow_trap
  else if (EXPECT_FALSE(Kmem::is_io_bitmap_page_fault(pfa)))
    return 0;

  // We're in kernel code faulting on a kernel memory region

  // A page is not present but a mapping exists in the global page dir.
  // Update our page directory by copying from the master pdir
  // This is the only path that should be executed with interrupts
  // disabled if the page faulter also had interrupts disabled.   
  // thread_page_fault() takes care of that.
  else if (Mem_layout::is_caps_area(pfa))
    {
      // Test for special case -- see function documentation
      if (pagein_tcb_request(regs))
	 return 2;

      printf("Fiasco BUG: Invalid CAP access (pc=%lx, pfa=%lx)\n", pc, pfa);
      kdb_ke("Fiasco BUG: Invalid access to Caps area");
      return 0;
    }

  WARN("No page-fault handler for 0x%lx, error 0x%lx, pc " L4_PTR_FMT "\n",
        pfa, error_code, pc);

  // An error occurred.  Our last chance to recover is an exception
  // handler a kernel function may have set.
 error:

  if (_recover_jmpbuf)
    longjmp(*_recover_jmpbuf, 1);

  return 0;
}

#line 646 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"




inline Buf_utcb_saver::Buf_utcb_saver(const Utcb *u)
{
  buf_desc = u->buf_desc;
  buf[0] = u->buffers[0];
  buf[1] = u->buffers[1];
}

#line 656 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"


inline void
Buf_utcb_saver::restore(Utcb *u)
{
  u->buf_desc = buf_desc;
  u->buffers[0] = buf[0];
  u->buffers[1] = buf[1];
}

#line 665 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"


inline Pf_msg_utcb_saver::Pf_msg_utcb_saver(Utcb const *u) : Buf_utcb_saver(u)
{
  msg[0] = u->values[0];
  msg[1] = u->values[1];
}

#line 672 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"


inline void
Pf_msg_utcb_saver::restore(Utcb *u)
{
  Buf_utcb_saver::restore(u);
  u->values[0] = msg[0];
  u->values[1] = msg[1];
}

#line 363 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"

// end of: IPC-gate deletion stuff -------------------------------

/** Currently executing thread.
    @return currently executing thread.
 */

inline Thread*
current_thread()
{ return nonull_static_cast<Thread*>(current()); }

#endif // thread_h
