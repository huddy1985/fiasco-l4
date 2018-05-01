// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "cpu_lock.h"
#include "cpu_lock_i.h"

#line 70 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_lock.cpp"

Cpu_lock cpu_lock INIT_PRIORITY(EARLY_INIT_PRIO);
#line 89 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_lock.cpp"
/**
 * Generic implementation of the CPU lock.
 * This implementation uses Proc::cli and
 * Proc::sti from the processor headers.
 */

