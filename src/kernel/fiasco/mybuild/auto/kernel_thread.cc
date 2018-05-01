// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "kernel_thread.h"
#include "kernel_thread_i.h"

#line 125 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_thread.cpp"

// ------------------------------------------------------------------------


#line 46 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_thread.cpp"



Kernel_thread::Kernel_thread(Ram_quota *q)
: Thread_object(q, Thread::Kernel)
{}

#line 57 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_thread.cpp"

// the kernel bootstrap routine
FIASCO_INIT
void
Kernel_thread::bootstrap()
{
  // Initializations done -- Helping_lock can now use helping lock
  Helping_lock::threading_system_active = true;

  // we need per CPU data for our never running dummy CPU too
  // FIXME: we in fact need only the _pending_rqq lock
  Per_cpu_data_alloc::alloc(Cpu::invalid());
  Per_cpu_data::run_ctors(Cpu::invalid());
  set_current_cpu(Cpu::boot_cpu()->id());
  _home_cpu = Cpu::boot_cpu()->id();
  Mem::barrier();

  state_change_dirty(0, Thread_ready);		// Set myself ready

  Timer::init_system_clock();
  Sched_context::rq.current().set_idle(this->sched());

  Kernel_task::kernel_task()->make_current();

  // Setup initial timeslice
  Sched_context::rq.current().set_current_sched(sched());

  Timer_tick::setup(current_cpu());
  assert (current_cpu() == Cpu_number::boot_cpu()); // currently the boot cpu must be 0
  Mem_space::enable_tlb(current_cpu());

  Per_cpu_data::run_late_ctors(Cpu_number::boot_cpu());
  Per_cpu_data::run_late_ctors(Cpu::invalid());
  bootstrap_arch();

  Timer_tick::enable(current_cpu());
  Proc::sti();
  Watchdog::enable();
  printf("Calibrating timer loop... ");
  // Init delay loop, needs working timer interrupt
  Delay::init();
  printf("done.\n");

  run();
}

#line 102 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_thread.cpp"

/**
 * The idle loop
 * NEVER inline this function, because our caller is an initcall
 */
FIASCO_NOINLINE FIASCO_NORETURN
void
Kernel_thread::run()
{
  free_initcall_section();

  // No initcalls after this point!

  kernel_context(home_cpu(), this);

  Rcu::leave_idle(home_cpu());
  // init_workload cannot be an initcall, because it fires up the userland
  // applications which then have access to initcall frames as per kinfo page.
  init_workload();

  for (;;)
    idle_op();
}
