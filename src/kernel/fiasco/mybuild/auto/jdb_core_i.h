// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_core_i_h
#define jdb_core_i_h
#line 138 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"

#include <cstring>
#line 140 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#include <cstdarg>
#line 142 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#include <cstdlib>
#line 143 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#include <cctype>
#line 144 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#include <simpleio.h>
#line 145 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"

#include "div32.h"
#line 147 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#include "l4_types.h"
#line 148 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#include "kernel_console.h"
#line 149 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#include "keycodes.h"
#line 150 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#include "jdb_prompt_ext.h"
#line 151 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#include "jdb_screen.h"
#line 152 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#include "processor.h"
#line 795 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


//===================
// Std JDB modules
//===================


/**
 * Private 'go' module.
 * 
 * This module handles the 'go' or 'g' command 
 * that continues normal program execution.
 */
class Go_m : public Jdb_module
{
public:
  Go_m() FIASCO_INIT;

public:  
#line 822 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
  Jdb_module::Action_code action( int, void *&, char const *&, int & );
  
#line 828 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
  int num_cmds() const;
  
#line 834 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
  Jdb_module::Cmd const * cmds() const;
};
#line 845 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


/**
 * Private 'help' module.
 * 
 * This module handles the 'help' or 'h' command and 
 * prints out a help screen.
 */
class Help_m : public Jdb_module
{
public:
  Help_m() FIASCO_INIT;

public:  
#line 864 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
  Jdb_module::Action_code action( int, void *&, char const *&, int & );
  
#line 954 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
  int num_cmds() const;
  
#line 960 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
  Jdb_module::Cmd const * cmds() const;
};

#endif // jdb_core_i_h
