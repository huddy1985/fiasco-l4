// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef obj_space_phys_util_h
#define obj_space_phys_util_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"

#include "assert_opt.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
#include "obj_space_types.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
#include "ram_quota.h"
#line 49 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"

#include "cxx/type_traits"

//
// INTERFACE definition follows 
//

#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"

template< typename SPACE >
class Obj_space_phys
{
public:
  typedef Obj::Attr Attr;
  typedef Obj::Capability Capability;
  typedef Obj::Entry Entry;
  typedef Kobject_iface *Phys_addr;

  typedef Obj::Cap_addr V_pfn;
  typedef Cap_diff V_pfc;
  typedef Order Page_order;

  bool v_lookup(V_pfn const &virt, Phys_addr *phys,
                Page_order *size, Attr *attribs);

  L4_fpage::Rights v_delete(V_pfn virt, Order size,
                            L4_fpage::Rights page_attribs);
  Obj::Insert_result v_insert(Phys_addr phys, V_pfn const &virt, Order size,
                              Attr page_attribs);

  Capability lookup(Cap_index virt);

private:
  enum
  {
    Slots_per_dir = Config::PAGE_SIZE / sizeof(void*)
  };

  struct Cap_table { Entry e[Obj::Caps_per_page]; };
  struct Cap_dir   { Cap_table *d[Slots_per_dir]; };
  Cap_dir *_dir;

  Ram_quota *ram_quota() const
  {
    assert_opt (this);
    return SPACE::ram_quota(this);
  }

public:  
#line 140 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
  inline Obj_space_phys();
  
#line 191 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
  void
  caps_free();
  
#line 255 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
  inline Kobject_iface *
  lookup_local(Cap_index virt, L4_fpage::Rights *rights);
  
#line 329 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
  inline typename Obj_space_phys<SPACE>::V_pfn
  obj_map_max_address() const;
  
#line 339 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
  typename Obj_space_phys<SPACE>::Entry *
  jdb_lookup_cap(Cap_index index);

private:  
#line 149 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
  typename Obj_space_phys<SPACE>::Entry *
  get_cap(Cap_index index);
  
#line 169 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
  typename Obj_space_phys<SPACE>::Entry *
  caps_alloc(Cap_index virt);
};
#line 46 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"

// ------------------------------------------------------------------------

#line 51 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"

/**
 * Allows to override the virtually mapped object space Space
 * by the multi-level table based structure.
 *
 * This is useful for Vm or Io spaces that never run threads, and
 * saves the overhead of software page-table walks and phys-to-virt
 * translations for capability lookup.
 */
