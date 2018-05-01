// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef thread_i_h
#define thread_i_h
#line 161 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"

#include <cassert>
#line 163 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include <cstdlib>		// panic()
#line 164 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include <cstring>
#line 165 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "atomic.h"
#line 166 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "entry_frame.h"
#line 167 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "fpu_alloc.h"
#line 168 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "globals.h"
#line 170 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "kdb_ke.h"
#line 171 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "kernel_task.h"
#line 172 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "kmem_alloc.h"
#line 173 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "logdefs.h"
#line 174 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "map_util.h"
#line 175 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "ram_quota.h"
#line 176 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "sched_context.h"
#line 178 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "std_macros.h"
#line 179 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "task.h"
#line 180 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "thread_state.h"
#line 787 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"

#include "fpu.h"
#line 789 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "fpu_alloc.h"
#line 790 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "fpu_state.h"
#line 1292 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"

#include "string_buffer.h"
#line 1294 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "kdb_ke.h"
#line 1295 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
#include "terminate.h"
#line 25 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

#include "config.h"
#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "cpu.h"
#line 28 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "cpu_lock.h"
#line 29 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "gdt.h"
#line 30 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "idt.h"
#line 31 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "ipi.h"
#line 32 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "mem_layout.h"
#line 33 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "logdefs.h"
#line 34 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "paging.h"
#line 35 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "processor.h"		// for cli/sti
#line 36 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "regdefs.h"
#line 37 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "std_macros.h"
#line 38 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "thread.h"
#line 39 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "timer.h"
#line 40 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "trap_state.h"
#line 511 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

#include <feature.h>
#line 600 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "globalconfig.h"
#line 601 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "idt.h"
#line 602 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "simpleio.h"
#line 603 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "static_init.h"
#line 604 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"
#include "terminate.h"
#line 116 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"

#include <cstdlib>		// panic()
#line 118 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"

#include "l4_types.h"
#line 120 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
#include "l4_msg_item.h"
#line 121 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"

#include "config.h"
#line 123 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
#include "cpu_lock.h"
#line 124 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
#include "ipc_timeout.h"
#line 125 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
#include "lock_guard.h"
#line 126 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
#include "logdefs.h"
#line 127 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
#include "map_util.h"
#line 128 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
#include "processor.h"
#line 130 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"
#include "warn.h"
#line 1227 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"

#include "string_buffer.h"
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-pagefault.cpp"

#include <cstdio>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-pagefault.cpp"

#include "config.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-pagefault.cpp"
#include "cpu.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-pagefault.cpp"
#include "kmem.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-pagefault.cpp"
#include "logdefs.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-pagefault.cpp"
#include "processor.h"
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-pagefault.cpp"
#include "thread.h"
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-log.cpp"

#include <cstring>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-log.cpp"
#include "config.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-log.cpp"
#include "jdb_tbuf.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-log.cpp"
#include "types.h"
#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-debug.cpp"

#include <cstdio>
#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-debug.cpp"
#include "kmem.h"
#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-debug.cpp"
#include "mem_layout.h"
#line 22 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-debug.cpp"
#include "simpleio.h"
#line 23 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-debug.cpp"
#include "string_buffer.h"
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-dbf.cpp"
#include "cpu.h"
#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-dbf.cpp"
#include "kernel_console.h"
#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-dbf.cpp"
#include "reset.h"
#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-dbf.cpp"
#include "tss.h"
#line 22 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-dbf.cpp"
#include "watchdog.h"
#line 303 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"

// IPC-gate deletion stuff ------------------------------------

/**
 * Fake IRQ Chip class for IPC-gate-delete notifications.
 * This chip uses the IRQ number as thread pointer and implements
 * the bind and unbind functionality.
 */
class Del_irq_chip : public Irq_chip_soft
{
public:
  static Del_irq_chip chip;

public:  
#line 320 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  static inline Thread *thread(Mword pin);
  
#line 324 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  static inline Mword pin(Thread *t);
  
#line 328 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"
  inline void
  unbind(Irq_base *irq);
};

//
// IMPLEMENTATION of inline functions follows
//


#line 438 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


inline void
Thread::user_invoke_generic()
{
  Context *const c = current();
  assert (c->state() & Thread_ready_mask);

  if (c->handle_drq())
    c->schedule();

  // release CPU lock explicitly, because
  // * the context that switched to us holds the CPU lock
  // * we run on a newly-created stack without a CPU lock guard
  cpu_lock.clear();
}

