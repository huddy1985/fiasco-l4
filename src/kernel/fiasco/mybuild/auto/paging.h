// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef paging_h
#define paging_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/paging.cpp"

#include "types.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/paging.cpp"
#include "l4_msg_item.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/paging.cpp"
#include "ptab_base.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/paging.cpp"
#include "mem_layout.h"
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/paging-ia32-32.cpp"

#include <cassert>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/paging-ia32-32.cpp"
#include "types.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/paging-ia32-32.cpp"
#include "config.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/paging-ia32-32.cpp"
#include "ptab_base.h"
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"

#include "types.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
#include "config.h"

//
// INTERFACE definition follows 
//

#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/paging.cpp"

class Page
{
public:

  /* These things must be defined in arch part in
     the most efficent way according to the architecture.

  typedef int Attribs;

  enum Attribs_enum {
    USER_NO  = xxx, ///< User No access
    USER_RO  = xxx, ///< User Read only
    USER_RW  = xxx, ///< User Read/Write
    USER_RX  = xxx, ///< User Read/Execute
    USER_XO  = xxx, ///< User Execute only
    USER_RWX = xxx, ///< User Read/Write/Execute

    NONCACHEABLE = xxx, ///< Caching is off
    CACHEABLE    = xxx, ///< Cahe is enabled
  };

  */
  typedef L4_msg_item::Memory_type Type;

  struct Kern
  : cxx::int_type_base<unsigned char, Kern>,
    cxx::int_bit_ops<Kern>,
    cxx::int_null_chk<Kern>
  {
    Kern() = default;
    explicit Kern(Value v) : cxx::int_type_base<unsigned char, Kern>(v) {}

    static Kern Global() { return Kern(1); }
  };

  typedef L4_fpage::Rights Rights;

  struct Attr
  {
    Rights rights;
    Type type;
    Kern kern;

    Attr() = default;
    explicit Attr(Rights r, Type t = Type::Normal(), Kern k = Kern(0))
    : rights(r), type(t), kern(k) {}

    Attr apply(Attr o) const
    {
      Attr n = *this;
      n.rights &= o.rights;
      if ((o.type & Type::Set()) == Type::Set())
        n.type = o.type & ~Type::Set();
      return n;
    }

    constexpr bool empty() const
    { return (rights & Rights::RWX()).empty(); }
  };

#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
private:

public:
  enum Attribs_enum
  {
    MAX_ATTRIBS   = 0x00000006,
    Cache_mask    = 0x00000018, ///< Cache attrbute mask
    CACHEABLE     = 0x00000000,
    BUFFERED      = 0x00000010,
    NONCACHEABLE  = 0x00000018,
  };
};
#line 68 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/paging.cpp"

class PF
{
public:
  static Mword is_translation_error( Mword error );
  static Mword is_usermode_error( Mword error );
  static Mword is_read_error( Mword error );
  static Mword addr_to_msgword0( Address pfa, Mword error );
  static Mword pc_to_msgword1( Address pc, Mword error );
};
#line 78 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/paging.cpp"


class Pdir_alloc_null
{
public:
  Pdir_alloc_null() {}
  void *alloc(unsigned long) const { return 0; }
  void free(void *, unsigned long) const {}
  bool valid() const { return false; }
};
#line 88 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/paging.cpp"

template<typename ALLOC>
class Pdir_alloc_simple
{
public:
  Pdir_alloc_simple(ALLOC *a = 0) : _a(a) {}

  void *alloc(unsigned long size) const
  { return _a->unaligned_alloc(size); }

  void free(void *block, unsigned long size) const
  { _a->unaligned_free(size, block); }

  bool valid() const { return _a; }

  Phys_mem_addr::Value
  to_phys(void *v) const { return _a->to_phys(v); }

private:
  ALLOC *_a;
};
#line 109 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/paging.cpp"

template<typename PTE_PTR, typename TRAITS, typename VA>
class Pdir_t : public Ptab::Base<PTE_PTR, TRAITS, VA, Mem_layout>
{
public:
  enum { Super_level = PTE_PTR::Super_level };

public:  
#line 134 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/paging.cpp"
  Address
  virt_to_phys(Address virt) const;
};
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/paging-ia32-32.cpp"

