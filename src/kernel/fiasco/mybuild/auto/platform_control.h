// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef platform_control_h
#define platform_control_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/platform_control.cpp"

#include "types.h"

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/platform_control.cpp"

class Platform_control
{
public:
  static void init(Cpu_number);
  static bool cpu_shutdown_available();
  static int cpu_allow_shutdown(Cpu_number cpu, bool allow);
  static int system_suspend(Mword extra);

public:  
#line 3 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/platform_control-ia32.cpp"
  static inline void
  prepare_cpu_suspend(Cpu_number);
  
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/platform_control-ia32.cpp"
  static inline void FIASCO_NORETURN
  cpu_suspend(Cpu_number);
};
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/platform_control.cpp"

// ------------------------------------------------------------------------


//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/platform_control.cpp"

#include "l4_types.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/platform_control-ia32.cpp"

inline void
Platform_control::prepare_cpu_suspend(Cpu_number)
{
  asm volatile ("wbinvd");
}

#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/platform_control-ia32.cpp"

inline void FIASCO_NORETURN
Platform_control::cpu_suspend(Cpu_number)
{
  for (;;)
    asm volatile ("cli; wbinvd; hlt");
}

#line 28 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/platform_control.cpp"


inline bool
Platform_control::cpu_shutdown_available()
{ return false; }

#line 33 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/platform_control.cpp"


inline int
Platform_control::cpu_allow_shutdown(Cpu_number, bool)
{ return -L4_err::ENodev; }

#endif // platform_control_h
