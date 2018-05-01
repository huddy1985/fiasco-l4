// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef apic_i_h
#define apic_i_h
#line 103 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "cpu.h"
#line 200 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

#include <cassert>
#line 202 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include <cstdio>
#line 203 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include <cstdlib>
#line 204 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include <cstring>
#line 205 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

#include "config.h"
#line 208 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "cpu_lock.h"
#line 209 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "entry_frame.h"
#line 210 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "globals.h"
#line 211 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "io.h"
#line 212 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "kmem.h"
#line 213 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "kip.h"
#line 214 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "lock_guard.h"
#line 215 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "panic.h"
#line 216 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "processor.h"
#line 217 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "regdefs.h"
#line 218 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "pic.h"
#line 219 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "pit.h"
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-debug.cpp"

#include <cstdio>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-debug.cpp"
#include "simpleio.h"

//
// IMPLEMENTATION of inline functions follows
//


#line 242 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline Unsigned32
Apic::get_version()
{
  return reg_read(APIC_lvr) & 0xFF;
}

#line 381 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

// test if APIC present

inline int
Apic::test_present()
{
  return cpu().features() & FEAT_APIC;
}

#endif // apic_i_h
