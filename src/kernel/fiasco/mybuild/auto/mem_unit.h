// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef mem_unit_h
#define mem_unit_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_unit-ia32.cpp"

#include "types.h"

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_unit-ia32.cpp"

class Mem_unit
{

public:  
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_unit-ia32.cpp"
  static inline void
  make_coherent_to_pou(void const *);
  
#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_unit-ia32.cpp"
  /** Flush the whole TLB.
   */
  
  static inline void
  tlb_flush();
  
#line 28 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_unit-ia32.cpp"
  /** Flush TLB at virtual address.
   */
  
  static inline void
  tlb_flush(Address addr);
  
#line 38 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_unit-ia32.cpp"
  static inline void
  clean_dcache();
  
#line 43 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_unit-ia32.cpp"
  static inline void
  clean_dcache(void const *addr);
  
#line 48 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_unit-ia32.cpp"
  static inline void
  clean_dcache(void const *start, void const *end);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_unit-ia32.cpp"


inline ALWAYS_INLINE void
Mem_unit::make_coherent_to_pou(void const *)
{}

#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_unit-ia32.cpp"

/** Flush the whole TLB.
 */

inline ALWAYS_INLINE void
Mem_unit::tlb_flush()
{
  Mword dummy;
  __asm__ __volatile__ ("mov %%cr3,%0; mov %0,%%cr3 " : "=r"(dummy) : : "memory");
}

#line 26 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_unit-ia32.cpp"


/** Flush TLB at virtual address.
 */

inline ALWAYS_INLINE void
Mem_unit::tlb_flush(Address addr)
{
  __asm__ __volatile__ ("invlpg %0" : : "m" (*(char*)addr) : "memory");
}

#line 36 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_unit-ia32.cpp"


inline ALWAYS_INLINE void
Mem_unit::clean_dcache()
{ asm volatile ("wbinvd"); }

#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_unit-ia32.cpp"


inline ALWAYS_INLINE void
Mem_unit::clean_dcache(void const *addr)
{ asm volatile ("clflush %0" : : "m" (*(char const *)addr)); }

#line 46 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_unit-ia32.cpp"


inline ALWAYS_INLINE void
Mem_unit::clean_dcache(void const *start, void const *end)
{
  enum { Cl_size = 64 };
  if (((Address)end) - ((Address)start) >= 8192)
    clean_dcache();
  else
    for (char const *s = (char const *)start; s < (char const *)end;
         s += Cl_size)
      clean_dcache(s);
}

#endif // mem_unit_h