#line 714 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


inline Thread::Migration *
Thread::start_migration()
{
  assert(cpu_lock.test());
  Migration *m = _migration;

  assert (!((Mword)m & 0x3)); // ensure alignment

  if (!m || !mp_cas(&_migration, m, (Migration*)0))
    return reinterpret_cast<Migration*>(0x2); // bit one == 0 --> no need to reschedule

  if (m->cpu == home_cpu())
    {
      set_sched_params(m->sp);
      Mem::mp_mb();
      write_now(&m->in_progress, true);
      return reinterpret_cast<Migration*>(0x1); // bit one == 1 --> need to reschedule
    }

  return m; // need to do real migration
}

#line 915 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"



inline bool
Thread::migrate_away(Migration *inf, bool remote)
{
  assert (current() != this);
  assert (cpu_lock.test());
  bool resched = false;

  Cpu_number cpu = inf->cpu;
  //  LOG_MSG_3VAL(this, "MGi ", Mword(current()), (current_cpu() << 16) | cpu(), Context::current_sched());
  if (_timeout)
    _timeout->reset();

  if (!remote)
    {
      auto &rq = Sched_context::rq.current();

      // if we are in the middle of the scheduler, leave it now
      if (rq.schedule_in_progress == this)
        rq.schedule_in_progress = 0;

      rq.ready_dequeue(sched());

        {
          // Not sure if this can ever happen
          Sched_context *csc = rq.current_sched();
          if (csc == sched())
            {
              rq.set_current_sched(kernel_context(current_cpu())->sched());
              resched = true;
            }
        }
    }

  Sched_context *sc = sched_context();
  sc->set(inf->sp);
  sc->replenish();
  set_sched(sc);

  state_add_dirty(Thread_finish_migration);
  set_home_cpu(cpu);
  write_now(&inf->in_progress, true);
  return resched;
}

#line 961 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


inline bool
Thread::migrate_to(Cpu_number target_cpu, bool)
{
  if (!Cpu::online(target_cpu))
    {
      handle_drq();
      return false;
    }

  auto &rq = Sched_context::rq.current();
  if (state() & Thread_ready_mask && !in_ready_list())
    rq.ready_enqueue(sched());

  enqueue_timeout_again();

  return false;
}

#line 614 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

/**
 * The ia32 specific part of the thread constructor.
 */

inline void
Thread::arch_init()
{
  // clear out user regs that can be returned from the thread_ex_regs
  // system call to prevent covert channel
  Entry_frame *r = regs();
  r->flags(EFLAGS_IOPL_K | EFLAGS_IF | 2);	// ei
  r->cs(Gdt::gdt_code_user | Gdt::Selector_user);
  r->ss(Gdt::gdt_data_user | Gdt::Selector_user);

  r->sp(0);
  // after cs initialisation as ip() requires proper cs
  r->ip(0);
}

#line 647 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


inline void
Thread::check_f00f_bug(Trap_state *ts)
{
  // If we page fault on the IDT, it must be because of the F00F bug.
  // Figure out exception slot and raise the corresponding exception.
  // XXX: Should we also modify the error code?
  if (ts->_trapno == 14		// page fault?
      && ts->_cr2 >= Idt::idt()
      && ts->_cr2 <  Idt::idt() + Idt::_idt_max * 8)
    ts->_trapno = (ts->_cr2 - Idt::idt()) / 8;
}

#line 660 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"



inline unsigned
Thread::check_io_bitmap_delimiter_fault(Trap_state *ts)
{
  // check for page fault at the byte following the IO bitmap
  if (ts->_trapno == 14           // page fault?
      && (ts->_err & 4) == 0         // in supervisor mode?
      && ts->ip() <= Mem_layout::User_max   // delimiter byte accessed?
      && (ts->_cr2 == Mem_layout::Io_bitmap + Mem_layout::Io_port_max / 8))
    {
      // page fault in the first byte following the IO bitmap
      // map in the cpu_page read_only at the place
      Mem_space::Status result =
	mem_space()->v_insert(
	    Mem_space::Phys_addr(mem_space()->virt_to_phys_s0((void*)Kmem::io_bitmap_delimiter_page())),
	    Virt_addr(Mem_layout::Io_bitmap + Mem_layout::Io_port_max / 8),
	    Mem_space::Page_order(Config::PAGE_SHIFT),
	    Page::Attr(Page::Rights::R(), Page::Type::Normal(), Page::Kern::Global()));

      switch (result)
	{
	case Mem_space::Insert_ok:
	  return 1; // success
	case Mem_space::Insert_err_nomem:
	  // kernel failure, translate this into a general protection
	  // violation and hope that somebody handles it
	  ts->_trapno = 13;
	  ts->_err    =  0;
	  return 0; // fail
	default:
	  // no other error code possible
	  assert (false);
	}
    }

  return 1;
}

