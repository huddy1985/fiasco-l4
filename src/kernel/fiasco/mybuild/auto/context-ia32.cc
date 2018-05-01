// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "context.h"
#include "context_i.h"

#line 57 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/context-ia32.cpp"

//---------------------------------------------------------------------------

#line 78 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/context-ia32.cpp"

//--------------------------------------------------------------------


#line 32 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/context-ia32.cpp"

/** Thread context switchin.  Called on every re-activation of a thread
    (switch_exec()).  This method is public only because it is called from
    from assembly code in switch_cpu().
 */

void
Context::switchin_context(Context *from)
{
  assert (this == current());
  assert (state() & Thread_ready_mask);

  from->handle_lock_holder_preemption();
  // Set kernel-esp in case we want to return to the user.
  // kmem::kernel_sp() returns a pointer to the kernel SP (in the
  // TSS) the CPU uses when next switching from user to kernel mode.
  // regs() + 1 returns a pointer to the end of our kernel stack.
  Cpu::cpus.current().kernel_sp() = reinterpret_cast<Address>(regs() + 1);

  // switch to our page directory if necessary
  vcpu_aware_space()->switchin_context(from->vcpu_aware_space());

  // load new segment selectors
  load_segments();
}
