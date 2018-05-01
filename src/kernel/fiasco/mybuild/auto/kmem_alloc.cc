// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "kmem_alloc.h"
#include "kmem_alloc_i.h"

#line 86 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"

static Kmem_alloc::Alloc _a;
#line 88 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
Kmem_alloc::Alloc *Kmem_alloc::a = &_a;
#line 89 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
unsigned long Kmem_alloc::_orig_free;
#line 90 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
Kmem_alloc::Lock Kmem_alloc::lock;
#line 91 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
Kmem_alloc* Kmem_alloc::_alloc;
#line 319 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"

Kmem_alloc_reaper::Reaper_list Kmem_alloc_reaper::mem_reapers;

#line 109 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"


void
Kmem_alloc::allocator(Kmem_alloc *a)
{
  _alloc=a;
}

#line 116 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"

FIASCO_INIT
void
Kmem_alloc::init()
{
  static Kmem_alloc al;
  Kmem_alloc::allocator(&al);
}

#line 124 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"


void
Kmem_alloc::dump() const
{ a->dump(); }

#line 160 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"


void *
Kmem_alloc::unaligned_alloc(unsigned long size)
{
  assert(size >=8 /*NEW INTERFACE PARANIOIA*/);
  void* ret;

  {
    auto guard = lock_guard(lock);
    ret = a->alloc(size);
  }

  if (!ret)
    {
      Kmem_alloc_reaper::morecore (/* desperate= */ true);

      auto guard = lock_guard(lock);
      ret = a->alloc(size);
    }

  return ret;
}

#line 183 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"


void
Kmem_alloc::unaligned_free(unsigned long size, void *page)
{
  assert(size >=8 /*NEW INTERFACE PARANIOIA*/);
  auto guard = lock_guard(lock);
  a->free(page, size);
}

#line 192 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"


FIASCO_INIT
unsigned long
Kmem_alloc::create_free_map(Kip const *kip, Mem_region_map_base *map)
{
  unsigned long available_size = 0;

  for (auto const &md: kip->mem_descs_a())
    {
      if (!md.valid())
	{
	  const_cast<Mem_desc &>(md).type(Mem_desc::Undefined);
	  continue;
	}

      if (md.is_virtual())
	continue;

      unsigned long s = md.start();
      unsigned long e = md.end();

      // Sweep out stupid descriptors (that have the end before the start)

      switch (md.type())
	{
	case Mem_desc::Conventional:
	  s = (s + Config::PAGE_SIZE - 1) & ~(Config::PAGE_SIZE - 1);
	  e = ((e + 1) & ~(Config::PAGE_SIZE - 1)) - 1;
	  if (e <= s)
	    break;
	  available_size += e - s + 1;
	  if (!map->add(Mem_region(s, e)))
	    panic("Kmem_alloc::create_free_map(): memory map too small");
	  break;
	case Mem_desc::Reserved:
	case Mem_desc::Dedicated:
	case Mem_desc::Shared:
	case Mem_desc::Arch:
	case Mem_desc::Bootloader:
	  s = s & ~(Config::PAGE_SIZE - 1);
	  e = ((e + Config::PAGE_SIZE) & ~(Config::PAGE_SIZE - 1)) - 1;
	  if (!map->sub(Mem_region(s, e)))
	    panic("Kmem_alloc::create_free_map(): memory map too small");
	  break;
	default:
	  break;
	}
    }

  return available_size;
}

#line 328 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"


size_t
Kmem_alloc_reaper::morecore(bool desperate)
{
  size_t freed = 0;

  for (Reaper_list::Const_iterator reaper = mem_reapers.begin();
       reaper != mem_reapers.end(); ++reaper)
    {
      freed += reaper->_reap(desperate);
    }

  return freed;
}
