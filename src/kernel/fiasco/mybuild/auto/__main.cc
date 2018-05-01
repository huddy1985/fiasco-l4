// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "__main.h"
#include "__main_i.h"

#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/__main.cpp"

void kernel_main(void);

#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/__main.cpp"

extern "C" FIASCO_FASTCALL FIASCO_INIT
void
__main(unsigned checksum_ro)
{
  /* set global to be used in the constructors */
  Boot_info::set_checksum_ro(checksum_ro);
  Boot_info::init();

  atexit(&static_destruction);
  static_construction();

  kernel_main();
  exit(0);
}
