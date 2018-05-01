// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_timeout_i_h
#define jdb_timeout_i_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"

#include <cstdio>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include <cstring>
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"

#include "config.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "globals.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "ipc_timeout.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "jdb.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "jdb_kobject.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "jdb_kobject_names.h"
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "jdb_module.h"
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "jdb_screen.h"
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "kernel_console.h"
#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "keycodes.h"
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "kmem.h"
#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "simpleio.h"
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "static_init.h"
#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "timeout.h"
#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "timeslice_timeout.h"
#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
#include "thread.h"
#line 22 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"

class Jdb_list_timeouts : public Jdb_module
{
public:
  Jdb_list_timeouts() FIASCO_INIT;
private:
  enum
  {
    Timeout_timeslice = 1,
    Timeout_sc        = 2,
  };

public:  
#line 420 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&, char const *&, int &);
  
#line 432 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 445 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
  int
  num_cmds() const;

private:  
#line 187 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
  // use implicit knowledge to determine the type of a timeout because we
  // cannot use dynamic_cast (we compile with -fno-rtti)
  
  static int
  get_type(Timeout *t);
  
#line 204 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
  static Thread*
  get_owner(Timeout *t);
  
#line 222 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
  static void
  show_header();
  
#line 230 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
  static void
  list_timeouts_show_timeout(Timeout *t);
  
#line 282 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
  static void
  complete_show();
  
#line 297 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_timeout.cpp"
  static void
  list();
};

#endif // jdb_timeout_i_h
