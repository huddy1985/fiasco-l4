// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef ipi_h
#define ipi_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipi.cpp"

#include "types.h"

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipi.cpp"

class Ipi
{
public:
  static void init(Cpu_number cpu);

#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipi.cpp"
private:

public:
  enum Message { Request, Global_request, Debug };

public:  
#line 39 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipi.cpp"
  static inline void
  send(Message, Cpu_number from_cpu, Cpu_number to_cpu);
  
#line 44 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipi.cpp"
  static inline void
  eoi(Message, Cpu_number on_cpu);
  
#line 49 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipi.cpp"
  static inline void
  bcast(Message, Cpu_number from_cpu);
  
#line 63 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipi.cpp"
  static inline void
  stat_sent(Cpu_number from_cpu);
  
#line 68 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipi.cpp"
  static inline void
  stat_received(Cpu_number on_cpu);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 37 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipi.cpp"


inline void
Ipi::send(Message, Cpu_number from_cpu, Cpu_number to_cpu)
{ (void)from_cpu; (void)to_cpu; }

#line 42 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipi.cpp"


inline void
Ipi::eoi(Message, Cpu_number on_cpu)
{ (void)on_cpu; }

#line 47 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipi.cpp"


inline void
Ipi::bcast(Message, Cpu_number from_cpu)
{ (void)from_cpu; }

#line 61 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipi.cpp"


inline void
Ipi::stat_sent(Cpu_number from_cpu)
{ (void)from_cpu; }

#line 66 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipi.cpp"


inline void
Ipi::stat_received(Cpu_number on_cpu)
{ (void)on_cpu; }

#line 32 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipi.cpp"


inline void
Ipi::init(Cpu_number cpu)
{ (void)cpu; }

#endif // ipi_h
