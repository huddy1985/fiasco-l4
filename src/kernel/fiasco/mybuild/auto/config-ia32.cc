// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "config.h"
#include "config_i.h"

#line 109 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/config-ia32.cpp"

bool Config::hlt_works_ok = true;
#line 111 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/config-ia32.cpp"

bool Config::found_vmware = false;
#line 113 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/config-ia32.cpp"
char const Config::char_micro = '\265';
#line 114 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/config-ia32.cpp"
bool Config::apic = false;
#line 115 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/config-ia32.cpp"
unsigned Config::scheduler_irq_vector;
#line 116 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/config-ia32.cpp"

#ifdef CONFIG_WATCHDOG
#line 118 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/config-ia32.cpp"
bool Config::watchdog = false;
#line 119 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/config-ia32.cpp"
#endif
#line 120 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/config-ia32.cpp"

const char *const Config::kernel_warn_config_string =
#ifdef CONFIG_SCHED_RTC
  "  CONFIG_SCHED_RTC is on\n"
#endif
#ifndef CONFIG_INLINE
  "  CONFIG_INLINE is off\n"
#endif
#ifndef CONFIG_NDEBUG
  "  CONFIG_NDEBUG is off\n"
#endif
#ifndef CONFIG_NO_FRAME_PTR
  "  CONFIG_NO_FRAME_PTR is off\n"
#endif
#ifdef CONFIG_LIST_ALLOC_SANITY
  "  CONFIG_LIST_ALLOC_SANITY is on\n"
#endif
#ifdef CONFIG_BEFORE_IRET_SANITY
  "  CONFIG_BEFORE_IRET_SANITY is on\n"
#endif
#ifdef CONFIG_FINE_GRAINED_CPUTIME
  "  CONFIG_FINE_GRAINED_CPUTIME is on\n"
#endif
#ifdef CONFIG_JDB_ACCOUNTING
  "  CONFIG_JDB_ACCOUNTING is on\n"
#endif
  "";

#line 147 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/config-ia32.cpp"

FIASCO_INIT
void
Config::init_arch()
{
#ifdef CONFIG_WATCHDOG
  if (Koptions::o()->opt(Koptions::F_watchdog))
    {
      watchdog = true;
      apic = true;
    }
#endif

  if (Koptions::o()->opt(Koptions::F_nohlt))
    hlt_works_ok = false;

  if (Koptions::o()->opt(Koptions::F_apic))
    apic = true;

  if (Scheduler_mode == SCHED_APIC)
    apic = true;
}
