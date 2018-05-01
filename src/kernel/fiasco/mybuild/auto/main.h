// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef main_h
#define main_h
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/main-ia32-32.cpp"

#include "initcalls.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/main-ia32-32.cpp"
#include "std_macros.h"

//
// INTERFACE definition follows 
//

#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/main-ia32-32.cpp"

class Kernel_thread;

#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/main-ia32-32.cpp"
FIASCO_INIT
void
kernel_main(void);

#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/main-ia32.cpp"
extern "C" void __attribute__ ((noreturn))
_exit(int);

#line 76 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/main-ia32.cpp"
void
main_arch();

#endif // main_h