class Pt_entry
{
public:
  enum
  {
    Super_level   = 0,
    Valid         = 0x00000001, ///< Valid
    Writable      = 0x00000002, ///< Writable
    User          = 0x00000004, ///< User accessible
    Write_through = 0x00000008, ///< Write through
    Cacheable     = 0x00000000, ///< Cache is enabled
    Noncacheable  = 0x00000010, ///< Caching is off
    Referenced    = 0x00000020, ///< Page was referenced
    Dirty         = 0x00000040, ///< Page was modified
    Pse_bit       = 0x00000080, ///< Indicates a super page
    Cpu_global    = 0x00000100, ///< pinned in the TLB
    L4_global     = 0x00000200, ///< pinned in the TLB
    XD            = 0,
    ATTRIBS_MASK  = 0x06,
  };

#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
private:

private:
  static Unsigned32 _cpu_global;
  static unsigned _super_level;
  static bool _have_superpages;

public:  
#line 44 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
  static inline void
  have_superpages(bool yes);
  
#line 52 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
  static inline unsigned
  super_level();
  
#line 266 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
  static inline void
  enable_global();
  
#line 270 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
  /**
   * Global entries are entries that are not automatically flushed when the
   * page-table base register is reloaded. They are intended for kernel data
   * that is shared between all tasks.
   * @return global page-table--entry flags
   */
  
  static inline Unsigned32
  global();
};
#line 29 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/paging-ia32-32.cpp"

class Pte_ptr

: private Pt_entry
{
public:
  Pte_ptr(void *pte, unsigned char level) : pte((Mword*)pte), level(level) {}
  Pte_ptr() = default;

  typedef Mword Entry;
  Entry *pte;
  Entry entry() const { return *pte; }
  unsigned char level;

#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
private:

public:
  using Pt_entry::Super_level;

public:  
#line 58 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
  inline bool
  is_valid() const;
  
#line 63 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
  inline bool
  is_leaf() const;
  
#line 67 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
  /**
   * \pre is_leaf() == false
   */
  
  inline Mword
  next_level() const;
  
#line 75 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
  /**
   * \pre cxx::get_lsb(phys_addr, Config::PAGE_SHIFT) == 0
   */
  
  inline void
  set_next_level(Mword phys_addr);
  
#line 84 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
  inline void
  set_page(Mword phys, Mword attr);
  
#line 94 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
  inline Pte_ptr const &
  operator++ ();
  
#line 102 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
  inline Mword
  page_addr() const;
  
#line 108 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
  inline void
  set_attribs(Page::Attr attr);
  
#line 126 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
  inline Mword
  make_page(Phys_mem_addr addr, Page::Attr attr);
  
#line 144 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
  inline void
  set_page(Mword p);
  
#line 151 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
  inline Page::Attr
  attribs() const;
  
#line 176 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
  inline void
  add_attribs(Mword attr);
  
#line 181 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
  inline unsigned char
  page_order() const;
  
#line 186 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
  inline L4_fpage::Rights
  access_flags() const;
  
#line 211 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
  inline void
  clear();
  
#line 216 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
  static inline void
  write_back(void *, void *);
  
#line 221 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
  static inline void
  write_back_if(bool);
  
#line 226 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
  inline void
  del_attribs(Mword attr);
  
#line 231 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
  inline void
  del_rights(L4_fpage::Rights r);
};
#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/paging-ia32-32.cpp"



typedef Ptab::List< Ptab::Traits<Unsigned32, 22, 10, true, false>,
                    Ptab::Traits<Unsigned32, 12, 10, true> > Ptab_traits;
#line 46 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/paging-ia32-32.cpp"

typedef Ptab::Shift<Ptab_traits, Virt_addr::Shift>::List Ptab_traits_vpn;
#line 48 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/paging-ia32-32.cpp"
typedef Ptab::Page_addr_wrap<Page_number, Virt_addr::Shift> Ptab_va_vpn;
#line 49 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/paging-ia32-32.cpp"
typedef Pdir_t<Pte_ptr, Ptab_traits_vpn, Ptab_va_vpn> Pdir;
#line 50 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/paging-ia32-32.cpp"
class Kpdir : public Pdir {};
#line 33 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"


