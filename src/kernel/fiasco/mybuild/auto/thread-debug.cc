// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "thread.h"
#include "thread_i.h"


#line 24 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread-debug.cpp"


void
Thread::Log_thread_exregs::print(String_buffer *buf) const
{
  buf->printf("D=%lx ip=%lx sp=%lx op=%s%s%s",
              id, ip, sp,
              op & Exr_cancel ? "Cancel" : "",
              ((op & (Exr_cancel | Exr_trigger_exception))
               == (Exr_cancel | Exr_trigger_exception))
               ? ","
               : ((op & (Exr_cancel | Exr_trigger_exception))
                  == 0 ? "0" : "") ,
              op & Exr_trigger_exception ? "TrExc" : "");
}
