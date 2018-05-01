// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_obj_space_i_h
#define jdb_obj_space_i_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"

#include <cstdio>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"

#include "config.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
#include "jdb.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
#include "jdb_screen.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
#include "jdb_table.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
#include "jdb_kobject.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
#include "kernel_console.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
#include "kmem.h"
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
#include "keycodes.h"
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
#include "space.h"
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
#include "task.h"
#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
#include "thread_object.h"
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
#include "static_init.h"
#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
#include "types.h"
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"

class Jdb_obj_space : public Jdb_table, public Jdb_kobject_handler
{
public:
  enum Mode
  {
    Name,
    Raw,
    End_mode
  };

private:
  Address _base;
  Space  *_task;
  Mode    _mode;

  bool show_kobject(Kobject_common *, int) { return false; }

public:  
#line 52 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
  Jdb_obj_space(Address base = 0, int level = 0);
  
#line 62 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
  unsigned
  col_width(unsigned column) const;
  
#line 67 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
  unsigned long
  cols() const;
  
#line 72 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
  unsigned long
  rows() const;
  
#line 77 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
  void
  print_statline(unsigned long row, unsigned long col);
  
#line 100 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
  void
  print_entry(Cap_index entry);
  
#line 129 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
  void
  draw_entry(unsigned long row, unsigned long col);
  
#line 165 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
  unsigned
  key_pressed(int c, unsigned long &row, unsigned long &col);
  
#line 188 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
  bool
  handle_key(Kobject_common *o, int code);
  
#line 213 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
  Kobject_iface *
  item(Cap_index entry, unsigned *rights);

private:  
#line 139 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
  Cap_index
  index(unsigned long row, unsigned long col);
  
#line 147 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
  bool
  handle_user_keys(int c, Kobject_iface *o);
};

#endif // jdb_obj_space_i_h
