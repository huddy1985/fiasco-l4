// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef idt_h
#define idt_h
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"

#include "initcalls.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"
#include "idt_init.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"
#include "kmem.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"
#include "mem_layout.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"
#include "types.h"
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"
#include "x86desc.h"

//
// INTERFACE definition follows 
//

#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"

class Idt_init_entry;
#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"

class Idt
{
  friend class Jdb_kern_info_bench;
public:
  static const unsigned _idt_max = FIASCO_IDT_MAX;
private:
  static const Address  _idt = Mem_layout::Idt;
  static Address _idt_pa;

public:  
#line 60 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  static FIASCO_INIT
  void
  init_table(Idt_init_entry *src, Idt_entry *idt);
  
#line 75 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  /**
   * IDT initialization function. Sets up initial interrupt vectors.
   * It also write-protects the IDT because of the infamous Pentium F00F bug.
   */
  static FIASCO_INIT
  void
  init();
  
#line 97 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  static void
  init_current_cpu();
  
#line 117 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  static void
  load();
  
#line 125 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  static void
  set_entry(unsigned vector, Idt_entry entry);
  
#line 138 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  static Idt_entry const &
  get(unsigned vector);
  
#line 146 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  /**
   * IDT patching function.
   * Allows to change interrupt gate vectors at runtime.
   * It makes the IDT writable for the duration of this operation.
   * @param vector interrupt vector to be modified
   * @param func new handler function for this interrupt vector
   * @param user true if user mode can use this vector, false otherwise
   */
  
  static void
  set_entry(unsigned vector, Address entry, bool user);
  
#line 175 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  static Address
  get_entry(unsigned vector);
  
#line 184 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  static inline Address
  idt();
  
#line 196 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  /**
   * IDT loading function.
   * Loads IDT base and limit into the CPU.
    * @param desc IDT descriptor (base address, limit)
    */  
  
  static inline void
  set(Pseudo_descriptor *desc);
  
#line 209 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  static inline void
  get(Pseudo_descriptor *desc);
  
#line 221 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  /**
   * Set IDT vector to the normal timer interrupt handler.
   */
  
  static void
  set_vectors_run();

private:  
#line 39 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"
  /**
   * IDT write-protect/write-unprotect function.
   * @param writable true if IDT should be made writable, false otherwise
   */
  
  static void
  set_writable(bool writable);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 182 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"


inline Address
Idt::idt()
{
  return _idt;
}

#line 195 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"

/**
 * IDT loading function.
 * Loads IDT base and limit into the CPU.
  * @param desc IDT descriptor (base address, limit)
  */  

inline void
Idt::set(Pseudo_descriptor *desc)
{
  asm volatile ("lidt %0" : : "m" (*desc));
}

#line 207 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/idt.cpp"


inline void
Idt::get(Pseudo_descriptor *desc)
{
  asm volatile ("sidt %0" : "=m" (*desc) : : "memory");
}

#endif // idt_h
