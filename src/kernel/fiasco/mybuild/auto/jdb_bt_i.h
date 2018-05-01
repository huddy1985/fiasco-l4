// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_bt_i_h
#define jdb_bt_i_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"

#include <cstdio>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
#include <cctype>
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"

#include "config.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
#include "jdb.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
#include "jdb_input.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
#include "jdb_input_task.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
#include "jdb_kobject.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
#include "jdb_lines.h"
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
#include "jdb_module.h"
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
#include "jdb_symbol.h"
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
#include "mem_layout.h"
#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
#include "keycodes.h"
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
#include "thread_object.h"
#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
#include "task.h"
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"

class Jdb_bt : public Jdb_module, public Jdb_input_task_addr
{
public:
  Jdb_bt() FIASCO_INIT;
private:
  static char     dummy;
  static char     first_char;
  static char     first_char_addr;
  static Address  addr;
  static Thread * tid;
  static Kobject *ko_tid;
  static Space *  task;

public:  
#line 307 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&args, char const *&fmt, int &next_char);
  
#line 414 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 428 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
  int
  num_cmds() const;

private:  
#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
  // determine the user level ebp and eip considering the current thread state
  static void
  get_user_eip_ebp(Address &eip, Address &ebp);
  
#line 112 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
  static Mword
  get_user_ebp_following_kernel_stack();
  
#line 163 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
  static void
  get_kernel_eip_ebp(Mword &eip1, Mword &eip2, Mword &ebp);
  
#line 215 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
  /** Show one backtrace item we found. Add symbol name and line info */
  static void
  show_item(int nr, Address ksp, Address addr, Address_type user);
  
#line 253 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
  static void
  show_without_ebp();
  
#line 267 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"
  static void
  show(Mword ebp, Mword eip1, Mword eip2, Address_type user);
};
#line 147 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bt-ia32-ux.cpp"

struct Is_current
{
  Thread *tid;
  mutable Thread *c;
  mutable Cpu_number cpu;

  void operator () (Cpu_number _cpu) const
  {
    Thread *t = Jdb::get_thread(_cpu);
    if (t == tid)
      { c = t; cpu = _cpu; }
  }

};

#endif // jdb_bt_i_h