#line 699 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


inline bool
Thread::handle_sysenter_trap(Trap_state *ts, Address eip, bool from_user)
{
  if (EXPECT_FALSE
      ((ts->_trapno == 6 || ts->_trapno == 13)
       && (ts->_err & 0xffff) == 0
       && (eip < Mem_layout::User_max - 1)
       && (mem_space()->peek((Unsigned16*) eip, from_user)) == 0x340f))
    {
      // somebody tried to do sysenter on a machine without support for it
      WARN("tcb=%p killed:\n"
	   "\033[1;31mSYSENTER not supported on this machine\033[0m",
	   this);

      if (Cpu::have_sysenter())
	// GP exception if sysenter is not correctly set up..
        WARN("MSR_SYSENTER_CS: %llx", Cpu::rdmsr(MSR_SYSENTER_CS));
      else
	// We get UD exception on processors without SYSENTER/SYSEXIT.
        WARN("SYSENTER/EXIT not available.");

      return false;
    }

  return true;
}

#line 727 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"


inline int
Thread::handle_not_nested_trap(Trap_state *ts)
{
  // no kernel debugger present
  printf(" %p IP=" L4_PTR_FMT " Trap=%02lx [Ret/Esc]\n",
	 this, ts->ip(), ts->_trapno);

  int r;
  // cannot use normal getchar because it may block with hlt and irq's
  // are off here
  while ((r = Kconsole::console()->getchar(false)) == -1)
    Proc::pause();

  if (r == '\033')
    terminate (1);

  return 0;
}

#line 757 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-ia32.cpp"

inline Cpu_number Thread::dbg_find_cpu() { return Cpu_number::boot_cpu(); }

#line 154 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"


inline bool
Thread::check_known_inkernel_fault(Trap_state *ts)
{
  extern char in_slowtrap_exit_label_restore_gs[];
  extern char in_slowtrap_exit_label_restore_fs[];
  extern char in_slowtrap_exit_label_iret[];
  extern char vcpu_resume_label_gs[];
  extern char vcpu_resume_label_fs[];

  return    ts->ip() == (Mword)in_slowtrap_exit_label_restore_gs
         || ts->ip() == (Mword)in_slowtrap_exit_label_restore_fs
         || ts->ip() == (Mword)in_slowtrap_exit_label_iret
         || ts->ip() == (Mword)vcpu_resume_label_gs
         || ts->ip() == (Mword)vcpu_resume_label_fs;
}

#line 184 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"



inline int
Thread::check_trap13_kernel(Trap_state *ts)
{
  if (EXPECT_FALSE(ts->_trapno == 13 && (ts->_err & 3) == 0))
    {
      // First check if user loaded a segment register with 0 because the
      // resulting exception #13 can be raised from user _and_ kernel. If
      // the user tried to load another segment selector, the thread gets
      // killed.
      // XXX Should we emulate this too? Michael Hohmuth: Yes, we should.
      if (EXPECT_FALSE(!(ts->_ds & 0xffff)))
	{
	  Cpu::set_ds(Gdt::data_segment());
	  return 0;
	}
      if (EXPECT_FALSE(!(ts->_es & 0xffff)))
	{
	  Cpu::set_es(Gdt::data_segment());
	  return 0;
	}
      if (EXPECT_FALSE(ts->_ds & 0xfff8) == Gdt::gdt_code_user)
	{
	  WARN("%p eip=%08lx: code selector ds=%04lx",
               this, ts->ip(), ts->_ds & 0xffff);
	  Cpu::set_ds(Gdt::data_segment());
	  return 0;
	}
      if (EXPECT_FALSE(ts->_es & 0xfff8) == Gdt::gdt_code_user)
	{
	  WARN("%p eip=%08lx: code selector es=%04lx",
               this, ts->ip(), ts->_es & 0xffff);
	  Cpu::set_es(Gdt::data_segment());
	  return 0;
	}
      if (EXPECT_FALSE(ts->_fs & 0xfff8) == Gdt::gdt_code_user)
	{
	  WARN("%p eip=%08lx: code selector fs=%04lx",
               this, ts->ip(), ts->_fs & 0xffff);
	  ts->_fs = 0;
	  return 0;
	}
      if (EXPECT_FALSE(ts->_gs & 0xfff8) == Gdt::gdt_code_user)
	{
	  WARN("%p eip=%08lx: code selector gs=%04lx",
               this, ts->ip(), ts->_gs & 0xffff);
	  ts->_gs = 0;
	  return 0;
	}
    }

  return 1;
}

