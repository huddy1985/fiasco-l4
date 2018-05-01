// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kmem_h
#define kmem_h
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

#include "globalconfig.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "initcalls.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "kip.h"
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "mem_layout.h"
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "paging.h"
#line 512 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

#include "simple_alloc.h"
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/kmem-ia32-32.cpp"

#include "simple_alloc.h"

//
// INTERFACE definition follows 
//

#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

class Cpu;
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
class Tss;
#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

class Device_map
{
public:
  enum
  {
    Max = 16,
    Virt_base = 0x20000000,
  };

private:
  Address _map[Max];


public:  
#line 102 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  void
  init();
  
#line 124 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  template< typename T > T *
  lookup(T *phys);
  
#line 166 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  template< typename T > T *
  map(T *phys, bool cache = true);
  
#line 171 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  void
  unmap(void const *phys);

private:  
#line 110 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  unsigned
  lookup_idx(Address phys);
  
#line 136 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  Address
  map(Address phys, bool /*cache*/);
};
#line 31 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

/**
 * The system's base facilities for kernel-memory management.
 * The kernel memory is a singleton object.  We access it through a
 * static class interface.
 */
class Kmem : public Mem_layout
{
  friend class Device_map;
  friend class Jdb;
  friend class Jdb_dbinfo;
  friend class Jdb_kern_info_misc;
  friend class Kdb;
  friend class Profile;
  friend class Vmem_alloc;

private:
  Kmem();			// default constructors are undefined
  Kmem (const Kmem&);

public:
  static Device_map dev_map;

  static void init_pageing(Cpu const &boot_cpu);
  static void init_boot_cpu(Cpu const &boot_cpu);
  static void init_app_cpu(Cpu const &cpu);
  static Mword is_kmem_page_fault(Address pfa, Mword error);
  static Mword is_ipc_page_fault(Address pfa, Mword error);
  static Mword is_io_bitmap_page_fault(Address pfa);
  static Address kcode_start();
  static Address kcode_end();
  static Address virt_to_phys(const void *addr);


#line 71 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
private:

  friend class Kernel_task;

public:
  static Address     user_max();

private:
  static Unsigned8   *io_bitmap_delimiter;
  static Address kphys_start, kphys_end;

#line 514 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
private:

  static unsigned long tss_mem_pm;
  static cxx::Simple_alloc tss_mem_vm;

public:  
#line 191 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  static inline Address
  io_bitmap_delimiter_page();
  
#line 220 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  // Only used for initialization and kernel debugger
  
  static Address
  map_phys_page_tmp(Address phys, Mword idx);
  
#line 249 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  static inline Address kernel_image_start();
  
#line 262 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  /** Return number of IPC slots to copy */
  
  static inline unsigned
  ipc_slots();
  
#line 284 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  //
  // helper functions
  //
  
  // Establish a 4k-mapping
  
  static void
  map_phys_page(Address phys, Address virt,
                      bool cached, bool global, Address *offs = 0);
  
#line 311 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  static Address
  mmio_remap(Address phys);
  
#line 324 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  static FIASCO_INIT
  void
  init_mmu();
  
#line 485 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  /**
   * Compute a kernel-virtual address for a physical address.
   * This function always returns virtual addresses within the
   * physical-memory region.
   * @pre addr <= highest kernel-accessible RAM address
   * @param addr a physical address
   * @return kernel-virtual address.
   */
  
  static inline void *
  phys_to_virt(Address addr);
  
#line 500 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  /**
   * Return Global page directory.
   * This is the master copy of the kernel's page directory. Kernel-memory
   * allocations are kept here and copied to task page directories lazily
   * upon page fault.
   * @return kernel's global page directory
   */
  static inline const Pdir* dir();
  
#line 547 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  static Address
  get_realmode_startup_pdbr();
  
#line 557 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  static inline Kpdir *
  current_cpu_kdir();
  
#line 632 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  static FIASCO_INIT_CPU
  void
  init_cpu(Cpu &cpu);
  
#line 647 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  static inline void
  resume_cpu(Cpu_number);

private:  
#line 412 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  static void
  setup_cpu_structures(Cpu &cpu, cxx::Simple_alloc *cpu_alloc,
                             cxx::Simple_alloc *tss_alloc);
  
#line 567 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
  static inline void
  setup_global_cpu_structures(bool superpages);
  
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/kmem-ia32-32.cpp"
  static inline FIASCO_INIT_CPU
  void
  init_cpu_arch(Cpu &cpu, cxx::Simple_alloc *cpu_mem);
};
#line 65 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

