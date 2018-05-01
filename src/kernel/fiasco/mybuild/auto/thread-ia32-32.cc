// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "thread.h"
#include "thread_i.h"

#line 171 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"

//----------------------------------------------------------------------------

#line 270 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"

//---------------------------------------------------------------------------

#line 285 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"

//---------------------------------------------------------------------------


#line 239 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"



void
Thread::user_invoke()
{
  user_invoke_generic();
  Mword cx = 0;

  if (current()->space()->is_sigma0())
    cx = Kmem::virt_to_phys(Kip::k());

  asm volatile
    ("  movl %%eax,%%esp \n"    // set stack pointer to regs structure
     "  movl %%edx,%%es  \n"
     "  movl %%edx,%%ds  \n"
     "  xorl %%eax,%%eax \n"    // clean out user regs
     "  xorl %%edx,%%edx \n"
     "  xorl %%esi,%%esi \n"
     "  xorl %%edi,%%edi \n"
     "  xorl %%ebx,%%ebx \n"
     "  xorl %%ebp,%%ebp \n"
     "  iret             \n"
     :                          // no output
     : "a" (nonull_static_cast<Return_frame*>(current()->regs())),
       "d" (Gdt::gdt_data_user | Gdt::Selector_user),
       "c" (cx)
     );

  // never returns here
}

#line 290 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/thread-ia32-32.cpp"

/** Call the nested trap handler (either Jdb::enter_kdebugger() or the
 * gdb stub. Setup our own stack frame */

int
Thread::call_nested_trap_handler(Trap_state *ts)
{
  Cpu_number log_cpu = dbg_find_cpu();
  unsigned long &ntr = nested_trap_recover.cpu(log_cpu);

#if 0
  printf("%s: lcpu%u sp=%p t=%lu nested_trap_recover=%ld\n",
         __func__, log_cpu, (void*)Proc::stack_pointer(), ts->_trapno, ntr);
#endif

  int ret;

  unsigned dummy1, dummy2, dummy3;

  struct
  {
    Mword pdir;
    FIASCO_FASTCALL int (*handler)(Trap_state*, unsigned);
    void *stack;
  } p;

  if (!ntr)
    {
      LOG_MSG(current(), "===== enter jdb =====");
      p.stack = dbg_stack.cpu(log_cpu).stack_top;
    }
  else
    p.stack = 0;

  p.pdir = Kernel_task::kernel_task()->virt_to_phys((Address)Kmem::dir());
  p.handler = nested_trap_handler;

  // don't set %esp if gdb fault recovery to ensure that exceptions inside
  // kdb/jdb don't overwrite the stack
  asm volatile
    ("mov    %%esp,%[d2]	\n\t"
     "cmpl   $0,(%[ntr])	\n\t"
     "jne    1f			\n\t"
     "mov    8(%[p]),%%esp	\n\t"
     "1:			\n\t"
     "incl   (%[ntr])		\n\t"
     "mov    %%cr3, %[d1]	\n\t"
     "push   %[d2]		\n\t"
     "push   %[p]		\n\t"
     "push   %[d1]		\n\t"
     "mov    (%[p]), %[d1]	\n\t"
     "mov    %[d1], %%cr3	\n\t"
     "call   *4(%[p])		\n\t"
     "pop    %[d1]		\n\t"
     "mov    %[d1], %%cr3	\n\t"
     "pop    %[p]		\n\t"
     "pop    %%esp		\n\t"
     "cmpl   $0,(%[ntr])	\n\t"
     "je     1f			\n\t"
     "decl   (%[ntr])		\n\t"
     "1:			\n\t"

     : [ret] "=a"  (ret),
       [d1]  "=&c" (dummy1),
       [d2]  "=&r" (dummy2),
             "=d"  (dummy3)
     : [ts]      "a" (ts),
       [cpu]     "d" (log_cpu),
       [p]       "S" (&p),
       [ntr]     "D" (&ntr)
     : "memory");

  if (!ntr)
    Cpu_call::handle_global_requests();

  return ret == 0 ? 0 : -1;
}