#line 187 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"


inline void
Thread::snd_regs(Syscall_frame *r)
{ _snd_regs = r; }

#line 286 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"


inline Thread::Check_sender
Thread::check_sender(Thread *sender, bool timeout)
{
  if (EXPECT_FALSE(is_invalid()))
    {
      sender->utcb().access()->error = L4_error::Not_existent;
      return Check_sender::Failed;
    }

  if (EXPECT_FALSE(!sender_ok(sender)))
    {
      if (!timeout)
        {
          sender->utcb().access()->error = L4_error::Timeout;
          return Check_sender::Failed;
        }

      sender->set_wait_queue(sender_list());
      sender->sender_enqueue(sender_list(), sender->sched_context()->prio());
      vcpu_set_irq_pending();
      return Check_sender::Queued;
    }

  return Check_sender::Ok;
}

#line 349 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"



inline void Thread::goto_sleep(L4_timeout const &t, Sender *sender, Utcb *utcb)
{
  IPC_timeout timeout;

  state_del_dirty(Thread_ready);
  setup_timer(t, utcb, &timeout);

  if (sender == this)
    switch_sched(sched(), &Sched_context::rq.current());

  schedule();

  reset_timeout();

  assert (state() & Thread_ready);
}

#line 368 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"



/**
 * @pre cpu_lock must be held
 */

inline Thread::Check_sender
Thread::handshake_receiver(Thread *partner, L4_timeout snd_t)
{
  assert(cpu_lock.test());

  switch (expect(partner->check_sender(this, !snd_t.is_zero()), Check_sender::Ok))
    {
    case Check_sender::Failed:
      return Check_sender::Failed;
    case Check_sender::Queued:
      state_add_dirty(Thread_send_wait);
      return Check_sender::Queued;
    default:
      partner->state_change_dirty(~(Thread_ipc_mask | Thread_ready), Thread_ipc_transfer);
      return Check_sender::Ok;
    }
}

#line 392 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"


inline void
Thread::set_ipc_error(L4_error const &e, Thread *rcv)
{
  utcb().access()->error = e;
  rcv->utcb().access()->error = L4_error(e, L4_error::Rcv);
}

#line 400 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"



inline Sender *
Thread::get_next_sender(Sender *sender)
{
  if (!sender_list()->empty())
    {
      if (sender) // closed wait
        {
          if (EXPECT_TRUE(sender->in_sender_list())
              && EXPECT_TRUE(sender_list() == sender->wait_queue()))
            return sender;
          return 0;
        }
      else // open wait
        {
          Sender *next = Sender::cast(sender_list()->first());
          assert (next->in_sender_list());
          set_partner(next);
          return next;
        }
    }
  return 0;
}

#line 425 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"


inline bool
Thread::activate_ipc_partner(Thread *partner, Cpu_number current_cpu,
                             bool do_switch, bool closed_wait)
{
  if (partner->home_cpu() == current_cpu)
    {
      auto &rq = Sched_context::rq.current();
      Sched_context *cs = rq.current_sched();
      do_switch = do_switch && (closed_wait || cs != sched());
      partner->state_change_dirty(~Thread_ipc_transfer, Thread_ready);
      if (do_switch)
        {
          schedule_if(switch_exec_locked(partner, Not_Helping) != Switch::Ok);
          return true;
        }
      else
        return deblock_and_schedule(partner);
    }

  partner->xcpu_state_change(~Thread_ipc_transfer, Thread_ready);
  return false;
}

#line 626 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"



inline bool
Thread::transfer_msg(L4_msg_tag tag, Thread *receiver,
                     Syscall_frame *sender_regs, L4_fpage::Rights rights)
{
  Syscall_frame* dst_regs = receiver->rcv_regs();

  bool success = copy_utcb_to(tag, receiver, rights);
  tag.set_error(!success);
  dst_regs->tag(tag);
  dst_regs->from(sender_regs->from_spec());

  // setup the reply capability in case of a call
  if (success && partner() == receiver)
    receiver->set_caller(this, rights);

  return success;
}

