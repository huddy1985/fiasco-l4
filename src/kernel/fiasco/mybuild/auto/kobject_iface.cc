// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "kobject_iface.h"
#include "kobject_iface_i.h"

#line 48 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"

Kobject_iface::Factory_func *Kobject_iface::factory[Max_factory_index + 1];
#line 101 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"

// ------------------------------------------------------------------------


#line 67 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"


Kobject_iface *
Kobject_iface::downgrade(unsigned long del_attribs)
{ (void)del_attribs; return this; }

#line 72 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"


void
Kobject_iface::set_factory(long label, Factory_func *f)
{
  if (label > 0 || -label > Max_factory_index)
    panic("error: registering factory for invalid protocol/label: %ld\n",
          label);

  if (factory[-label])
    panic("error: factory for protocol/label %ld already registered: %p\n",
          label, factory[-label]);

  factory[-label] = f;
}
