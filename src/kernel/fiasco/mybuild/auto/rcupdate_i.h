// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef rcupdate_i_h
#define rcupdate_i_h
#line 174 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"

#include "logdefs.h"
#line 176 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
#include "string_buffer.h"
#line 190 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"

#include "cpu.h"
#line 195 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
#include "mem.h"
#line 196 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
#include "static_init.h"
#line 197 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
#include "timeout.h"
#line 198 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
#include "logdefs.h"
#line 199 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"

// XXX: includes for debugging
// #include "logdefs.h"


class Rcu_timeout : public Timeout
{

private:  
#line 208 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/rcupdate.cpp"
  /**
   * Timeout expiration callback function
   * @return true if reschedule is necessary, false otherwise
   */
  
  bool
  expired();
};

#endif // rcupdate_i_h
