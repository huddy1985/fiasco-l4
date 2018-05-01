// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_kern_info.h"
#include "jdb_kern_info_i.h"

#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kern_info-apic.cpp"

static Jdb_kern_info_apic k_a INIT_PRIORITY(JDB_MODULE_INIT_PRIO+1);

#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kern_info-apic.cpp"


Jdb_kern_info_apic::Jdb_kern_info_apic()
  : Jdb_kern_info_module('a', "Local APIC state")
{
  Jdb_kern_info::register_subcmd(this);
}

#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kern_info-apic.cpp"


void
Jdb_kern_info_apic::show()
{
  if (!Config::apic)
    {
      puts("Local APIC disabled/not available");
      return;
    }

  Apic::id_show();
  Apic::timer_show();
  Apic::regs_show();
  putchar('\n');
  Apic::irr_show();
  Apic::isr_show();
}
