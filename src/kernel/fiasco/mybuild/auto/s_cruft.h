// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef s_cruft_h
#define s_cruft_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/cxxlib/s_cruft.cpp"

#include <cstddef>			// for size_t

//
// INTERFACE definition follows 
//


#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/cxxlib/s_cruft.cpp"
// do not allow calls to these OSKit routines.  We have to provide
// these functions because libamm references them.
 
extern "C" __attribute__((noreturn)) void *smalloc(size_t);

#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/cxxlib/s_cruft.cpp"
extern "C" __attribute__((noreturn)) void sfree(void *, size_t);

#endif // s_cruft_h
