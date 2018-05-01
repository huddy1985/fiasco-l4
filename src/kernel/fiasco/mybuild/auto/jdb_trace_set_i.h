// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_trace_set_i_h
#define jdb_trace_set_i_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"

#include <cstdio>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"

#include "config.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"
#include "cpu.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"
#include "jdb_module.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"
#include "jdb_tbuf.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"
#include "jdb_trace.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"
#include "keycodes.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"
#include "simpleio.h"
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"
#include "static_init.h"
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
#include "syscalls.h"
#line 3 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
#include "idt.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
#include "jdb.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
#include "pm.h"
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"

class Jdb_set_trace : public Jdb_module
{
public:
  enum Mode { Off, Log, Log_to_buf, Trace, Use_c_short_cut, Use_slow_path };

  Jdb_set_trace() FIASCO_INIT;
  void ipc_tracing(Mode mode);

private:
  static char first_char;
  static char second_char;

public:  
#line 36 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&args, char const *&fmt, int &);
  
#line 232 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 255 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace_set.cpp"
  int
  num_cmds() const;

private:  
#line 22 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"
  static void
  set_ipc_vector();
};
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_trace_set-ia32-ux.cpp"

typedef void (Fast_entry_func)(void);

#endif // jdb_trace_set_i_h
