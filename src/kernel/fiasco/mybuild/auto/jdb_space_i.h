// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_space_i_h
#define jdb_space_i_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"

#include <climits>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include <cstring>
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include <cstdio>
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"

#include "jdb.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include "jdb_core.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include "jdb_module.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include "jdb_screen.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include "jdb_kobject.h"
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include "kernel_console.h"
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include "kernel_task.h"
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include "keycodes.h"
#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include "ram_quota.h"
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include "simpleio.h"
#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include "task.h"
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include "thread_object.h"
#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
#include "static_init.h"
#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"

class Jdb_space : public Jdb_module, public Jdb_kobject_handler
{
public:
  Jdb_space() FIASCO_INIT;
private:
  static Task *task;

public:  
#line 39 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
  bool
  show_kobject(Kobject_common *o, int lvl);
  
#line 54 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
  void
  show_kobject_short(String_buffer *buf, Kobject_common *o);
  
#line 92 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&, char const *&, int &);
  
#line 104 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 115 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
  int
  num_cmds() const;

private:  
#line 65 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
  static void
  print_space(Space *s);
  
#line 72 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
  void
  show(Task *t);
};

#endif // jdb_space_i_h
