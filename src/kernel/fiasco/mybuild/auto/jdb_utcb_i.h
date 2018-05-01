// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_utcb_i_h
#define jdb_utcb_i_h
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"

#include <cassert>
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
#include <cstdio>
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
#include "l4_types.h"
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
#include "config.h"
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
#include "jdb.h"
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
#include "jdb_kobject.h"
#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
#include "jdb_module.h"
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
#include "space.h"
#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
#include "static_init.h"
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
#include "thread_object.h"
#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
#include "thread_state.h"
#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"

class Jdb_utcb : public Jdb_module
{
public:
  Jdb_utcb() FIASCO_INIT;
private:
  static Kobject *thread;

public:  
#line 40 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
  static void
  print(Thread *t);
  
#line 63 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
  virtual Jdb_module::Action_code
  action( int cmd, void *&, char const *&, int &);
  
#line 82 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
  int
  num_cmds() const;
  
#line 87 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
  Jdb_module::Cmd
  const * cmds() const;
};
#line 96 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"

// --------------------------------------------------------------------------
// Handler for kobject list

class Jdb_kobject_utcb_hdl : public Jdb_kobject_handler
{
public:
  virtual bool show_kobject(Kobject_common *, int) { return true; }
  virtual ~Jdb_kobject_utcb_hdl() {}

public:  
#line 107 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
  static FIASCO_INIT
  void
  init();
  
#line 116 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
  bool
  handle_key(Kobject_common *o, int keycode);
};

#endif // jdb_utcb_i_h
