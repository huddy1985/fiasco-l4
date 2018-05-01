// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef irq_chip_pic_h
#define irq_chip_pic_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"

#include "i8259.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
#include "io.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
#include "irq_chip_ia32.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
#include "irq_mgr.h"

//
// INTERFACE definition follows 
//

#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"

/**
 * IRQ Chip based on the IA32 legacy PIC.
 *
 * 16 Vectors starting from Base_vector are statically assigned.
 */
class Irq_chip_ia32_pic :
  public Irq_chip_i8259<Io>,
  private Irq_chip_ia32,
  private Irq_mgr
{
  friend class Irq_chip_ia32;
public:
  bool reserve(Mword pin) override { return Irq_chip_ia32::reserve(pin); }
  Irq_base *irq(Mword pin) const override { return Irq_chip_ia32::irq(pin); }

private:
  enum { Base_vector = 0x20 };

public:  
#line 40 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
  bool
  alloc(Irq_base *irq, Mword irqn) override;
  
#line 53 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
  void
  unbind(Irq_base *irq) override;
  
#line 73 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
  unsigned
  nr_irqs() const override;
  
#line 78 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
  unsigned
  nr_msis() const override;
  
#line 99 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
  Irq_chip_ia32_pic();

private:  
#line 63 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"
  Irq_mgr::Irq
  chip(Mword irq) const override;
};

#endif // irq_chip_pic_h