template<typename BASE>
class Obj_space_phys_override :
  public BASE,
  Obj_space_phys< Obj_space_phys_override<BASE> >
{
  typedef Obj_space_phys< Obj_space_phys_override<BASE> > Obj_space;

public:
  using BASE::ram_quota;
  static Ram_quota *ram_quota(Obj_space const *obj_sp)
  { return static_cast<Obj_space_phys_override<BASE> const *>(obj_sp)->ram_quota(); }

  bool FIASCO_FLATTEN
  v_lookup(typename Obj_space::V_pfn const &virt,
           typename Obj_space::Phys_addr *phys,
           typename Obj_space::Page_order *size,
           typename Obj_space::Attr *attribs) override
  { return Obj_space::v_lookup(virt, phys, size, attribs); }

  L4_fpage::Rights FIASCO_FLATTEN
  v_delete(typename Obj_space::V_pfn virt, Order size,
           L4_fpage::Rights page_attribs) override
  { return Obj_space::v_delete(virt, size, page_attribs); }

  Obj::Insert_result FIASCO_FLATTEN
  v_insert(typename Obj_space::Phys_addr phys,
           typename Obj_space::V_pfn const &virt,
           Order size,
           typename Obj_space::Attr page_attribs) override
  { return Obj_space::v_insert(phys, virt, size, page_attribs); }

  typename Obj_space::Capability FIASCO_FLATTEN
  lookup(Cap_index virt) override
  { return Obj_space::lookup(virt); }

  typename Obj_space::V_pfn FIASCO_FLATTEN
  obj_map_max_address() const override
  { return Obj_space::obj_map_max_address(); }

  void FIASCO_FLATTEN caps_free() override
  { Obj_space::caps_free(); }

  template<typename ...ARGS>
  Obj_space_phys_override(ARGS &&...args) : BASE(cxx::forward<ARGS>(args)...) {}

public:  
#line 347 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
  static inline Obj_space_phys_override<BASE> *
  get_space(Obj_space *base);
  
#line 352 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
  Obj::Entry *
  jdb_lookup_cap(Cap_index index) override;
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 125 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"

#include <cstring>
#line 127 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
#include <cassert>
#line 128 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"

#include "atomic.h"
#line 130 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
#include "config.h"
#line 131 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
#include "cpu.h"
#line 132 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
#include "kmem_alloc.h"
#line 133 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
#include "mem.h"
#line 134 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
#include "mem_layout.h"
#line 135 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
#include "ram_quota.h"
#line 136 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"
#include "static_assert.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 137 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"



template< typename SPACE > inline Obj_space_phys<SPACE>::Obj_space_phys()
{
  static_assert(sizeof(Cap_dir) == Config::PAGE_SIZE, "cap_dir size mismatch");
  _dir = (Cap_dir*)Kmem_alloc::allocator()->q_unaligned_alloc(ram_quota(), Config::PAGE_SIZE);
  if (_dir)
    Mem::memset_mwords(_dir, 0, Config::PAGE_SIZE / sizeof(Mword));
}

#line 252 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"



template< typename SPACE > inline Kobject_iface *
Obj_space_phys<SPACE>::lookup_local(Cap_index virt, L4_fpage::Rights *rights)
{
  Entry *c = get_cap(virt);

  if (EXPECT_FALSE(!c))
    return 0;

  Capability cap = *c;

  if (rights)
    *rights = L4_fpage::Rights(cap.rights());

  return cap.obj();
}

#line 325 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"




template< typename SPACE > inline typename Obj_space_phys<SPACE>::V_pfn
Obj_space_phys<SPACE>::obj_map_max_address() const
{
  return V_pfn(Slots_per_dir * Obj::Caps_per_page);
}

#line 212 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"

//
// Utilities for map<Obj_space_phys> and unmap<Obj_space_phys>
//



template< typename SPACE > inline bool FIASCO_FLATTEN
Obj_space_phys<SPACE>::v_lookup(V_pfn const &virt, Phys_addr *phys,
                                Page_order *size, Attr *attribs)
{
  if (size) *size = Page_order(0);
  Entry *cap = get_cap(virt);

  if (EXPECT_FALSE(!cap))
    {
      if (size) *size = Page_order(Obj::Caps_per_page_ld2);
      return false;
    }

  Capability c = *cap;

  Obj::set_entry(virt, cap);
  if (phys) *phys = c.obj();
  if (c.valid() && attribs) *attribs = cap->rights();
  return c.valid();
}

#line 239 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"



template< typename SPACE > inline typename Obj_space_phys<SPACE>::Capability FIASCO_FLATTEN
Obj_space_phys<SPACE>::lookup(Cap_index virt)
{
  Capability *c = get_cap(virt);

  if (EXPECT_FALSE(!c))
    return Capability(0); // void

  return *c;
}

#line 270 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"




template< typename SPACE > inline L4_fpage::Rights FIASCO_FLATTEN
Obj_space_phys<SPACE>::v_delete(V_pfn virt, Page_order size,
                                   L4_fpage::Rights page_attribs)
{
  (void)size;
  assert (size == Page_order(0));
  Capability *c = get_cap(virt);

  if (c && c->valid())
    {
      if (page_attribs & L4_fpage::Rights::R())
        c->invalidate();
      else
	c->del_rights(page_attribs);
    }

  return L4_fpage::Rights(0);
}

#line 292 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"



template< typename SPACE > inline typename Obj::Insert_result FIASCO_FLATTEN
Obj_space_phys<SPACE>::v_insert(Phys_addr phys, V_pfn const &virt, Page_order size,
                                Attr page_attribs)
{
  (void)size;
  assert (size == Page_order(0));

  Entry *c = get_cap(virt);

  if (!c && !(c = caps_alloc(virt)))
    return Obj::Insert_err_nomem;

  if (c->valid())
    {
      if (c->obj() == phys)
	{
	  if (EXPECT_FALSE(c->rights() == page_attribs))
	    return Obj::Insert_warn_exists;

	  c->add_rights(page_attribs);
	  return Obj::Insert_warn_attrib_upgrade;
	}
      else
	return Obj::Insert_err_exists;
    }

  Obj::set_entry(virt, c);
  c->set(phys, page_attribs);
  return Obj::Insert_ok;
}

#line 345 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"

 
template<typename BASE> inline Obj_space_phys_override<BASE> *
Obj_space_phys_override<BASE>::get_space(Obj_space *base)
{ return static_cast<Obj_space_phys_override<BASE> *>(base); }

//
// IMPLEMENTATION of function templates
//


#line 147 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"


template< typename SPACE > typename Obj_space_phys<SPACE>::Entry *
Obj_space_phys<SPACE>::get_cap(Cap_index index)
{
  if (EXPECT_FALSE(!_dir))
    return 0;

  unsigned d_idx = cxx::int_value<Cap_index>(index) >> Obj::Caps_per_page_ld2;
  if (EXPECT_FALSE(d_idx >= Slots_per_dir))
    return 0;

  Cap_table *tab = _dir->d[d_idx];

  if (EXPECT_FALSE(!tab))
    return 0;

  unsigned offs  = cxx::get_lsb(cxx::int_value<Cap_index>(index), Obj::Caps_per_page_ld2);
  return &tab->e[offs];
}

#line 167 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"


template< typename SPACE > typename Obj_space_phys<SPACE>::Entry *
Obj_space_phys<SPACE>::caps_alloc(Cap_index virt)
{
  static_assert(sizeof(Cap_table) == Config::PAGE_SIZE, "cap table size mismatch");
  unsigned d_idx = cxx::int_value<Cap_index>(virt) >> Obj::Caps_per_page_ld2;
  if (EXPECT_FALSE(d_idx >= Slots_per_dir))
    return 0;

  void *mem = Kmem_alloc::allocator()->q_unaligned_alloc(ram_quota(), Config::PAGE_SIZE);

  if (!mem)
    return 0;

  Obj::add_cap_page_dbg_info(mem, SPACE::get_space(this),  cxx::int_value<Cap_index>(virt));

  Mem::memset_mwords(mem, 0, Config::PAGE_SIZE / sizeof(Mword));

  Cap_table *tab = _dir->d[d_idx] = (Cap_table*)mem;
  return &tab->e[ cxx::get_lsb(cxx::int_value<Cap_index>(virt), Obj::Caps_per_page_ld2)];
}

#line 189 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"


template< typename SPACE > void
Obj_space_phys<SPACE>::caps_free()
{
  if (!_dir)
    return;

  Cap_dir *d = _dir;
  _dir = 0;

  Kmem_alloc *a = Kmem_alloc::allocator();
  for (unsigned i = 0; i < Slots_per_dir; ++i)
    {
      if (!d->d[i])
        continue;

      Obj::remove_cap_page_dbg_info(d->d[i]);
      a->q_unaligned_free(ram_quota(), Config::PAGE_SIZE, d->d[i]);
    }

  a->q_unaligned_free(ram_quota(), Config::PAGE_SIZE, d);
}

#line 337 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"


template< typename SPACE > typename Obj_space_phys<SPACE>::Entry *
Obj_space_phys<SPACE>::jdb_lookup_cap(Cap_index index)
{ return get_cap(index); }

#line 350 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/obj_space_phys_util.cpp"


template<typename BASE> Obj::Entry *
Obj_space_phys_override<BASE>::jdb_lookup_cap(Cap_index index) 
{ return Obj_space::jdb_lookup_cap(index); }

#endif // obj_space_phys_util_h
