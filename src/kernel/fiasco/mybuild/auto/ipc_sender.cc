// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "ipc_sender.h"
#include "ipc_sender_i.h"


#line 32 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_sender.cpp"


void
Ipc_sender_base::ipc_receiver_aborted()
{
  assert (wait_queue());
  set_wait_queue(0);
}
