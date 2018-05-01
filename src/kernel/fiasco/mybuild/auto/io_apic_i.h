// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef io_apic_i_h
#define io_apic_i_h
#line 88 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

#include "acpi.h"
#line 90 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
#include "apic.h"
#line 92 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
#include "kmem.h"
#line 93 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
#include "kip.h"
#line 95 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
#include "boot_alloc.h"
#line 96 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
#include "warn.h"

//
// IMPLEMENTATION of inline functions follows
//


#line 451 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline void
Io_apic::_mask(unsigned irq)
{
  auto g = lock_guard(_l);
  //assert(irq <= _apic->num_entries());
  _apic->modify(0x10 + irq * 2, 1UL << 16, 0);
}

#line 460 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline void
Io_apic::_unmask(unsigned irq)
{
  auto g = lock_guard(_l);
  //assert(irq <= _apic->num_entries());
  _apic->modify(0x10 + irq * 2, 0, 1UL << 16);
}

#endif // io_apic_i_h
