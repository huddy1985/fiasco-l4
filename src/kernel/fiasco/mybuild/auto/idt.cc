// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "idt.h"
#include "idt_i.h"

#line 1 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"
/*
 * Fiasco Interrupt Descriptor Table (IDT) Code
 */


#line 36 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"

Address Idt::_idt_pa;
#line 189 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"


//---------------------------------------------------------------------------

#line 214 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"

extern "C" void entry_int_timer();
#line 216 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"
extern "C" void entry_int_timer_slow();
#line 217 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"
extern "C" void entry_int7();
#line 218 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"
extern "C" void entry_intf();
#line 219 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"
extern "C" void entry_int_pic_ignore();

#line 38 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"

/**
 * IDT write-protect/write-unprotect function.
 * @param writable true if IDT should be made writable, false otherwise
 */

void
Idt::set_writable(bool writable)
{
  auto e = Kmem::current_cpu_kdir()->walk(Virt_addr(_idt));

  // Make sure page directory entry is valid and not a 4MB page
  assert (e.is_valid() && e.level == Pdir::Depth);

  if (writable)
    e.add_attribs(Pt_entry::Writable); // Make read-write
  else
    e.del_attribs(Pt_entry::Writable); // Make read-only

  Mem_unit::tlb_flush (_idt);
}

#line 59 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"

FIASCO_INIT
void
Idt::init_table(Idt_init_entry *src, Idt_entry *idt)
{
  while (src->entry)
    {
      assert (src->vector < _idt_max);
      idt[src->vector] =
        ((src->type & 0x1f) == 0x05) // task gate?
        ? Idt_entry(src->entry, src->type)
        : Idt_entry(src->entry, Gdt::gdt_code_kernel, src->type);
      src++;
    }
}

#line 74 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"

/**
 * IDT initialization function. Sets up initial interrupt vectors.
 * It also write-protects the IDT because of the infamous Pentium F00F bug.
 */
FIASCO_INIT
void
Idt::init()
{
  assert (_idt_max * sizeof(Idt_entry) <= Config::PAGE_SIZE && "IDT too large");
  auto alloc = Kmem_alloc::allocator();
  Idt_entry *idt = (Idt_entry *)alloc->unaligned_alloc(Config::PAGE_SIZE);
  if (!idt)
    panic("IDT allocation failure: %d", __LINE__);

  _idt_pa = Mem_layout::pmem_to_phys(idt);
  memset(idt, 0, Config::PAGE_SIZE);
  init_table((Idt_init_entry*)&idt_init_table, idt);

  init_current_cpu();
}

#line 95 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"


void
Idt::init_current_cpu()
{
  auto d = Kmem::current_cpu_kdir()->walk(Virt_addr(_idt), Pdir::Depth);
  if (d.level != Pdir::Depth)
    panic("IDT allocation failure: %d: level=%d %lx", __LINE__,
          d.level, *d.pte);

  if (!d.is_valid())
    d.set_page(_idt_pa, Pt_entry::Referenced | Pt_entry::global());

  if (d.page_addr() != _idt_pa)
    panic("IDT allocation failure: %d: some other page mapped here %lx",
          __LINE__, _idt);

  load();
}

#line 114 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"



void
Idt::load()
{
  Pseudo_descriptor desc(_idt, _idt_max*sizeof(Idt_entry)-1);
  set(&desc);
}

#line 123 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"


void
Idt::set_entry(unsigned vector, Idt_entry entry)
{
  assert (vector < _idt_max);

  set_writable(true);

  Idt_entry *entries = (Idt_entry*)_idt;
  entries[vector] = entry;
  set_writable(false);
}

#line 136 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"


Idt_entry const &
Idt::get(unsigned vector)
{
  assert (vector < _idt_max);

  return ((Idt_entry*)_idt)[vector];
}

#line 145 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"

/**
 * IDT patching function.
 * Allows to change interrupt gate vectors at runtime.
 * It makes the IDT writable for the duration of this operation.
 * @param vector interrupt vector to be modified
 * @param func new handler function for this interrupt vector
 * @param user true if user mode can use this vector, false otherwise
 */

void
Idt::set_entry(unsigned vector, Address entry, bool user)
{
  assert (vector < _idt_max);

  set_writable(true);

  Idt_entry *entries = (Idt_entry*)_idt;
  if (entry)
    entries[vector] = Idt_entry(entry, Gdt::gdt_code_kernel,
			        Idt_entry::Access_intr_gate |
			        (user ? Idt_entry::Access_user 
			              : Idt_entry::Access_kernel));
  else
    entries[vector].clear();

  set_writable(false);
}

#line 173 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"


Address
Idt::get_entry(unsigned vector)
{
  assert (vector < _idt_max);
  Idt_entry *entries = (Idt_entry*)_idt;
  return entries[vector].offset();
}

#line 220 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"

/**
 * Set IDT vector to the normal timer interrupt handler.
 */

void
Idt::set_vectors_run()
{
  Address func = (Config::esc_hack || Config::watchdog ||
		  Config::serial_esc==Config::SERIAL_ESC_NOIRQ)
		    ? (Address)entry_int_timer_slow // slower for debugging
		    : (Address)entry_int_timer;     // non-debugging

  set_entry(Config::scheduler_irq_vector, func, false);
#if 0
  if (!Irq_chip::hw_chip->is_free(0x7))
    Irq_chip::hw_chip->reset(0x07);

  if (!Irq_chip::hw_chip->is_free(0xf))
    Irq_chip::hw_chip->reset(0x0f);
#endif
}
