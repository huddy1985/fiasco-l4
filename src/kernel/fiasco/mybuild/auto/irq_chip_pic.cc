// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "irq_chip_pic.h"
#include "irq_chip_pic_i.h"


#line 38 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"


bool
Irq_chip_ia32_pic::alloc(Irq_base *irq, Mword irqn) 
{
  // no mor than 16 IRQs
  if (irqn > 0xf)
    return false;

  // PIC uses 16 vectors from Base_vector statically
  unsigned vector = Base_vector + irqn;
  return valloc<Irq_chip_ia32_pic>(irq, irqn, vector);
}

#line 51 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"


void
Irq_chip_ia32_pic::unbind(Irq_base *irq) 
{
  extern char entry_int_pic_ignore[];
  mask(irq->pin());
  vfree(irq, &entry_int_pic_ignore);
  Irq_chip::unbind(irq);
}

#line 61 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"


Irq_mgr::Irq
Irq_chip_ia32_pic::chip(Mword irq) const 
{
  if (irq < 16)
    return Irq(const_cast<Irq_chip_ia32_pic*>(this), irq);

  return Irq();
}

#line 71 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"


unsigned
Irq_chip_ia32_pic::nr_irqs() const 
{ return 16; }

#line 76 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"


unsigned
Irq_chip_ia32_pic::nr_msis() const 
{ return 0; }

#line 97 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_pic.cpp"


Irq_chip_ia32_pic::Irq_chip_ia32_pic()
: Irq_chip_i8259<Io>(0x20, 0xa0), Irq_chip_ia32(16)
{
  Irq_mgr::mgr = this;
  bool sfn = !Koptions::o()->opt(Koptions::F_nosfn);
  init(Base_vector, sfn,
       Config::Pic_prio_modify
       && (int)Config::Scheduler_mode == Config::SCHED_RTC);

  reserve(2); // reserve cascade irq
  reserve(7); // reserve spurious vect
}
