// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "irq_msi.h"
#include "irq_msi_i.h"

#line 146 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

STATIC_INITIALIZE(Irq_mgr_msi);

#line 31 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"


bool
Irq_chip_msi::alloc(Irq_base *irq, Mword pin) 
{ return valloc<Irq_chip_msi>(irq, pin, 0); }

#line 36 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"


void
Irq_chip_msi::unbind(Irq_base *irq) 
{
  extern char entry_int_apic_ignore[];
  //Mword n = irq->pin();
  // hm: no way to mask an MSI: mask(n);
  vfree(irq, &entry_int_apic_ignore);
  Irq_chip_icu::unbind(irq);
}

#line 47 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"


int
Irq_chip_msi::msg(Mword pin, Unsigned64, Irq_mgr::Msi_info *inf)
{
  // the requester ID does not matter, we cannot verify
  // without IRQ remapping
  if (pin >= _irqs)
    return -L4_err::ERange;

  inf->data = vector(pin) | (1 << 14);
  Unsigned32 apicid = Apic::apic.current()->cpu_id();
  inf->addr = 0xfee00000 | (apicid << 12);

  return 0;
}

#line 63 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

int
Irq_chip_msi::set_mode(Mword, Mode) 
{ return 0; }

#line 67 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

bool
Irq_chip_msi::is_edge_triggered(Mword) const 
{ return true; }

#line 71 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

void
Irq_chip_msi::set_cpu(Mword, Cpu_number) 
{}

#line 75 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

void
Irq_chip_msi::mask(Mword) 
{}

#line 79 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

void
Irq_chip_msi::ack(Mword) 
{ ::Apic::irq_ack(); }

#line 83 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

void
Irq_chip_msi::mask_and_ack(Mword) 
{ ::Apic::irq_ack(); }

#line 87 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

void
Irq_chip_msi::unmask(Mword) 
{}

#line 95 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

Irq_mgr::Irq
Irq_mgr_msi::chip(Mword irq) const 
{
  if (irq & 0x80000000)
    return Irq(&_chip, irq & ~0x80000000);
  else
    return _orig->chip(irq);
}

#line 104 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"


unsigned
Irq_mgr_msi::nr_irqs() const 
{ return _orig->nr_irqs(); }

#line 109 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"


unsigned
Irq_mgr_msi::nr_msis() const 
{ return _chip.nr_irqs(); }

#line 114 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"


int
Irq_mgr_msi::msg(Mword irq, Unsigned64 src, Msi_info *inf) const 
{
  if (irq & 0x80000000)
    return _chip.msg(irq & ~0x80000000, src, inf);
  else
    return -L4_err::ERange;
}

#line 124 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"

unsigned
Irq_mgr_msi::legacy_override(Mword irq) 
{
  if (irq & 0x80000000)
    return irq;
  else
    return _orig->legacy_override(irq);
}

#line 133 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_msi.cpp"


FIASCO_INIT
void
Irq_mgr_msi::init()
{
  if (Irq_mgr::mgr && Irq_mgr::mgr->nr_msis() > 0)
    return;

  Irq_mgr_msi *m;
  Irq_mgr::mgr = m =  new Boot_object<Irq_mgr_msi>(Irq_mgr::mgr);
  printf("Enable MSI support: chained IRQ mgr @ %p\n", m->_orig);
}