//---------------------------------------------------------------------------


#line 122 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/paging.cpp"
//---------------------------------------------------------------------------


template<typename ALLOC> inline Pdir_alloc_simple<ALLOC> pdir_alloc(ALLOC *a);

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 37 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"

#include "atomic.h"
#line 284 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
#include "cpu.h"
#line 285 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
#include "mem_layout.h"
#line 286 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"
#include "regdefs.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 293 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"


inline Mword PF::is_usermode_error(Mword error)
{
  return (error & PF_ERR_USERMODE);
}

#line 123 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/paging.cpp"


inline Mword PF::pc_to_msgword1(Address pc, Mword error)
{
  return is_usermode_error(error) ? pc : (Mword)-1;
}

#line 287 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"


inline Mword PF::is_translation_error(Mword error)
{
  return !(error & PF_ERR_PRESENT);
}

#line 299 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"


inline Mword PF::is_read_error(Mword error)
{
  return !(error & PF_ERR_WRITE);
}

#line 305 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"


inline Mword PF::addr_to_msgword0(Address pfa, Mword error)
{
  Mword v = (pfa & ~0x7) | (error &  (PF_ERR_PRESENT | PF_ERR_WRITE));
  if (error & (1 << 4)) v |= 0x4;
  return v;
}

#line 42 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"


inline void
Pt_entry::have_superpages(bool yes)
{
  _have_superpages = yes;
  _super_level = yes ? Super_level : (Super_level + 1);
}

#line 50 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"


inline unsigned
Pt_entry::super_level()
{ return _super_level; }

#line 264 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"


inline void
Pt_entry::enable_global()
{ _cpu_global |= Cpu_global; }

#line 269 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"

/**
 * Global entries are entries that are not automatically flushed when the
 * page-table base register is reloaded. They are intended for kernel data
 * that is shared between all tasks.
 * @return global page-table--entry flags
 */

inline Unsigned32
Pt_entry::global()
{ return _cpu_global; }

#line 55 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"



inline bool
Pte_ptr::is_valid() const
{ return *pte & Valid; }

#line 61 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"


inline bool
Pte_ptr::is_leaf() const
{ return level == Pdir::Depth || (*pte & Pse_bit); }

#line 66 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"

/**
 * \pre is_leaf() == false
 */

inline Mword
Pte_ptr::next_level() const
{ return cxx::mask_lsb(*pte, (unsigned)Config::PAGE_SHIFT); }

#line 74 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"

/**
 * \pre cxx::get_lsb(phys_addr, Config::PAGE_SHIFT) == 0
 */

inline void
Pte_ptr::set_next_level(Mword phys_addr)
{ *pte = phys_addr | Valid | User | Writable; }

#line 82 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"


inline void
Pte_ptr::set_page(Mword phys, Mword attr)
{
  Mword v = phys | Valid | attr;
  if (level < Pdir::Depth)
    v |= Pse_bit;
  *pte = v;
}

#line 92 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"


inline Pte_ptr const &
Pte_ptr::operator++ ()
{
  ++pte;
  return *this;
}

#line 100 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"


inline Mword
Pte_ptr::page_addr() const
{ return cxx::mask_lsb(*pte, Pdir::page_order_for_level(level)) & ~Mword(XD); }

#line 105 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"



inline void
Pte_ptr::set_attribs(Page::Attr attr)
{
  typedef L4_fpage::Rights R;
  typedef Page::Type T;
  typedef Page::Kern K;
  Mword r = 0;
  if (attr.rights & R::W()) r |= Writable;
  if (attr.rights & R::U()) r |= User;
  if (!(attr.rights & R::X())) r |= XD;
  if (attr.type == T::Normal()) r |= Page::CACHEABLE;
  if (attr.type == T::Buffered()) r |= Page::BUFFERED;
  if (attr.type == T::Uncached()) r |= Page::NONCACHEABLE;
  if (attr.kern & K::Global()) r |= global();
  *pte = (*pte & ~(ATTRIBS_MASK | Page::Cache_mask)) | r;
}

