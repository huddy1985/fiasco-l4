// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_dump_i_h
#define jdb_dump_i_h
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"

#include <cstdio>
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include <cctype>
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"

#include "config.h"
#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "jdb.h"
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "jdb_disasm.h"
#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "jdb_table.h"
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "jdb_input.h"
#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "jdb_input_task.h"
#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "jdb_module.h"
#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "jdb_screen.h"
#line 22 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "jdb_symbol.h"
#line 23 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "kernel_console.h"
#line 24 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "keycodes.h"
#line 25 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "simpleio.h"
#line 26 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "static_init.h"
#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "types.h"
#line 28 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "task.h"
#line 29 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"

class Jdb_dump : public Jdb_module, public Jdb_table
{
public:
  Jdb_dump() FIASCO_INIT;
  unsigned long cols() const { return Jdb_screen::cols(); }
  unsigned long rows() const { return Jdb_screen::rows(); }
  void draw_entry(unsigned long row, unsigned long col);
  void print_statline();

private:
  enum
    {
      B_MODE = 'b',	// byte
      C_MODE = 'c',	// char
      D_MODE = 'd',	// word
    };
  
  static const unsigned elb = sizeof(Mword);
  static char show_adapter_memory;
  static Address highlight_start, highlight_end;

  int level;
  Space *task;
  char dump_type;
  static Address virt_addr;

public:  
#line 74 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
  unsigned
  col_width(unsigned col) const;
  
#line 86 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
  void
  print_statline(unsigned long row, unsigned long col);
  
#line 176 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
  Jdb_module::Action_code
  dump(Address virt, Space *task, int level);
  
#line 194 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
  bool
  edit_entry(unsigned long row, unsigned long col, unsigned cx, unsigned cy);
  
#line 216 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
  unsigned
  key_pressed(int c, unsigned long &row, unsigned long &col);
  
#line 373 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&args, char const *&fmt, int &next_char);
  
#line 399 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 412 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
  int
  num_cmds() const;

private:  
#line 67 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
  inline Address
  virt(unsigned long row, unsigned long col);
};

//
// IMPLEMENTATION of inline functions follows
//


#line 65 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"


inline Address
Jdb_dump::virt(unsigned long row, unsigned long col)
{
  return (col-1) * elb + row * (cols()-1) * elb;
}

#endif // jdb_dump_i_h
