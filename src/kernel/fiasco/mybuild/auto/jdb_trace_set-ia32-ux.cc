// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_trace_set.h"
#include "jdb_trace_set_i.h"

#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"

extern "C" void entry_sys_ipc_log (void);
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
extern "C" void entry_sys_ipc_c (void);
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
extern "C" void entry_sys_ipc (void);
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
extern "C" void entry_sys_fast_ipc_log (void);
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
extern "C" void entry_sys_fast_ipc_c (void);
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
extern "C" void entry_sys_fast_ipc (void);
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"

extern "C" void sys_ipc_wrapper (void);
#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
extern "C" void ipc_short_cut_wrapper (void);
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
extern "C" void sys_ipc_log_wrapper (void);
#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
extern "C" void sys_ipc_trace_wrapper (void);
#line 93 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"

namespace {
struct Jdb_ipc_log_pm : Pm_object
{
  Jdb_ipc_log_pm(Cpu_number cpu) { register_pm(cpu); }
  void pm_on_resume(Cpu_number cpu)
  {
    void (*fast_entry)(void);

    if (Jdb_ipc_trace::_trace || Jdb_ipc_trace::_slow_ipc ||
        Jdb_ipc_trace::_log)
      fast_entry  = entry_sys_fast_ipc_log;
    else
      fast_entry  = entry_sys_fast_ipc_c;

    Cpu::cpus.cpu(cpu).set_fast_entry(fast_entry);
  }

  void pm_on_suspend(Cpu_number) {}
};

DEFINE_PER_CPU static Per_cpu<Jdb_ipc_log_pm> _pm(Per_cpu_data::Cpu_num);

}

#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"


void
Jdb_set_trace::set_ipc_vector()
{
  void (*int30_entry)(void);
  void (*fast_entry)(void);

  if (Jdb_ipc_trace::_trace || Jdb_ipc_trace::_slow_ipc ||
      Jdb_ipc_trace::_log)
    {
      int30_entry = entry_sys_ipc_log;
      fast_entry  = entry_sys_fast_ipc_log;
    }
  else
    {
      int30_entry = entry_sys_ipc_c;
      fast_entry  = entry_sys_fast_ipc_c;
    }

  Idt::set_entry(0x30, (Address) int30_entry, true);
  Jdb::on_each_cpu([fast_entry](Cpu_number cpu){
    Cpu::cpus.cpu(cpu).set_fast_entry(fast_entry);
  });

  if (Jdb_ipc_trace::_trace)
    syscall_table[0] = sys_ipc_trace_wrapper;
  else if ((Jdb_ipc_trace::_log && !Jdb_ipc_trace::_slow_ipc))
    syscall_table[0] = sys_ipc_log_wrapper;
  else
    syscall_table[0] = sys_ipc_wrapper;
}

#line 52 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"

void
Jdb_set_trace::ipc_tracing(Mode mode)
{
  switch (mode)
    {
    case Off:
      Jdb_ipc_trace::_trace = 0;
      Jdb_ipc_trace::_log = 0;
      Jdb_ipc_trace::_cshortcut = 0;
      Jdb_ipc_trace::_slow_ipc = 0;
      break;
    case Log:
      Jdb_ipc_trace::_trace = 0;
      Jdb_ipc_trace::_log = 1;
      Jdb_ipc_trace::_log_to_buf = 0;
      Jdb_ipc_trace::_cshortcut = 0;
      Jdb_ipc_trace::_slow_ipc = 0;
      break;
    case Log_to_buf:
      Jdb_ipc_trace::_trace = 0;
      Jdb_ipc_trace::_log = 1;
      Jdb_ipc_trace::_log_to_buf = 1;
      Jdb_ipc_trace::_cshortcut = 0;
      Jdb_ipc_trace::_slow_ipc = 0;
      break;
    case Trace:
      Jdb_ipc_trace::_trace = 1;
      Jdb_ipc_trace::_cshortcut = 0;
      Jdb_ipc_trace::_log = 0;
      Jdb_ipc_trace::_slow_ipc = 0;
      break;
    case Use_c_short_cut:
      Jdb_ipc_trace::_cshortcut = 1;
      break;
    case Use_slow_path:
      Jdb_ipc_trace::_slow_ipc = 1;
      break;
    }
  set_ipc_vector();
}
