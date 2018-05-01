// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "boot_info.h"
#include "boot_info_i.h"

#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"

// these members needs to be initialized with some
// data to go into the data section and not into bss
unsigned Boot_info::_checksum_ro   = 15;
#line 24 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"
unsigned Boot_info::_checksum_rw   = 16;

#line 44 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"
//@}



void
Boot_info::init()
{}

#line 65 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"


void
Boot_info::reset_checksum_ro(void)
{
  set_checksum_ro(Checksum::get_checksum_ro());
}
