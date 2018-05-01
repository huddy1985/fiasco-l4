// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "thread.h"
#include "thread_i.h"

#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

Trap_state::Handler Thread::nested_trap_handler FIASCO_FASTCALL;
#line 341 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

//----------------------------------------------------------------------------

#line 445 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

//----------------------------------------------------------------------------

#line 513 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
KIP_KERNEL_FEATURE("segments");
#line 605 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

DEFINE_PER_CPU Per_cpu<Thread::Dbg_stack> Thread::dbg_stack;
#line 754 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

//---------------------------------------------------------------------------


#line 43 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


Thread::Thread(Ram_quota *q)
: Receiver(),
  Sender(0),   // select optimized version of constructor
  _pager(Thread_ptr::Invalid),
  _exc_handler(Thread_ptr::Invalid),
  _quota(q),
  _del_observer(0)
{
  assert (state(false) == 0);

  inc_ref();
  _space.space(Kernel_task::kernel_task());

  if (Config::Stack_depth)
    std::memset((char*)this + sizeof(Thread), '5',
		Thread::Size-sizeof(Thread)-64);

  _magic          = magic;
  _recover_jmpbuf = 0;
  _timeout        = 0;

  prepare_switch_to(&user_invoke);

  arch_init();

  state_add_dirty(Thread_dead, false);

  // ok, we're ready to go!
}

#line 145 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


extern "C" FIASCO_FASTCALL
void
thread_restore_exc_state()
{
  current_thread()->restore_exc_state();
}

#line 153 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


void
Thread::print_page_fault_error(Mword e)
{
  printf("%lx", e);
}

#line 160 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

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
Thread::handle_slow_trap(Trap_state *ts)
{
  Address ip;
  int from_user = ts->cs() & 3;

  if (EXPECT_FALSE(ts->_trapno == 0xee)) //debug IPI
    {
      Ipi::eoi(Ipi::Debug, current_cpu());
      goto generic_debug;
    }

  if (from_user && _space.user_mode())
    {
      if (ts->_trapno == 14 && Kmem::is_io_bitmap_page_fault(ts->_cr2))
        {
	  ts->_trapno = 13;
	  ts->_err    = 0;
        }

      if (send_exception(ts))
	goto success;
    }

  // XXX We might be forced to raise an exception. In this case, our return
  // CS:IP points to leave_by_trigger_exception() which will trigger the
  // exception just before returning to userland. But if we were inside an
  // IPC while we was ex-regs'd, we will generate the 'exception after the
  // syscall' _before_ we leave the kernel.
  if (ts->_trapno == 13 && (ts->_err & 6) == 6)
    goto check_exception;

  LOG_TRAP;

  if (!check_trap13_kernel (ts))
    return 0;

  if (EXPECT_FALSE(!from_user))
    {
      // get also here if a pagefault was not handled by the user level pager
      if (ts->_trapno == 14)
	goto check_exception;

      if (check_known_inkernel_fault(ts))
        {
          ts->ip(regs()->ip());
          goto check_exception;
        }

      goto generic_debug;      // we were in kernel mode -- nothing to emulate
    }

  if (EXPECT_FALSE(ts->_trapno == 2))
    goto generic_debug;        // NMI always enters kernel debugger

  if (EXPECT_FALSE(ts->_trapno == 0xffffffff))
    goto generic_debug;        // debugger interrupt

  check_f00f_bug(ts);

  // so we were in user mode -- look for something to emulate

  // We continue running with interrupts off -- no sti() here. But
  // interrupts may be enabled by the pagefault handler if we get a
  // pagefault in peek_user().

  // Set up exception handling.  If we suffer an un-handled user-space
  // page fault, kill the thread.
  jmp_buf pf_recovery;
  unsigned error;
  if (EXPECT_FALSE ((error = setjmp(pf_recovery)) != 0) )
    {
      WARN("%p killed:\n"
           "\033[1mUnhandled page fault, code=%08x\033[m\n", this, error);
      goto fail_nomsg;
    }

  _recover_jmpbuf = &pf_recovery;

  switch (handle_io_page_fault(ts))
    {
    case 1:
      _recover_jmpbuf = 0;
      goto success;
    case 2:
      _recover_jmpbuf = 0;
      goto fail;
    default:
      break;
    }

  ip = ts->ip();

  // just print out some warning, we do the normal exception handling
  handle_sysenter_trap(ts, ip, from_user);
  _recover_jmpbuf = 0;

check_exception:
  // backward compatibility cruft: check for those insane "int3" debug
  // messaging command sequences
  if (!from_user && (ts->_trapno == 3))
    goto generic_debug;

  // send exception IPC if requested
  if (send_exception(ts))
    goto success;

  // privileged tasks also may invoke the kernel debugger with a debug
  // exception
  if (ts->_trapno == 1)
    goto generic_debug;


fail:
  // can't handle trap -- kill the thread
  WARN("%p killed:\n"
       "\033[1mUnhandled trap \033[m\n", this);

fail_nomsg:
  if ((int)Config::Warn_level >= Warning)
    ts->dump();

  halt();

success:
  _recover_jmpbuf = 0;
  return 0;

generic_debug:
  _recover_jmpbuf = 0;

  if (!nested_trap_handler)
    return handle_not_nested_trap(ts);

  return call_nested_trap_handler(ts);
}

#line 344 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

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
		  Return_frame *regs)
{

  // XXX: need to do in a different way, if on debug stack e.g.
#if 0
  // If we're in the GDB stub -- let generic handler handle it
  if (EXPECT_FALSE (!in_context_area((void*)Proc::stack_pointer())))
    return false;
#endif

  Thread *t = current_thread();

  if (t->update_local_map(pfa, error_code))
    return 1;

  // Pagefault in user mode or interrupts were enabled
  if (EXPECT_TRUE(PF::is_usermode_error(error_code))
      && t->vcpu_pagefault(pfa, error_code, ip))
    return 1;

  if(EXPECT_TRUE(PF::is_usermode_error(error_code))
     || (flags & EFLAGS_IF)
     || !Kmem::is_kmem_page_fault(pfa, error_code))
    Proc::sti();

  return t->handle_page_fault(pfa, error_code, ip, regs);
}

#line 384 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

/** The catch-all trap entry point.  Called by assembly code when a 
    CPU trap (that's not specially handled, such as system calls) occurs.
    Just forwards the call to Thread::handle_slow_trap().
    @param state trap state
    @return 0 if trap has been consumed by handler;
           -1 if trap could not be handled.
 */
extern "C" FIASCO_FASTCALL
int
thread_handle_trap(Trap_state *ts, unsigned)
{
  return current_thread()->handle_slow_trap(ts);
}

#line 633 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


/** A C interface for Context::handle_fpu_trap, callable from assembly code.
    @relates Context
 */
// The "FPU not available" trap entry point
extern "C"
int
thread_handle_fputrap()
{
  LOG_TRAP_N(7);

  return current_thread()->switchin_fpu();
}
