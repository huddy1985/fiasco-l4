// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef processor_h
#define processor_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/processor.cpp"

#include "types.h"

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/processor.cpp"

/// Central processor specific methods.
class Proc
{
public:

  typedef Mword Status;

  /// Block external interrupts
  static void cli();

  /// Unblock external inetrrupts
  static void sti();

  /// Are external interrupts enabled ?
  static Status interrupts();

  /// Block external interrupts and save the old state
  static Status cli_save();

  /// Conditionally unblock external interrupts
  static void sti_restore( Status );

  static void pause();

  static void halt();

  static void irq_chance();

  static void stack_pointer(Mword sp);

  static Mword stack_pointer();

  static Mword program_counter();

  static inline
  void preemption_point()
  {
    sti();
    irq_chance();
    cli();
  }


public:  
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/ia32/processor-ia32.cpp"
  static inline Cpu_phys_id
  cpu_id();
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/ia32/processor-ia32.cpp"


inline Cpu_phys_id
Proc::cpu_id()
{
  Mword eax, ebx,ecx, edx;
  asm volatile ("cpuid" : "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx)
                        : "a" (1));
  return Cpu_phys_id((ebx >> 24) & 0xff);
}

#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/ia32/processor-ia32.cpp"


inline Mword Proc::stack_pointer()
{
  Mword sp;
  asm volatile ("movl %%esp, %0" : "=r" (sp));
  return sp;
}

#line 23 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/ia32/processor-ia32.cpp"


inline void Proc::stack_pointer(Mword sp)
{
  asm volatile ("movl %0, %%esp" : : "r" (sp));
}

#line 29 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/ia32/processor-ia32.cpp"


inline Mword Proc::program_counter()
{
  Mword pc;
  asm volatile ("call 1f; 1: pop %0" : "=r" (pc));
  return pc;
}

#line 37 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/ia32/processor-ia32.cpp"


inline void Proc::pause()
{
  asm volatile (".byte 0xf3, 0x90 #pause" );
}

#line 43 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/ia32/processor-ia32.cpp"


inline void Proc::halt()
{
  asm volatile ("hlt");
}

#line 49 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/ia32/processor-ia32.cpp"


inline void Proc::cli()
{
  asm volatile ("cli" : : : "memory");
}

#line 55 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/ia32/processor-ia32.cpp"


inline void Proc::sti()
{
  asm volatile ("sti" : : : "memory");
}

#line 61 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/ia32/processor-ia32.cpp"


inline Proc::Status Proc::cli_save()
{
  Status ret;
  asm volatile ("pushfl   \n\t"
                "popl %0  \n\t"
                "cli      \n\t"
                : "=g" (ret) : /* no input */ : "memory");
  return ret;
}

#line 72 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/ia32/processor-ia32.cpp"


inline void Proc::sti_restore(Status st)
{
  if (st & 0x0200)
    asm volatile ("sti" : : : "memory");
}

#line 79 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/ia32/processor-ia32.cpp"


inline Proc::Status Proc::interrupts()
{
  Status ret;
  asm volatile ("pushfl    \n\t"
                "popl %0   \n\t"
                : "=g" (ret) : /* no input */ : "memory");
  return ret & 0x0200;
}

#line 89 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/ia32/processor-ia32.cpp"


inline void Proc::irq_chance()
{
  asm volatile ("nop");
  pause();
}

#endif // processor_h
