// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "keyb.h"
#include "keyb_i.h"


#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/keyb.cpp"


int
Keyb::write(char const *, size_t len)
{
  return len;
}

#line 34 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/keyb.cpp"


Mword
Keyb::get_attributes() const
{
  return DIRECT | IN;
}
