// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kip_h
#define kip_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"

#include <cxx/static_vector>
#line 39 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"

#include "mem_region.h"
#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"
#include "types.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/ia32/kip-ia32.cpp"

#include "types.h"

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"

class Mem_desc
{
public:
  enum Mem_type
  {
    Undefined    = 0x0,
    Conventional = 0x1,
    Reserved     = 0x2,
    Dedicated    = 0x3,
    Shared       = 0x4,
    Kernel_tmp   = 0x7,

    Info         = 0xd,
    Bootloader   = 0xe,
    Arch         = 0xf,
  };

  enum Ext_type_info
  {
    Info_acpi_rsdp = 0
  };

private:
  Mword _l, _h;

public:  
#line 121 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"
  inline Mem_desc(Address start, Address end, Mem_type t, bool v = false,
                     unsigned st = 0);
  
#line 129 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"
  inline Address start() const;
  
#line 133 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"
  inline Address end() const;
  
#line 137 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"
  inline void
  type(Mem_type t);
  
#line 142 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"
  inline Mem_desc::Mem_type type() const;
  
#line 146 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"
  inline unsigned ext_type() const;
  
#line 150 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"
  inline unsigned is_virtual() const;
  
#line 154 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"
  inline bool contains(Address addr) const;
  
#line 160 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"
  inline bool valid() const;
  
#line 36 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip-debug.cpp"
  void
  dump() const;
};
#line 30 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"

//----------------------------------------------------------------------------

#line 33 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"

/* Empty class for VHW descriptor in KIP for native ia32 */
class Vhw_descriptor {};
#line 36 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"

//----------------------------------------------------------------------------

#line 42 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"

class Kip
{
public:
  void print() const;

  char const *version_string() const;

  /* 0x00 */
  Mword      magic;
  Mword      version;
  Unsigned8  offset_version_strings;
  Unsigned8  fill0[sizeof(Mword) - 1];
  Unsigned8  kip_sys_calls;
  Unsigned8  fill1[sizeof(Mword) - 1];

  /* the following stuff is undocumented; we assume that the kernel
     info page is located at offset 0x1000 into the L4 kernel boot
     image so that these declarations are consistent with section 2.9
     of the L4 Reference Manual */

  /* 0x10   0x20 */
  Mword      sched_granularity;
  Mword      _res1[3];

  /* 0x20   0x40 */
  Mword      sigma0_sp, sigma0_ip;
  Mword      _res2[2];

  /* 0x30   0x60 */
  Mword      sigma1_sp, sigma1_ip;
  Mword      _res3[2];

  /* 0x40   0x80 */
  Mword      root_sp, root_ip;
  Mword      _res4[2];

  /* 0x50   0xA0 */
  Mword      _res_50;
  Mword      _mem_info;
  Mword      _res_58[2];

  /* 0x60   0xC0 */
  Mword      _res5[16];

  /* 0xA0   0x140 */
  volatile Cpu_time clock;
  Unsigned64 _res6;

  /* 0xB0   0x150 */
  Mword      frequency_cpu;
  Mword      frequency_bus;

  /* 0xB8   0x160 */
  Mword      _res7[10 + ((sizeof(Mword) == 8) ? 2 : 0)];

  /* 0xE0   0x1C0 */
  Mword      user_ptr;
  Mword      vhw_offset;
  Mword      _res8[2];

  /* 0xF0   0x1E0 */

private:
  static Kip *global_kip asm ("GLOBAL_KIP");

#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip-debug.cpp"
private:

private:
  void debug_print_syscalls() const;

#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/ia32/kip-ia32.cpp"
private:

public:
  struct Platform_info
  {
    char name[16];
    Unsigned32 is_mp;
  };

