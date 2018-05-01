// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_misc_i_h
#define jdb_misc_i_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"

#include <cstdio>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
#include "config.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
#include "cpu.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
#include "jdb.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
#include "jdb_ktrace.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
#include "jdb_module.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
#include "jdb_symbol.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
#include "jdb_screen.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
#include "static_init.h"
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
#include "task.h"
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
#include "x86desc.h"
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"

class Jdb_misc_general : public Jdb_module
{
public:
  Jdb_misc_general() FIASCO_INIT;
private:
  static char first_char;

public:  
#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&, char const *&, int &);
  
#line 48 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 61 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
  int
  num_cmds() const;
};
#line 74 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"


//---------------------------------------------------------------------------//

class Jdb_misc_debug : public Jdb_module
{
public:
  Jdb_misc_debug() FIASCO_INIT;
private:
  static char     first_char;
  static Mword    task;

public:  
#line 101 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&args, char const *&fmt, int &);
  
#line 205 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 222 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
  int
  num_cmds() const;

private:  
#line 90 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
  static void
  show_lbr_entry(const char *str, Address addr);
  
#line 240 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
  static inline void
  show_ldt();
};
#line 286 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"

class Jdb_misc_info : public Jdb_module
{
public:
  Jdb_misc_info() FIASCO_INIT;
private:
  static char       first_char;
  static Address    addr;
  static Mword      value;
  static Unsigned64 value64;

public:  
#line 304 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&args, char const *&fmt, int &);
  
#line 389 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 405 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"
  int
  num_cmds() const;
};

//
// IMPLEMENTATION of inline functions follows
//


#line 239 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_misc-ia32-amd64.cpp"

inline void
Jdb_misc_debug::show_ldt()
{
  printf(" -- no LDT support\n");
}

#endif // jdb_misc_i_h
