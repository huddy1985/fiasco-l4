// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_tbuf_show_i_h
#define jdb_tbuf_show_i_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"

#include <cstdio>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include <cstring>
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"

#include "config.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "cpu.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "jdb.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "jdb_disasm.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "jdb_input.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "jdb_module.h"
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "jdb_screen.h"
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "jdb_symbol.h"
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "jdb_regex.h"
#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "jdb_tbuf.h"
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "jdb_tbuf_output.h"
#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "kern_cnt.h"
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "kernel_console.h"
#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "keycodes.h"
#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "perf_cnt.h"
#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "simpleio.h"
#line 22 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "static_init.h"
#line 23 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
#include "thread.h"
#line 24 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"

class Entry_group
{
public:
  enum { Max_group_size = 10 };
  typedef Tb_entry::Group_order Group_order;

  struct Item
  {
    Tb_entry const *e;
    Mword y;
    Group_order order;
    Item() : e(0), y(0), order(Group_order::none()) {}
  };

  Entry_group() : _c(0) {}

  Item const &operator [] (unsigned i) const { return _i[i]; }
  Item &operator [] (unsigned i) { return _i[i]; }
  unsigned size() const { return _c; }
  bool full() const { return _c >= Max_group_size; }
  unsigned push_back(Tb_entry const *e, Mword y, Group_order t)
  {
    unsigned p = _c++;
    Item *u = &_i[p];
    u->e = e;
    u->y = y;
    u->order = t;
    return p;
  }

private:
  unsigned _c;
  Item _i[Max_group_size];
};
#line 59 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"

class Jdb_tbuf_show : public Jdb_module
{
public:
  Jdb_tbuf_show() FIASCO_INIT;

private:
  static char  _search_str[40];
  static char  _filter_str[40];
  static String_buf<512> _buffer_str;
  static Mword _status_type;
  static Mword _absy;
  static Mword _nr_cur;
  static Mword _nr_ref;
  static Mword _nr_pos[10];
  static Mword y_offset;

  enum
  {
    Index_mode        = 0, // number of event
    Tsc_delta_mode    = 1, // tsc ticks starting from last event
    Tsc_ref_mode      = 2, // tsc ticks starting from reference event
    Tsc_start_mode    = 3, // tsc ticks starting from 0
    Kclock_ref_mode   = 4, // kernel clock units (us) since reference event
    Kclock_start_mode = 5, // kernel clock units (us) since start of system
    Pmc1_delta_mode   = 6, // ticks of ctr 1 starting from last event
    Pmc2_delta_mode   = 7, // ticks of ctr 2 starting from last event
    Pmc1_ref_mode     = 8, // ticks of ctr 1 starting from reference event
    Pmc2_ref_mode     = 9, // ticks of ctr 2 starting from reference event
  };

  enum
  {
    Tbuf_start_line   = 3,
  };

  enum
  {
    Status_ok         = 0,
    Status_redraw     = 1,
    Status_error      = 2,
  };

  enum
  {
    Nil               = (Mword)-1,
  };

public:  
#line 1084 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&, char const *&, int &);
  
#line 1113 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 1129 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  int
  num_cmds() const;

private:  
#line 120 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  static void
  error(const char * const msg);
  
#line 127 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  static void
  show_perf_event_unit_mask_entry(Mword nr, Mword idx,
                                                 Mword unit_mask, int exclusive);
  
#line 143 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  static void
  show_perf_event(Mword nr);
  
#line 166 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  static Mword
  select_perf_event_unit_mask(Mword nr, Mword unit_mask);
  
#line 263 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  static Mword
  select_perf_event(Mword event);
  
#line 362 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  static void
  show_events(Mword n, Mword ref, Mword count, Unsigned8 mode,
                             Unsigned8 time_mode, int long_output);
  
#line 512 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  // search in tracebuffer
  static Mword
  search(Mword start, Mword entries, const char *str,
                        Unsigned8 direction);
  
#line 579 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  static void
  find_group(Entry_group *g, Tb_entry const *e, bool older, unsigned lines,
                            unsigned depth);
  
#line 634 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_show.cpp"
  static void
  show();
};

#endif // jdb_tbuf_show_i_h
