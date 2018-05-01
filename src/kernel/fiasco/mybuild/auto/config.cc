// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "config.h"
#include "config_i.h"

#line 1 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
/*
 * Global kernel configuration
 */


#line 223 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"

KIP_KERNEL_ABI_VERSION(FIASCO_STRINGIFY(FIASCO_KERNEL_SUBVERSION));
#line 225 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"

// class variables
bool Config::esc_hack = false;
#line 228 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
#ifdef CONFIG_SERIAL
#line 229 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
int  Config::serial_esc = Config::SERIAL_NO_ESC;
#line 230 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
#endif
#line 231 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"

unsigned Config::tbuf_entries = 0x20000 / sizeof(Mword); //1024;
#line 233 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
bool Config::getchar_does_hlt_works_ok = false;
#line 234 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
unsigned Config::num_ap_cpus;
#line 235 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"

#ifdef CONFIG_FINE_GRAINED_CPUTIME
#line 237 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
KIP_KERNEL_FEATURE("fi_gr_cputime");
#line 238 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
#endif
#line 239 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"

//-----------------------------------------------------------------------------


#line 242 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"

FIASCO_INIT
void Config::init()
{
  init_arch();

  if (Koptions::o()->opt(Koptions::F_esc))
    esc_hack = true;

#ifdef CONFIG_SERIAL
  if (    Koptions::o()->opt(Koptions::F_serial_esc)
      && !Koptions::o()->opt(Koptions::F_noserial)
# ifdef CONFIG_KDB
      &&  Koptions::o()->opt(Koptions::F_nokdb)
# endif
      && !Koptions::o()->opt(Koptions::F_nojdb))
    {
      serial_esc = SERIAL_ESC_IRQ;
    }
#endif
}
