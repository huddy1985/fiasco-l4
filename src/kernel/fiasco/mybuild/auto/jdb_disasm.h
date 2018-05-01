// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_disasm_h
#define jdb_disasm_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"

#include "jdb_module.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"
#include "l4_types.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"
#include "types.h"

//
// INTERFACE definition follows 
//

#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"

class Space;
#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"

class Jdb_disasm : public Jdb_module
{
public:
  Jdb_disasm() FIASCO_INIT;
  static bool avail() { return true; }
private:
  static char show_intel_syntax;
  static char show_lines;

public:  
#line 154 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"
  static bool
  show_disasm_line(int len, Address &addr,
  			     int show_symbols, Space *task);
  
#line 183 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"
  static Jdb_module::Action_code
  show(Address virt, Space *task, int level, bool do_clear_screen = false);
  
#line 311 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&args, char const *&fmt, int &next_char);
  
#line 336 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 350 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"
  int
  num_cmds() const;

private:  
#line 74 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"
  static bool
  disasm_line(char *buffer, int buflen, Address &addr,
  			int show_symbols, Space *task);
  
#line 93 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"
  static int
  at_symbol(Address addr, Space *task);
  
#line 100 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"
  static int
  at_line(Address addr, Space *task);
  
#line 108 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_disasm.cpp"
  static Address
  disasm_offset(Address &start, int offset, Space *task);
};

#endif // jdb_disasm_h