#line 124 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"


inline Mword
Pte_ptr::make_page(Phys_mem_addr addr, Page::Attr attr)
{
  Mword r = (level < Pdir::Depth) ? (Mword)Pse_bit : 0;
  typedef L4_fpage::Rights R;
  typedef Page::Type T;
  typedef Page::Kern K;
  if (attr.rights & R::W()) r |= Writable;
  if (attr.rights & R::U()) r |= User;
  if (!(attr.rights & R::X())) r |= XD;
  if (attr.type == T::Normal()) r |= Page::CACHEABLE;
  if (attr.type == T::Buffered()) r |= Page::BUFFERED;
  if (attr.type == T::Uncached()) r |= Page::NONCACHEABLE;
  if (attr.kern & K::Global()) r |= global();
  return cxx::int_value<Phys_mem_addr>(addr) | r | Valid;
}

#line 142 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"


inline void
Pte_ptr::set_page(Mword p)
{
  write_now(pte, p);
}

#line 149 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"


inline Page::Attr
Pte_ptr::attribs() const
{
  typedef L4_fpage::Rights R;
  typedef Page::Type T;

  Mword _raw = *pte;
  R r = R::R();
  if (_raw & Writable) r |= R::W();
  if (_raw & User) r |= R::U();
  if (!(_raw & XD)) r |= R::X();

  T t;
  switch (_raw & Page::Cache_mask)
    {
    default:
    case Page::CACHEABLE:    t = T::Normal(); break;
    case Page::BUFFERED:     t = T::Buffered(); break;
    case Page::NONCACHEABLE: t = T::Uncached(); break;
    }
  // do not care for kernel special flags, as this is used for user
  // level mappings
  return Page::Attr(r, t);
}

#line 175 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"

inline void
Pte_ptr::add_attribs(Mword attr)
{ *pte |= attr; }

#line 179 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"


inline unsigned char
Pte_ptr::page_order() const
{ return Pdir::page_order_for_level(level); }

#line 184 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"


inline L4_fpage::Rights
Pte_ptr::access_flags() const
{

  if (!is_valid())
    return L4_fpage::Rights(0);

  L4_fpage::Rights r;
  for (;;)
    {
      auto raw = *pte;

      if (raw & Dirty)
        r = L4_fpage::Rights::RW();
      else if (raw & Referenced)
        r = L4_fpage::Rights::R();
      else
        return L4_fpage::Rights(0);

      if (mp_cas(pte, raw, raw & ~(Dirty | Referenced)))
        return r;
    }
}

#line 209 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"


inline void
Pte_ptr::clear()
{ *pte = 0; }

#line 214 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"


inline void
Pte_ptr::write_back(void *, void *)
{}

#line 219 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"


inline void
Pte_ptr::write_back_if(bool)
{}

#line 224 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"


inline void
Pte_ptr::del_attribs(Mword attr)
{ *pte &= ~attr; }

#line 229 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/paging-ia32.cpp"


inline void
Pte_ptr::del_rights(L4_fpage::Rights r)
{
  if (r & L4_fpage::Rights::W())
    *pte &= ~Writable;

  if (r & L4_fpage::Rights::X())
    *pte |= XD;
}

#line 118 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/paging.cpp"
//---------------------------------------------------------------------------


template<typename ALLOC> inline Pdir_alloc_simple<ALLOC> pdir_alloc(ALLOC *a)
{ return Pdir_alloc_simple<ALLOC>(a); }

//
// IMPLEMENTATION of function templates
//


#line 132 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/paging.cpp"


template<typename PTE_PTR, typename TRAITS, typename VA> Address
Pdir_t<PTE_PTR, TRAITS, VA>::virt_to_phys(Address virt) const
{
  Virt_addr va(virt);
  auto i = this->walk(va);
  if (!i.is_valid())
    return ~0;

  return i.page_addr() | cxx::get_lsb(virt, i.page_order());
}

#endif // paging_h
