// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "timer_tick.h"
#include "timer_tick_i.h"


#line 126 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timer_tick.cpp"


void
Timer_tick::Log::print(String_buffer *buf) const
{
  buf->printf("u-ip=0x%lx", user_ip);
}
