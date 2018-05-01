// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef io_apic_remapped_i_h
#define io_apic_remapped_i_h
#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"

#include "acpi_dmar.h"
#line 23 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
#include "intel_iommu.h"
#line 24 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"

#include "types.h"
#line 26 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
#include "idt.h"
#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
#include "irq_chip.h"
#line 28 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
#include "irq_mgr.h"
#line 29 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
#include "irq_chip_ia32.h"
#line 30 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"

#include "apic.h"
#line 32 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
#include "boot_alloc.h"
#line 33 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
#include "io_apic.h"
#line 34 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
#include "cxx/static_vector"
#line 35 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
#include "intel_iommu.h"
#line 36 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"

#include "warn.h"
#line 38 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"

class Irq_chip_rmsi : public Irq_chip_icu, private Irq_chip_ia32
{
  friend class Irq_chip_ia32;
public:
  // this is somehow arbitrary
  enum { Max_msis = Int_vector_allocator::End - Int_vector_allocator::Base - 0x8 };
  explicit Irq_chip_rmsi(Intel::Io_mmu::Irte volatile *irt)
  : Irq_chip_ia32(Max_msis), _irt(irt)
  {}

  unsigned nr_irqs() const override { return Irq_chip_ia32::nr_irqs(); }
  bool reserve(Mword pin) override { return Irq_chip_ia32::reserve(pin); }
  Irq_base *irq(Mword pin) const override { return Irq_chip_ia32::irq(pin); }

  Intel::Io_mmu::Irte volatile *_irt;

public:  
#line 72 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
  bool
  alloc(Irq_base *irq, Mword pin) override;
  
#line 77 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
  void
  unbind(Irq_base *irq) override;
  
#line 92 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
  int
  msg(Mword pin, Unsigned64 src, Irq_mgr::Msi_info *inf);
  
#line 121 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
  int
  set_mode(Mword, Mode) override;
  
#line 125 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
  bool
  is_edge_triggered(Mword) const override;
  
#line 129 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
  void
  set_cpu(Mword pin, Cpu_number cpu) override;
  
#line 151 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
  void
  mask(Mword pin) override;
  
#line 169 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
  void
  ack(Mword) override;
  
#line 173 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
  void
  mask_and_ack(Mword pin) override;
  
#line 192 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
  void
  unmask(Mword pin) override;
  
#line 438 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
  inline char const *
  chip_type() const override;

private:  
#line 63 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
  inline void
  inv_iec(unsigned vect);
};
#line 55 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"

class Irq_mgr_rmsi : public Io_apic_mgr
{
public:
  mutable Irq_chip_rmsi _chip;

public:  
#line 215 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
  explicit inline Irq_mgr_rmsi(Intel::Io_mmu::Irte volatile *irt);
  
#line 219 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
  Irq_mgr::Irq
  chip(Mword irq) const override;
  
#line 229 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
  unsigned
  nr_irqs() const override;
  
#line 234 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
  unsigned
  nr_msis() const override;
  
#line 239 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
  int
  msg(Mword irq, Unsigned64 src, Msi_info *inf) const override;
  
#line 248 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
  unsigned
  legacy_override(Mword irq) override;
};

//
// IMPLEMENTATION of inline functions follows
//


#line 436 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"


inline char const *
Irq_chip_rmsi::chip_type() const 
{ return "rMSI"; }

#line 212 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"



inline Irq_mgr_rmsi::Irq_mgr_rmsi(Intel::Io_mmu::Irte volatile *irt)
: _chip(irt)
{}

#endif // io_apic_remapped_i_h
