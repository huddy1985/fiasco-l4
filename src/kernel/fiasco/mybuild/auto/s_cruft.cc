// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "s_cruft.h"
#include "s_cruft_i.h"


#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/cxxlib/s_cruft.cpp"

// do not allow calls to these OSKit routines.  We have to provide
// these functions because libamm references them.
 
extern "C" __attribute__((noreturn)) void *smalloc(size_t)
{
  panic("smalloc called");
}

#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/cxxlib/s_cruft.cpp"
   
extern "C" __attribute__((noreturn)) void sfree(void *, size_t)
{
  panic("sfree called");
}
