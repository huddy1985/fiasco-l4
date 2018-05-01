// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef mapdb_i_h
#define mapdb_i_h
#line 272 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"

//
// class Treemap_ops
//
// Helper operations for Treemaps (used in Mapping_tree::flush)

class Treemap_ops
{
  typedef Treemap::Order Order;
  typedef Treemap::Page Page;
  typedef Treemap::Pfn Pfn;
  typedef Treemap::Pcnt Pcnt;
  Order _page_shift;

public:  
#line 288 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Treemap_ops(Order page_shift);
  
#line 293 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Treemap::Pfn
  to_vaddr(Page v) const;
  
#line 298 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Treemap::Pcnt
  page_size() const;
  
#line 303 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  unsigned long
  mem_size(Treemap const *submap) const;
  
#line 322 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  void
  grant(Treemap *submap, Space *new_space, Page page) const;
  
#line 343 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Space *
  owner(Treemap const *submap) const;
  
#line 348 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline bool
  is_partial(Treemap const *submap, Treemap::Pcnt offs_begin,
                          Treemap::Pcnt offs_end) const;
  
#line 357 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline void 
  del(Treemap *submap) const;
  
#line 362 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline void
  flush(Treemap *submap,
                     Treemap::Pcnt offs_begin, Treemap::Pcnt offs_end) const;
};

//
// IMPLEMENTATION of inline functions follows
//


#line 221 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Physframe *
Physframe::alloc(size_t size)
{
#if 1				// Optimization: See constructor
  void *mem = Kmem_alloc::allocator()->unaligned_alloc(mem_size(size));
  if (mem)
    memset(mem, 0, size * sizeof(Physframe));
  return (Physframe *)mem;
#else
  Physframe* block
    = (Physframe *)Kmem_alloc::allocator()->unaligned_alloc(mem_size(size));
  assert (block);
  for (unsigned i = 0; i < size; ++i)
    new (block + i) Physframe();

  return block;
#endif
}

#line 397 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


//
// Treemap members
//


inline Treemap::Treemap(Page key_end, Space *owner_id,
                 Pfn page_offset, Order page_shift,
                 const size_t* sub_shifts, unsigned sub_shifts_max,
                 Physframe *physframe)
  : _key_end(key_end),
    _owner_id(owner_id),
    _page_offset(page_offset),
    _page_shift(page_shift),
    _physframe(physframe),
    _sub_shifts(sub_shifts),
    _sub_shifts_max(sub_shifts_max)
{
  assert (_physframe);
}

#line 286 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Treemap_ops::Treemap_ops(Order page_shift)
: _page_shift(page_shift)
{}

#line 291 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Treemap::Pfn
Treemap_ops::to_vaddr(Page v) const
{ return Pfn(cxx::int_value<Page>(v << _page_shift)); }

#line 296 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Treemap::Pcnt
Treemap_ops::page_size() const
{ return Pcnt(1) << _page_shift; }

#line 341 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Space *
Treemap_ops::owner(Treemap const *submap) const
{ return submap->owner(); }

#line 346 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


inline bool
Treemap_ops::is_partial(Treemap const *submap, Treemap::Pcnt offs_begin,
                        Treemap::Pcnt offs_end) const
{
  return offs_begin > Treemap::Pcnt(0)
         || offs_end < submap->size();
}

#line 355 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


inline void 
Treemap_ops::del(Treemap *submap) const
{ delete submap; }

#line 360 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


inline void
Treemap_ops::flush(Treemap *submap,
                   Treemap::Pcnt offs_begin, Treemap::Pcnt offs_end) const
{
  typedef Treemap::Pcnt Pcnt;
  typedef Treemap::Pfn Pfn;

  for (Treemap::Page i = submap->trunc_to_page(offs_begin);
      i < submap->round_to_page(offs_end);
      ++i)
    {
      Pcnt page_offs_begin = submap->to_vaddr(i) - Pfn(0);
      Pcnt page_offs_end = page_offs_begin + submap->page_size();

      Physframe* subframe = submap->frame(i);

      if (!subframe->tree)
        continue;

      auto guard = lock_guard(subframe->lock);

      if (offs_begin <= page_offs_begin && offs_end >= page_offs_end)
	subframe->tree.reset();
      else
	{
          // FIXME: do we have to check for subframe->tree != 0 here ?
	  submap->flush(subframe, subframe->tree->mappings(), false,
	    page_offs_begin > offs_begin
	    ? Pcnt(0) : cxx::get_lsb(offs_begin - page_offs_begin, _page_shift),
	    page_offs_end < offs_end
	    ? page_size()
	    : cxx::get_lsb(offs_end - page_offs_begin - Pcnt(1), _page_shift) + Pcnt(1));
	}
    }
}

#endif // mapdb_i_h
