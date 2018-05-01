// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "l4_error.h"
#include "l4_error_i.h"

#line 49 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/l4_error.cpp"

static char const *__errors[] =
{ "OK", "timeout", "not existent", "canceled", "overflow",
  "xfer snd", "xfer rcv", "aborted", "map failed" };

#line 53 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/l4_error.cpp"




char const *
L4_error::str_error()
{
  return __errors[(_raw >> 1) & 0xf];
}
