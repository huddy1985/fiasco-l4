// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_log_i_h
#define jdb_log_i_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"

#include <climits>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include <cstring>
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include <cstdio>
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"

#include "jdb.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include "jdb_core.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include "jdb_module.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include "jdb_kobject.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include "jdb_list.h"
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include "jdb_screen.h"
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include "kernel_console.h"
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include "keycodes.h"
#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include "mem_unit.h"
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include "ram_quota.h"
#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include "simpleio.h"
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include "task.h"
#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
#include "static_init.h"
#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"


class Jdb_log_list : public Jdb_list
{
  friend class Jdb_log_list_hdl;
public:
  void *get_head() const { return _jdb_log_table; }
  char const *show_head() const { return "[Log]"; }

private:
  static Tb_log_table_entry *_end;

public:  
#line 118 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  void
  show_item(String_buffer *buffer, void *item) const;
  
#line 147 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  bool
  enter_item(void *item) const;
  
#line 232 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  int
  seek(int cnt, void **item);
  
#line 291 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  static void
  move_dups();

private:  
#line 130 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  static inline unsigned
  patch_val(Tb_log_table_entry const *e);
  
#line 135 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  static Tb_log_table_entry *
  find_next_log(const char *name, const char *sc,
                              Tb_log_table_entry *i);
  
#line 156 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  static void
  patch_item(Tb_log_table_entry const *e, unsigned char val);
  
#line 170 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  static bool
  equal(Tb_log_table_entry const *a, Tb_log_table_entry const *b);
  
#line 186 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  bool
  next(void **item);
  
#line 208 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  bool
  pref(void **item);
};
#line 34 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"

class Jdb_log_list_hdl : public Jdb_kobject_handler
{
public:
  virtual bool show_kobject(Kobject_common *, int) { return true; }

public:  
#line 42 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  bool
  invoke(Kobject_common *, Syscall_frame *f, Utcb *utcb);
};
#line 255 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"

class Jdb_log : public Jdb_module
{
public:
  Jdb_log() FIASCO_INIT;
private:

public:  
#line 337 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  Jdb_module::Action_code
  action(int, void *&, char const *&, int &);
  
#line 351 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 362 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"
  int
  num_cmds() const;
};

//
// IMPLEMENTATION of inline functions follows
//


#line 128 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_log.cpp"


inline unsigned
Jdb_log_list::patch_val(Tb_log_table_entry const *e)
{ return (e - _jdb_log_table) + Tbuf_dynentries; }

#endif // jdb_log_i_h
