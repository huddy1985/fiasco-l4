// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "irq_chip.h"
#include "irq_chip_i.h"

#line 216 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_chip.cpp"

Irq_chip_soft Irq_chip_soft::sw_chip INIT_PRIORITY(EARLY_INIT_PRIO);
#line 218 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_chip.cpp"
Irq_base *(*Irq_base::dcast)(Kobject_iface *);

#line 341 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_chip.cpp"


void
Irq_base::Irq_log::print(String_buffer *buf) const
{
  Kobject_dbg::Const_iterator irq = Kobject_dbg::pointer_to_obj(obj);

  buf->printf("0x%lx/%lu @ chip %s(%p) ", pin, pin, chip->chip_type(), chip);

  if (irq != Kobject_dbg::end())
    buf->printf("D:%lx", irq->dbg_id());
  else
    buf->printf("irq=%p", obj);
}