#line 1018 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"


/**
 * \pre Runs on the sender CPU
 * \retval true when the IPC was aborted
 * \retval false iff the IPC was already finished
 */

inline bool
Thread::abort_send(L4_error const &e, Thread *partner)
{
  state_del_dirty(Thread_full_ipc_mask);
  Abort_state abt = Abt_ipc_done;

  if (partner->home_cpu() == current_cpu())
    {
      if (in_sender_list())
        {
          sender_dequeue(partner->sender_list());
          partner->vcpu_update_state();
          abt = Abt_ipc_cancel;
        }
      else if (partner->in_ipc(this))
        abt = Abt_ipc_in_progress;
    }
  else
    abt = partner->Receiver::abort_send(this);

  switch (abt)
    {
    default:
    case Abt_ipc_done:
      return false;
    case Abt_ipc_cancel:
      utcb().access()->error = e;
      return true;
    case Abt_ipc_in_progress:
      state_add_dirty(Thread_ipc_transfer);
      while (state() & Thread_ipc_transfer)
        {
          state_del_dirty(Thread_ready);
          schedule();
        }
      return false;
    }
}

#line 1064 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"



/**
 * \pre Runs on the sender CPU
 * \retval true iff the IPC was finished during the wait
 * \retval false iff the IPC was aborted with some error
 */

inline bool
Thread::do_send_wait(Thread *partner, L4_timeout snd_t)
{
  IPC_timeout timeout;

  if (EXPECT_FALSE(snd_t.is_finite()))
    {
      Unsigned64 tval = snd_t.microsecs(Timer::system_clock(), utcb().access(true));
      // Zero timeout or timeout expired already -- give up
      if (tval == 0)
        return !abort_send(L4_error::Timeout, partner);

      set_timeout(&timeout, tval);
    }

  Mword ipc_state;

  while (((ipc_state = state() & (Thread_send_wait | Thread_ipc_abort_mask))) == Thread_send_wait)
    {
      state_del_dirty(Thread_ready);
      schedule();
    }

  reset_timeout();

  if (EXPECT_FALSE(ipc_state == (Thread_canceled | Thread_send_wait)))
    {
      state_del_dirty(Thread_full_ipc_mask);
      utcb().access()->error = L4_error::Canceled;
      return false;
    }

  if (EXPECT_FALSE(ipc_state == (Thread_cancel | Thread_send_wait)))
    return !abort_send(L4_error::Canceled, partner);

  if (EXPECT_FALSE(ipc_state == (Thread_timeout | Thread_send_wait)))
    return !abort_send(L4_error::Timeout, partner);

  return true;
}

#line 1113 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-ipc.cpp"


inline void
Thread::set_ipc_send_rights(L4_fpage::Rights c)
{
  _ipc_send_rights = c;
}

#line 213 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/thread-io.cpp"


inline int
Thread::handle_io_page_fault(Trap_state *ts)
{
  Address eip = ts->ip();
  if (!check_io_bitmap_delimiter_fault(ts))
    return 0;

  // Check for IO page faults. If we got exception #14, the IO bitmap page is
  // not available. If we got exception #13, the IO bitmap is available but
  // the according bit is set. In both cases we have to dispatch the code at
  // the faulting eip to determine the IO port and send an IO flexpage to our
  // pager. If it was a page fault, check the faulting address to prevent
  // touching userland.
  if (eip <= Mem_layout::User_max &&
      ((ts->_trapno == 13 && (ts->_err & 7) == 0) ||
       (ts->_trapno == 14 && Kmem::is_io_bitmap_page_fault(ts->_cr2))))
    {
      ts->_cr2 = 0;
      ts->_trapno = 13;
      ts->_err = 0;
      _recover_jmpbuf = 0;
      if (send_exception(ts))
        return 1;
      else
        return 2; // fail, don't send exception again
    }
  return 0; // fail
}

#line 318 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


inline Thread *Del_irq_chip::thread(Mword pin)
{ return (Thread*)pin; }

#line 322 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


inline Mword Del_irq_chip::pin(Thread *t)
{ return (Mword)t; }

#line 326 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread.cpp"


inline void
Del_irq_chip::unbind(Irq_base *irq)
{ thread(irq->pin())->remove_delete_irq(); }

#endif // thread_i_h
