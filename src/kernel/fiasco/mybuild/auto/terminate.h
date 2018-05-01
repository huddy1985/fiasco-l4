// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef terminate_h
#define terminate_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/terminate.cpp"

#include "std_macros.h"

//
// INTERFACE definition follows 
//


#line 33 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/terminate.cpp"
void set_exit_question(void (*eq)(void));

#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/terminate.cpp"
FIASCO_NORETURN
void
terminate (int exit_value);

#endif // terminate_h
