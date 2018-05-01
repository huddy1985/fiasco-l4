// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef x86desc_h
#define x86desc_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"

#include "l4_types.h"

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"

class X86desc
{
public:
  enum
  {
    Accessed            = 0x01,
    Access_kernel       = 0x00,
    Access_user         = 0x60,
    Access_present      = 0x80,

    Access_tss          = 0x09,
    Access_intr_gate    = 0x0e,
    Access_trap_gate    = 0x0f,

    Long_mode           = 0x02, // XXX for code segments
  };

public:  
#line 192 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  const char*
  type_str() const;
  
#line 261 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  void
  show() const;
  
#line 281 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline X86desc();
  
#line 285 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline unsigned access() const;
  
#line 289 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline int
  present() const;
  
#line 296 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Unsigned8
  type() const;
  
#line 303 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Unsigned8
  dpl() const;
  
#line 310 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline bool
  unsafe() const;
};
#line 22 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


class Gdt_entry : public X86desc
{
public:
  enum
  {
    Access_type_user    = 0x10,
    Access_code_read    = 0x1a,
    Access_data_write   = 0x12,
    Size_32             = 0x04,
  };

  union {
    struct {
      Unsigned16   limit_low;
      Unsigned16   base_low;
      Unsigned8    base_med;
      Unsigned8    access;
      Unsigned8    limit_high;
      Unsigned8    base_high;
    };
    Unsigned64 raw;
  };


public:  
#line 124 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Address
  base() const;
  
#line 221 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  void
  show() const;
  
#line 346 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Gdt_entry(Address base, Unsigned32 limit,
  		     Unsigned8 _access, Unsigned8 szbits);
  
#line 359 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Gdt_entry();
  
#line 364 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Mword
  limit() const;
  
#line 369 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Mword
  size() const;
  
#line 377 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline bool
  avl() const;
  
#line 384 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline bool
  seg64() const;
  
#line 391 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline bool
  seg32() const;
  
#line 398 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline unsigned
  mode() const;
  
#line 403 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline bool
  granularity() const;
  
#line 410 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline bool
  writable() const;
  
#line 417 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline int
  contents() const;
  
#line 424 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline void
  clear();
} __attribute__((packed));
#line 48 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


class Idt_entry : public X86desc
{
private:
  union {
    struct {
      Unsigned16 _offset_low;
      Unsigned16 _selector;
      Unsigned8  _ist;
      Unsigned8  _access;
      Unsigned16 _offset_high;
    };
    Unsigned64 _raw;
  };

public:  
#line 79 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Address offset() const;
  
#line 83 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Idt_entry();
  
#line 86 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  // interrupt gate
  
  inline Idt_entry(Address entry, Unsigned16 selector, Unsigned8 access, unsigned = 0);
  
#line 97 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  // task gate
  
  inline Idt_entry(Unsigned16 selector, Unsigned8 access);
  
#line 109 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  static inline Idt_entry
  free(Unsigned16 val);
  
#line 119 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Unsigned16
  get_free_val() const;
  
#line 235 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline unsigned
  selector() const;
  
#line 240 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  void
  show() const;
  
#line 331 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline unsigned
  ist() const;
  
#line 341 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline void
  clear();
} __attribute__((packed));
#line 64 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"



class Pseudo_descriptor
{
  Unsigned16 _limit;
  Mword _base;

public:  
#line 315 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Pseudo_descriptor();
  
#line 319 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Pseudo_descriptor(Address base, Unsigned16 limit);
  
#line 324 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Address
  base() const;
  
#line 336 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"
  inline Unsigned16
  limit() const;
} __attribute__((packed));
#line 72 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"



//----------------------------------------------------------------------------


//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 279 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline X86desc::X86desc()
{}

#line 283 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline unsigned X86desc::access() const
{ return ((Unsigned8 const *)this)[5]; }

#line 287 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline int
X86desc::present() const
{
  return (access() & 0x80) >> 7;
}

#line 294 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Unsigned8
X86desc::type() const
{
  return access() & 0x1f;
}

