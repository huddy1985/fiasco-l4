// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "mem_space.h"
#include "mem_space_i.h"

#line 355 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


// --------------------------------------------------------------------

#line 419 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"

// --------------------------------------------------------------------

#line 430 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"

// --------------------------------------------------------------------


#line 94 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


Mem_space::Mem_space(Ram_quota *q, Dir_type* pdir)
  : _quota(q), _dir(pdir)
{
  _kernel_space = this;
  _current.cpu(Cpu_number::boot_cpu()) = this;
}

#line 152 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


Mem_space::Status
Mem_space::v_insert(Phys_addr phys, Vaddr virt, Page_order size,
                    Attr page_attribs)
{
  // insert page into page table

  // XXX should modify page table using compare-and-swap

  assert (cxx::is_zero(cxx::get_lsb(Phys_addr(phys), size)));
  assert (cxx::is_zero(cxx::get_lsb(Virt_addr(virt), size)));

  int level;
  for (level = 0; level <= Pdir::Depth; ++level)
    if (Page_order(Pdir::page_order_for_level(level)) <= size)
      break;

  auto i = _dir->walk(virt, level, false,
                            Kmem_alloc::q_allocator(_quota));

  if (EXPECT_FALSE(!i.is_valid() && i.level != level))
    return Insert_err_nomem;

  if (EXPECT_FALSE(i.is_valid()
                   && (i.level != level || Phys_addr(i.page_addr()) != phys)))
    return Insert_err_exists;

  bool const valid = i.is_valid();
  if (valid)
    page_attribs.rights |= i.attribs().rights;

  auto entry = i.make_page(phys, page_attribs);

  if (valid)
    {
      if (EXPECT_FALSE(i.entry() == entry))
        return Insert_warn_exists;

      i.set_page(entry);
      page_protect(Virt_addr::val(virt), Address(1) << Page_order::val(size),
                   *i.pte & Page_all_attribs);

      return Insert_warn_attrib_upgrade;
    }
  else
    {
      i.set_page(entry);
      page_map(Virt_addr::val(phys), Virt_addr::val(virt),
               Address(1) << Page_order::val(size), page_attribs);

      return Insert_ok;
    }

}

#line 207 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


void
Mem_space::v_set_access_flags(Vaddr virt, L4_fpage::Rights access_flags)
{
  auto i = _dir->walk(virt);

  if (EXPECT_FALSE(!i.is_valid()))
    return;

  unsigned page_attribs = 0;

  if (access_flags & L4_fpage::Rights::R())
    page_attribs |= Page_referenced;
  if (access_flags & L4_fpage::Rights::W())
    page_attribs |= Page_dirty;

  i.add_attribs(page_attribs);
}

#line 272 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


bool
Mem_space::v_lookup(Vaddr virt, Phys_addr *phys,
                    Page_order *order, Attr *page_attribs)
{
  auto i = _dir->walk(virt);
  if (order) *order = Page_order(i.page_order());

  if (!i.is_valid())
    return false;

  if (phys) *phys = Phys_addr(i.page_addr());
  if (page_attribs) *page_attribs = i.attribs();

  return true;
}

#line 289 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


L4_fpage::Rights
Mem_space::v_delete(Vaddr virt, Page_order size, L4_fpage::Rights page_attribs)
{
  assert (cxx::is_zero(cxx::get_lsb(Virt_addr(virt), size)));

  auto i = _dir->walk(virt);

  if (EXPECT_FALSE (! i.is_valid()))
    return L4_fpage::Rights(0);

  assert (! (*i.pte & Pt_entry::global())); // Cannot unmap shared pages

  L4_fpage::Rights ret = i.access_flags();

  if (! (page_attribs & L4_fpage::Rights::R()))
    {
      // downgrade PDE (superpage) rights
      i.del_rights(page_attribs);
      page_protect(Virt_addr::val(virt), Address(1) << Page_order::val(size),
                   *i.pte & Page_all_attribs);
    }
  else
    {
      // delete PDE (superpage)
      i.clear();
      page_unmap(Virt_addr::val(virt), Address(1) << Page_order::val(size));
    }

  return ret;
}

#line 321 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"

/**
 * Destructor.  Deletes the address space and unregisters it from
 * Space_index.
 */

void
Mem_space::dir_shutdown()
{
  // free all page tables we have allocated for this address space
  // except the ones in kernel space which are always shared
  _dir->destroy(Virt_addr(0UL),
                Virt_addr(Mem_layout::User_max), 0, Pdir::Depth,
                Kmem_alloc::q_allocator(_quota));

  // free all unshared page table levels for the kernel space
  _dir->destroy(Virt_addr(Mem_layout::User_max + 1),
                Virt_addr(~0UL), 0, Pdir::Super_level,
                Kmem_alloc::q_allocator(_quota));
}

#line 341 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"

/**
 * \brief Free all memory allocated for this Mem_space.
 * \pre Runs after the destructor!
 */

Mem_space::~Mem_space()
{
  if (_dir)
    {
      dir_shutdown();
      Kmem_alloc::allocator()->q_free(_quota, Config::PAGE_SHIFT, _dir);
    }
}

#line 530 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


void
Mem_space::init_page_sizes()
{
  add_page_size(Page_order(Config::PAGE_SHIFT));
  if (Cpu::cpus.cpu(Cpu_number::boot_cpu()).superpages())
    add_page_size(Page_order(22)); // 4MB
}
