// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef filter_console_i_h
#define filter_console_i_h
#line 30 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/filter_console.cpp"

#include <cstdio>
#line 32 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/filter_console.cpp"
#include <cstring>
#line 33 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/filter_console.cpp"
#include <cctype>
#line 34 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/filter_console.cpp"
#include "keycodes.h"
#line 35 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/filter_console.cpp"
#include "delayloop.h"

//
// IMPLEMENTATION of inline functions follows
//


#line 108 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/filter_console.cpp"


inline int
Filter_console::getchar_timeout(unsigned timeout)
{
  if (!(_o->state() & INENABLED))
    return -1;

  int c;
  while ((c = _o->getchar(false)) == -1 && timeout--)
    Delay::delay(1);
  return c;
}

#endif // filter_console_i_h