typedef Kmem Kmem_space;
#line 67 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


//----------------------------------------------------------------------------

#line 84 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


//--------------------------------------------------------------------------

#line 520 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

//--------------------------------------------------------------------------


//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 88 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

#include "cpu.h"
#line 90 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "l4_types.h"
#line 91 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "kmem_alloc.h"
#line 92 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "mem_unit.h"
#line 93 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "panic.h"
#line 94 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "paging.h"
#line 95 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "pic.h"
#line 96 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "std_macros.h"
#line 97 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "simple_alloc.h"
#line 98 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

#include <cstdio>
#line 468 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

#include <cstdlib>
#line 470 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include <cstddef>		// size_t
#line 471 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include <cstring>		// memset
#line 472 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

#include "config.h"
#line 474 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "cpu.h"
#line 475 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "gdt.h"
#line 476 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "globals.h"
#line 477 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "paging.h"
#line 478 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "regdefs.h"
#line 479 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "std_macros.h"
#line 480 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
#include "tss.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 188 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"



inline Address
Kmem::io_bitmap_delimiter_page()
{
  return reinterpret_cast<Address>(io_bitmap_delimiter);
}

#line 247 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


inline Address Kmem::kernel_image_start()
{ return virt_to_phys(&Mem_layout::image_start) & Config::PAGE_MASK; }

#line 260 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


/** Return number of IPC slots to copy */

inline unsigned
Kmem::ipc_slots()
{ return (8 << 20) / Config::SUPERPAGE_SIZE; }

#line 484 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

/**
 * Compute a kernel-virtual address for a physical address.
 * This function always returns virtual addresses within the
 * physical-memory region.
 * @pre addr <= highest kernel-accessible RAM address
 * @param addr a physical address
 * @return kernel-virtual address.
 */

inline void *
Kmem::phys_to_virt(Address addr)
{
  return reinterpret_cast<void *>(Mem_layout::phys_to_pmem(addr));
}

#line 499 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

/**
 * Return Global page directory.
 * This is the master copy of the kernel's page directory. Kernel-memory
 * allocations are kept here and copied to task page directories lazily
 * upon page fault.
 * @return kernel's global page directory
 */
inline const Pdir* Kmem::dir() { return kdir; }

#line 555 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


inline Kpdir *
Kmem::current_cpu_kdir()
{
  return kdir;
}

#line 645 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


inline void
Kmem::resume_cpu(Cpu_number)
{
  Cpu::set_pdbr(pmem_to_phys(kdir));
}

#line 196 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


/**
 * Compute physical address from a kernel-virtual address.
 * @param addr a virtual address
 * @return corresponding physical address if a mappings exists.
 *         -1 otherwise.
 */

inline Address
Kmem::virt_to_phys(const void *addr)
{
  Address a = reinterpret_cast<Address>(addr);

  if (EXPECT_TRUE(Mem_layout::in_pmem(a)))
    return Mem_layout::pmem_to_phys(a);

  if (EXPECT_TRUE(Mem_layout::in_kernel_image(a)))
    return a - Mem_layout::Kernel_image_offset;

  return kdir->virt_to_phys(a);
}

#line 251 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

inline Address Kmem::kcode_start()
{ return virt_to_phys(&Mem_layout::start) & Config::PAGE_MASK; }

#line 254 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

inline Address Kmem::kcode_end()
{
  return (virt_to_phys(&Mem_layout::end) + Config::PAGE_SIZE)
         & Config::PAGE_MASK;
}

#line 267 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


inline Mword
Kmem::is_io_bitmap_page_fault(Address addr)
{
  return addr >= Mem_layout::Io_bitmap &&
	 addr <= Mem_layout::Io_bitmap + Mem_layout::Io_port_max / 8;
}

#line 275 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


inline Mword
Kmem::is_kmem_page_fault(Address addr, Mword /*error*/)
{
  return addr > Mem_layout::User_max;
}

#line 462 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

inline Address Kmem::user_max() { return ~0UL; }

//
// IMPLEMENTATION of function templates
//


#line 120 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"




template< typename T > T *
Device_map::lookup(T *phys)
{
  unsigned idx = lookup_idx((Address)phys);
  if (idx == ~0U)
    return (T*)~0UL;

  return (T*)((Virt_base + idx * Config::SUPERPAGE_SIZE)
      | ((Address)phys & ~(~0UL << Config::SUPERPAGE_SHIFT)));
}

#line 163 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"



template< typename T > T *
Device_map::map(T *phys, bool cache)
{ return (T*)map((Address)phys, cache); }

#endif // kmem_h
