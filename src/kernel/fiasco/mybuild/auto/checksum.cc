// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "checksum.h"
#include "checksum_i.h"


#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/checksum.cpp"

// calculate simple checksum over kernel text section and read-only data

unsigned Checksum::get_checksum_ro()
{
  unsigned *p, sum = 0;

  for (p = (unsigned*)&Mem_layout::start; 
       p < (unsigned*)&Mem_layout::etext; sum += *p++)
    ;

  return sum;
}

#line 25 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/checksum.cpp"


bool
Checksum::check_ro()
{ return Boot_info::get_checksum_ro() == get_checksum_ro(); }

#line 30 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/checksum.cpp"


// calculate simple checksum over kernel data section

unsigned Checksum::get_checksum_rw()
{
  unsigned *p, sum = 0;

  for (p = (unsigned*)&Mem_layout::data_start;
       p < (unsigned*)&Mem_layout::edata; sum += *p++)
    ;

  return sum;
}