  /* 0xF0 */
  Platform_info platform_info;
  Unsigned32 __reserved[3];

public:  
#line 172 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"
  inline unsigned num_mem_descs() const;
  
#line 176 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"
  inline cxx::static_vector<Mem_desc>
  mem_descs_a();
  
#line 181 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"
  inline cxx::static_vector<Mem_desc const>
  mem_descs_a() const;
  
#line 187 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"
  inline void num_mem_descs(unsigned n);
  
#line 194 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"
  Mem_desc *add_mem_region(Mem_desc const &md);
  
#line 212 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"
  static inline void
  init_global_kip(Kip *kip);
  
#line 223 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"
  static inline Kip *k();

private:  
#line 164 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"
  inline Mem_desc *mem_descs();
  
#line 168 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"
  inline Mem_desc const *mem_descs() const;
  
#line 44 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip-debug.cpp"
  void
  debug_print_memory() const;
  
#line 60 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip-debug.cpp"
  void
  debug_print_features() const;
};
#line 108 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"

#define L4_KERNEL_INFO_MAGIC (0x4BE6344CL) /* "L4µK" */
#line 110 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"

//============================================================================


//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 115 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"
#include "config.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 119 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"


inline Mem_desc::Mem_desc(Address start, Address end, Mem_type t, bool v,
                   unsigned st)
: _l((start & ~0x3ffUL) | (t & 0x0f) | ((st << 4) & 0x0f0)
     | (v?0x0200:0x0)),
  _h(end)
{}

#line 127 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"


inline ALWAYS_INLINE Address Mem_desc::start() const
{ return _l & ~0x3ffUL; }

#line 131 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"


inline ALWAYS_INLINE Address Mem_desc::end() const
{ return _h | 0x3ffUL; }

#line 135 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"


inline ALWAYS_INLINE void
Mem_desc::type(Mem_type t)
{ _l = (_l & ~0x0f) | (t & 0x0f); }

#line 140 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"


inline ALWAYS_INLINE Mem_desc::Mem_type Mem_desc::type() const
{ return (Mem_type)(_l & 0x0f); }

#line 144 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"


inline unsigned Mem_desc::ext_type() const
{ return (_l >> 4) & 0x0f; }

#line 148 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"


inline ALWAYS_INLINE unsigned Mem_desc::is_virtual() const
{ return _l & 0x200; }

#line 152 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"


inline bool Mem_desc::contains(Address addr) const
{
  return start() <= addr && end() >= addr;
}

#line 158 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"


inline ALWAYS_INLINE bool Mem_desc::valid() const
{ return type() && start() < end(); }

#line 170 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"


inline ALWAYS_INLINE unsigned Kip::num_mem_descs() const
{ return _mem_info & ((1UL << (MWORD_BITS/2))-1); }

#line 184 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"



inline void Kip::num_mem_descs(unsigned n)
{
  _mem_info = (_mem_info & ~((1UL << (MWORD_BITS / 2)) - 1))
              | (n & ((1UL << (MWORD_BITS / 2)) - 1));
}

#line 162 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"


inline ALWAYS_INLINE Mem_desc *Kip::mem_descs()
{ return (Mem_desc*)(((Address)this) + (_mem_info >> (MWORD_BITS/2))); }

#line 166 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"


inline Mem_desc const *Kip::mem_descs() const
{ return (Mem_desc const *)(((Address)this) + (_mem_info >> (MWORD_BITS/2))); }

#line 174 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"

 
inline ALWAYS_INLINE cxx::static_vector<Mem_desc>
Kip::mem_descs_a()
{ return cxx::static_vector<Mem_desc>(mem_descs(), num_mem_descs()); }

#line 179 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"

 
inline ALWAYS_INLINE cxx::static_vector<Mem_desc const>
Kip::mem_descs_a() const
{ return cxx::static_vector<Mem_desc const>(mem_descs(), num_mem_descs()); }

#line 210 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"


inline ALWAYS_INLINE void
Kip::init_global_kip(Kip *kip)
{
  global_kip = kip;

  kip->platform_info.is_mp = Config::Max_num_cpus > 1;

  // check that the KIP has actually been set up
  //assert(kip->sigma0_ip && kip->root_ip && kip->user_ptr);
}

#line 222 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"

inline Kip *Kip::k() { return global_kip; }

#endif // kip_h
