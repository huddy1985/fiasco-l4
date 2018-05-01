// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef cpu_i_h
#define cpu_i_h
#line 316 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

#include <cstdio>
#line 318 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include <cstring>
#line 319 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "config.h"
#line 320 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "panic.h"
#line 321 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "processor.h"
#line 1272 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

#include "config.h"
#line 1274 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "div32.h"
#line 1275 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "gdt.h"
#line 1276 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "globals.h"
#line 1277 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "initcalls.h"
#line 1278 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "io.h"
#line 1279 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "pit.h"
#line 1281 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "regdefs.h"
#line 1282 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "tss.h"
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"

#include "mem_layout.h"

//
// IMPLEMENTATION of inline functions follows
//


#line 1836 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

inline FIASCO_INIT_CPU_AND_PM
void
Cpu::init_indirect_branch_mitigation()
{}

#line 212 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"


inline void
Cpu::set_sysenter(void (*func)(void))
{
  _sysenter_eip = (Mword) func;
  wrmsr((Mword) func, 0, MSR_SYSENTER_EIP);
}

#endif // cpu_i_h
