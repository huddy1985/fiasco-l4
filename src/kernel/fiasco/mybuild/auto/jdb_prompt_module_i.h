// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_prompt_module_i_h
#define jdb_prompt_module_i_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"

#include <cstdio>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
#include <cstring>
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"

#include "jdb.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
#include "jdb_module.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
#include "jdb_screen.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
#include "kernel_console.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
#include "static_init.h"
#line 235 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"

#include "processor.h"
#line 254 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"

#include "cpu.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"


//===================
// Std JDB modules
//===================

/**
 * Jdb-prompt module.
 *
 * This module handles some commands that
 * change Jdb prompt and screen settings.
 */
class Jdb_pcm : public Jdb_module
{
public:
  Jdb_pcm() FIASCO_INIT;
private:
  static char subcmd;
  static char prompt_color;
  static char direct_enable;
  static int  screen_height;
  static int  screen_width;
  static unsigned input_time_block_sec;

  int wait_for_escape(Console *cons);

public:  
#line 107 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&args, char const *&fmt, int &);
  
#line 201 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
  int num_cmds() const;
  
#line 207 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
  Jdb_module::Cmd const * cmds() const;

private:  
#line 48 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
  int
  get_coords(Console *cons, unsigned &x, unsigned &y);
  
#line 81 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_prompt_module.cpp"
  void
  detect_screensize();
};

#endif // jdb_prompt_module_i_h
