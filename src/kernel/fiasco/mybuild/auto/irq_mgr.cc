// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "irq_mgr.h"
#include "irq_mgr_i.h"

#line 93 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_mgr.cpp"

Irq_mgr *Irq_mgr::mgr;

#line 135 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_mgr.cpp"


void
Irq_mgr::set_cpu(Mword irqnum, Cpu_number cpu) const
{
  Irq i = chip(irqnum);
  if (!i.chip)
    return;

  return i.chip->set_cpu(i.pin, cpu);
}
