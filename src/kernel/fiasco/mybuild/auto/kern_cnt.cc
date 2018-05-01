// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "kern_cnt.h"
#include "kern_cnt_i.h"

#line 23 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kern_cnt.cpp"

Mword *Kern_cnt::kcnt[Max_slot];
#line 25 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kern_cnt.cpp"
Mword (*Kern_cnt::read_kcnt_fn[Max_slot])() = { read_kcnt1, read_kcnt2 };

#line 26 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kern_cnt.cpp"

Mword Kern_cnt::read_kcnt1() { return *kcnt[0]; }

#line 28 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kern_cnt.cpp"
Mword Kern_cnt::read_kcnt2() { return *kcnt[1]; }

#line 29 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kern_cnt.cpp"


Mword*
Kern_cnt::get_ctr(int num)
{
  Tracebuffer_status *status = Jdb_tbuf::status();

  return (Mword*)(num < Kern_cnt_max ? status->kerncnts + num : 0);
}

#line 38 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kern_cnt.cpp"


const char *
Kern_cnt::get_str(Mword num)
{
  switch (num)
    {
    case Kern_cnt_context_switch:    return "Context switches";
    case Kern_cnt_addr_space_switch: return "Address space switches";
    case Kern_cnt_shortcut_failed:   return "IPC shortcut failed";
    case Kern_cnt_shortcut_success:  return "IPC shortcut success";
    case Kern_cnt_irq:               return "Hardware interrupts";
    case Kern_cnt_ipc_long:          return "Long IPCs";
    case Kern_cnt_page_fault:        return "Page faults";
    case Kern_cnt_io_fault:          return "IO bitmap faults";
    case Kern_cnt_task_create:       return "Tasks created";
    case Kern_cnt_schedule:          return "Scheduler calls";
    case Kern_cnt_iobmap_tlb_flush:  return "IO bitmap TLB flushs";
    case Kern_cnt_exc_ipc:           return "Exception IPCs";
    default:                         return 0;
    }
}

#line 60 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kern_cnt.cpp"


int
Kern_cnt::mode(Mword slot, const char **mode, const char **name, Mword *event)
{
  Mword *c = 0;

  switch (slot)
    {
    case 0: c = kcnt[0]; break;
    case 1: c = kcnt[1]; break;
    }

  if (c)
    {
      Mword num = c - get_ctr(0);

      *mode  = "on";
      *name  = get_str(num);
      *event = 0x80000000 | num;
      return 1;
    }

  *mode = "off";
  *name = "";
  return 0;
}

#line 87 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kern_cnt.cpp"


int
Kern_cnt::setup_pmc(Mword slot, Mword event)
{
  if (slot>=Max_slot)
    return 0;

  if (!(event & 0x80000000))
    {
      kcnt[slot] = 0;
      Tb_entry::set_rdcnt(slot, 0);
      return 0;
    }

  event &= 0xff;
  if (event >= Kern_cnt_max)
    return 0;

  kcnt[slot] = get_ctr(event);
  Tb_entry::set_rdcnt(slot, read_kcnt_fn[slot]);
  return 1;
}
