// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "context.h"
#include "context_i.h"

#line 146 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context-vcpu.cpp"


// --------------------------------------------------------------------------


#line 163 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context-vcpu.cpp"


void
Context::Vcpu_log::print(String_buffer *buf) const
{
  switch (type)
    {
    case 0:
    case 4:
      buf->printf("%sret pc=%lx sp=%lx state=%lx task=D:%lx",
                  type == 4 ? "f" : "", ip, sp, state, space);
      break;
    case 1:
      buf->printf("ipc from D:%lx task=D:%lx sp=%lx",
                  Kobject_dbg::pointer_to_id((Kobject*)ip), state, sp);
      break;
    case 2:
      buf->printf("exc #%x err=%lx pc=%lx sp=%lx state=%lx task=D:%lx",
                  (unsigned)trap, err, ip, sp, state, space);
      break;
    case 3:
      buf->printf("pf  pc=%lx pfa=%lx err=%lx state=%lx task=D:%lx",
                  ip, sp, err, state, space);
      break;
    default:
      buf->printf("vcpu: unknown");
      break;
    }
}
