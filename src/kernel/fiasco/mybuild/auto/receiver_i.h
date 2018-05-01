// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef receiver_i_h
#define receiver_i_h
#line 56 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"

#include "l4_types.h"
#line 59 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"

#include "cpu_lock.h"
#line 61 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
#include "globals.h"
#line 62 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
#include "lock_guard.h"
#line 63 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
#include "logdefs.h"
#line 65 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
#include "thread_lock.h"
#line 66 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"
#include "entry_frame.h"
#line 304 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/receiver.cpp"


// --------------------------------------------------------------------------

struct Ipc_remote_dequeue_request
{
  Receiver *partner;
  Sender *sender;
  Receiver::Abort_state state;
};

#endif // receiver_i_h
