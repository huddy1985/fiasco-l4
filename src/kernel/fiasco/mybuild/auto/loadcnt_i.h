// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef loadcnt_i_h
#define loadcnt_i_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/loadcnt.cpp"

#include <cstring>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/loadcnt.cpp"
#include "koptions.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/loadcnt.cpp"
#include "perf_cnt.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/loadcnt.cpp"
#include "static_init.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/loadcnt.cpp"

class Loadcnt
{

public:  
#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/loadcnt.cpp"
  static void FIASCO_INIT_CPU
  init();
};

#endif // loadcnt_i_h
