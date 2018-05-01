// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef vkey_i_h
#define vkey_i_h
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"

#include "irq_chip.h"
#line 46 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"

#include <cstdio>
#line 48 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"

#include "config.h"
#line 50 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"
#include "cpu.h"
#line 51 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"
#include "globals.h"
#line 52 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"
#include "kernel_console.h"
#line 53 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"
#include "keycodes.h"

//
// IMPLEMENTATION of inline functions follows
//


#line 26 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"


inline bool
Vkey::is_debugger_entry_key(int key)
{
  return key == KEY_SINGLE_ESC;
}

#endif // vkey_i_h
