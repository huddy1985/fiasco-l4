// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kmem_alloc_i_h
#define kmem_alloc_i_h
#line 79 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"

#include "config.h"
#line 81 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
#include "kip.h"
#line 83 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
#include "mem_region.h"
#line 84 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
#include "buddy_alloc.h"
#line 85 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
#include "panic.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem_alloc-ia32.cpp"

#include <cstdio>
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem_alloc-ia32.cpp"

#include "kip.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem_alloc-ia32.cpp"
#include "koptions.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem_alloc-ia32.cpp"
#include "mem_region.h"
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem_alloc-ia32.cpp"
#include "panic.h"
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem_alloc-ia32.cpp"
#include "types.h"
#line 171 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem_alloc-ia32.cpp"

#include "div32.h"

//
// IMPLEMENTATION of inline functions follows
//


#line 186 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem_alloc-ia32.cpp"


inline unsigned long
Kmem_alloc::orig_free()
{
  return _orig_free;
}

#endif // kmem_alloc_i_h
