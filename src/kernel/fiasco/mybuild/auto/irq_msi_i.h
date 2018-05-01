// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef irq_msi_i_h
#define irq_msi_i_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

#include "idt.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
#include "irq_chip.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
#include "irq_mgr.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
#include "irq_chip_ia32.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

#include "apic.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
#include "static_init.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
#include "boot_alloc.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

class Irq_chip_msi : public Irq_chip_icu, private Irq_chip_ia32
{
  friend class Irq_chip_ia32;
public:
  // this is somehow arbitrary
  enum { Max_msis = Int_vector_allocator::End - Int_vector_allocator::Base - 0x8 };
  Irq_chip_msi() : Irq_chip_ia32(Max_msis) {}

  unsigned nr_irqs() const override { return Irq_chip_ia32::nr_irqs(); }
  bool reserve(Mword pin) override { return Irq_chip_ia32::reserve(pin); }
  Irq_base *irq(Mword pin) const override { return Irq_chip_ia32::irq(pin); }

public:  
#line 33 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  bool
  alloc(Irq_base *irq, Mword pin) override;
  
#line 38 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  void
  unbind(Irq_base *irq) override;
  
#line 49 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  int
  msg(Mword pin, Unsigned64, Irq_mgr::Msi_info *inf);
  
#line 64 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  int
  set_mode(Mword, Mode) override;
  
#line 68 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  bool
  is_edge_triggered(Mword) const override;
  
#line 72 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  void
  set_cpu(Mword, Cpu_number) override;
  
#line 76 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  void
  mask(Mword) override;
  
#line 80 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  void
  ack(Mword) override;
  
#line 84 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  void
  mask_and_ack(Mword) override;
  
#line 88 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  void
  unmask(Mword) override;
  
#line 152 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  inline char const *
  chip_type() const override;
};
#line 24 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

class Irq_mgr_msi : public Irq_mgr
{
private:
  mutable Irq_chip_msi _chip;
  Irq_mgr *_orig;

public:  
#line 94 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  explicit inline Irq_mgr_msi(Irq_mgr *o);
  
#line 96 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  Irq_mgr::Irq
  chip(Mword irq) const override;
  
#line 106 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  unsigned
  nr_irqs() const override;
  
#line 111 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  unsigned
  nr_msis() const override;
  
#line 116 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  int
  msg(Mword irq, Unsigned64 src, Msi_info *inf) const override;
  
#line 125 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  unsigned
  legacy_override(Mword irq) override;
  
#line 135 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"
  static FIASCO_INIT
  void
  init();
};

//
// IMPLEMENTATION of inline functions follows
//


#line 150 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"


inline char const *
Irq_chip_msi::chip_type() const 
{ return "MSI"; }

#line 91 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"



inline Irq_mgr_msi::Irq_mgr_msi(Irq_mgr *o) : _orig(o) {}

#endif // irq_msi_i_h
