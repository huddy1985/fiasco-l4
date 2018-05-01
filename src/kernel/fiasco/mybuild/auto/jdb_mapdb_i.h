// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_mapdb_i_h
#define jdb_mapdb_i_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"

#include <cstdio>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"

#include "jdb.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "jdb_input.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "jdb_screen.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "kernel_console.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "kobject.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "keycodes.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "mapdb.h"
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "mapdb_i.h"
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "map_util.h"
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "simpleio.h"
#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "static_init.h"
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "task.h"
#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "jdb_kobject.h"
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
#include "jdb_kobject_names.h"
#line 473 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"

#include "dbg_page_info.h"
#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"

class Jdb_mapdb : public Jdb_module
{
  friend class Jdb_kobject_mapdb_hdl;
public:
  Jdb_mapdb() FIASCO_INIT;
private:
  static Mword pagenum;
  static char  subcmd;

public:  
#line 302 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&args, char const *&fmt, int &next_char);
  
#line 361 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 376 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
  int
  num_cmds() const;

private:  
#line 49 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
  static unsigned long long
  val(Mdb_types::Pfn p, Mdb_types::Order base_size);
  
#line 57 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
  static bool
  show_tree(Treemap* pages, Mapping::Pcnt offset, Mdb_types::Order base_size,
                       unsigned &screenline, unsigned indent = 1);
  
#line 184 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
  static Address
  end_address (Mapdb* mapdb);
  
#line 191 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
  static void
  show(Mapping::Pfn page, char which_mapdb);
  
#line 477 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
  static bool
  show_simple_tree(Kobject_common *f, unsigned indent = 1);
  
#line 549 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
  static void
  dump_all_cap_trees();
};
#line 388 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"

// --------------------------------------------------------------------------
// Handler for kobject list

class Jdb_kobject_mapdb_hdl : public Jdb_kobject_handler
{
public:
  virtual bool show_kobject(Kobject_common *, int) { return true; }
  virtual ~Jdb_kobject_mapdb_hdl() {}

public:  
#line 399 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
  static FIASCO_INIT
  void
  init();
  
#line 408 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
  bool
  handle_key(Kobject_common *o, int keycode);
};

#endif // jdb_mapdb_i_h
