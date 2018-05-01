// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef dirq_h
#define dirq_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/dirq-ia32-ux.cpp"
#include "std_macros.h"
#line 3 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/dirq-ia32-ux.cpp"
#include "types.h"

//
// INTERFACE definition follows 
//


#line 31 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/dirq-ia32-ux.cpp"
/** Hardware interrupt entry point.  Calls corresponding Dirq instance's
    Dirq::hit() method.
    @param irqobj hardware-interrupt object
 */
extern "C" FIASCO_FASTCALL
void
irq_interrupt(Mword _irqobj, Mword ip);

#endif // dirq_h
