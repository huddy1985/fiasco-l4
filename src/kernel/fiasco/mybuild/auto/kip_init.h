// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kip_init_h
#define kip_init_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kip_init-ia32.cpp"

#include "initcalls.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kip_init-ia32.cpp"
#include "types.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kip_init-ia32.cpp"
#include "kip.h"

//
// INTERFACE definition follows 
//

#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kip_init-ia32.cpp"

class Cpu;
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kip_init-ia32.cpp"


class Kip_init
{
public:
  /**
   * Insert memory descriptor for the Kmem region and finish the memory
   * info field.
   * @post no more memory descriptors may be added
   */
  static void setup_kmem_region (Address kmem_base, Address kmem_size);

public:  
#line 38 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kip_init-ia32.cpp"
  /** KIP initialization. */
  static FIASCO_INIT
  void
  init_freq(Cpu const &cpu);
  
#line 85 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kip_init-ia32.cpp"
  static FIASCO_INIT
  //IMPLEMENT
  void init();
  
#line 144 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kip_init-ia32.cpp"
  static FIASCO_INIT
  void
  setup_user_virtual(Kip *kinfo);

private:  
#line 24 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kip_init-ia32.cpp"
  static inline void
  setup_ux(Kip *);
  
#line 138 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kip_init-ia32.cpp"
  static inline void
  reserve_amd64_hole();
};

#endif // kip_init_h