#line 301 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Unsigned8
X86desc::dpl() const
{
  return (access() & 0x60) >> 5;
}

#line 308 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline bool
X86desc::unsafe() const
{ return present() && (dpl() != 3); }

#line 122 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Address
Gdt_entry::base() const
{
  return (Address)base_low | ((Address)base_med  << 16)
         | ((Address)base_high << 24);
}

#line 344 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Gdt_entry::Gdt_entry(Address base, Unsigned32 limit,
		     Unsigned8 _access, Unsigned8 szbits)
{
  limit_low  =  limit & 0x0000ffff;
  base_low   =  base  & 0x0000ffff;
  base_med   = (base  & 0x00ff0000) >> 16;
  access     =  _access | Access_present;
  limit_high = ((limit & 0x000f0000) >> 16) |
			(((Unsigned16)szbits) << 4);
  base_high  = (base  & 0xff000000) >> 24;
}

#line 357 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Gdt_entry::Gdt_entry()
{}

#line 361 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"



inline Mword
Gdt_entry::limit() const
{ return (Mword)limit_low | (((Mword)limit_high & 0x0f) << 16); }

#line 401 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline bool
Gdt_entry::granularity() const
{
  return (limit_high & 0x80);
}

#line 367 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Mword
Gdt_entry::size() const
{
  Mword l = limit();
  return granularity() ? ((l+1) << 12)-1 : l;
}

#line 375 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline bool
Gdt_entry::avl() const
{
  return (limit_high & 0x10);
}

#line 382 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline bool
Gdt_entry::seg64() const
{
  return (limit_high & 0x20);
}

#line 389 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline bool
Gdt_entry::seg32() const
{
  return (limit_high & 0x40);
}

#line 396 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline unsigned
Gdt_entry::mode() const
{ return (limit_high >> 5) & 3; }

#line 408 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline bool
Gdt_entry::writable() const
{
  return (type() & 0x02);
}

#line 415 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline int
Gdt_entry::contents() const
{
  return (type() & 0x0c) >> 2;
}

#line 422 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline void
Gdt_entry::clear()
{
  raw = 0;
}

#line 77 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Address Idt_entry::offset() const
{ return (Address)_offset_low | ((Address)_offset_high << 16); }

#line 81 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Idt_entry::Idt_entry()
{}

#line 85 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"

// interrupt gate

inline Idt_entry::Idt_entry(Address entry, Unsigned16 selector, Unsigned8 access, unsigned)
{
  _offset_low  = entry & 0x0000ffff;
  _selector    = selector;
  _ist         = 0;
  _access      = access | X86desc::Access_present;
  _offset_high = (entry & 0xffff0000) >> 16;
}

#line 96 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"

// task gate

inline Idt_entry::Idt_entry(Unsigned16 selector, Unsigned8 access)
{
  _offset_low  = 0;
  _selector    = selector;
  _ist         = 0;
  _access      = access | X86desc::Access_present;
  _offset_high = 0;
}

#line 107 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Idt_entry
Idt_entry::free(Unsigned16 val)
{
  Idt_entry e;
  e._access = 0;
  e._offset_low = val;
  return e;
}

#line 117 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Unsigned16
Idt_entry::get_free_val() const
{ return _offset_low; }

#line 233 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline unsigned
Idt_entry::selector() const
{ return _selector; }

#line 329 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline unsigned
Idt_entry::ist() const
{ return _ist; }

#line 339 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline void
Idt_entry::clear()
{ _raw = 0; }

#line 313 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Pseudo_descriptor::Pseudo_descriptor()
{}

#line 317 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Pseudo_descriptor::Pseudo_descriptor(Address base, Unsigned16 limit)
  : _limit(limit), _base(base)
{}

#line 322 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Address
Pseudo_descriptor::base() const
{
  return _base;
}

#line 334 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/x86desc.cpp"


inline Unsigned16
Pseudo_descriptor::limit() const
{ return _limit; }

#endif // x86desc_h
