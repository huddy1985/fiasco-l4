// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef mem_space_i_h
#define mem_space_i_h
#line 229 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"

//
// class Mem_space
//

#include "config.h"
#line 235 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
#include "globals.h"
#line 236 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
#include "l4_types.h"
#line 237 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
#include "kmem_alloc.h"
#line 238 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
#include "mem_unit.h"
#line 239 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
#include "paging.h"
#line 240 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
#include "panic.h"
#line 38 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space-user.cpp"

#include <cassert>
#line 40 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space-user.cpp"
#include "mem.h"
#line 66 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"

#include <cstring>
#line 68 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
#include <cstdio>
#line 69 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
#include "cpu.h"
#line 70 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
#include "l4_types.h"
#line 72 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
#include "paging.h"
#line 73 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
#include "std_macros.h"
#line 359 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"

#include <cassert>
#line 361 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
#include "l4_types.h"
#line 362 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
#include "kmem.h"
#line 364 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
#include "cpu_lock.h"
#line 365 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
#include "lock_guard.h"
#line 368 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"

#include <cstring>
#line 370 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
#include "config.h"

#endif // mem_space_i_h
