// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_exit_module_i_h
#define jdb_exit_module_i_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"

#include <cstdio>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"
#include "simpleio.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"

#include "jdb.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"
#include "jdb_module.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"
#include "jdb_screen.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"
#include "kernel_console.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"
#include "static_init.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"
#include "terminate.h"
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"
#include "types.h"
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"

/**
 * Private 'exit' module.
 *
 * This module handles the 'exit' or '^' command that
 * makes a call to exit() and virtually reboots the system.
 */
class Jdb_exit_module : public Jdb_module
{
public:
  Jdb_exit_module() FIASCO_INIT;

public:  
#line 29 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"
  Jdb_module::Action_code
  action (int cmd, void *&, char const *&, int &);
  
#line 51 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"
  int
  num_cmds() const;
  
#line 58 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"
  Jdb_module::Cmd const *
  cmds() const;

private:  
#line 97 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_exit_module.cpp"
  void
  vmx_off() const;
};

#endif // jdb_exit_module_i_h
