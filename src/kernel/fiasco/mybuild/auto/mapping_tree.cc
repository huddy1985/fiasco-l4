// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "mapping_tree.h"
#include "mapping_tree_i.h"


#line 301 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping_tree.cpp"
static Kmem_slab *
allocator_for_treesize(int size);
#line 296 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping_tree.cpp"

static Kmem_slab *_allocators[Size_id_max + 1];
#line 298 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping_tree.cpp"
static Mapping_tree_allocators<Size_id_max> _mapping_tree_allocators(_allocators);

#line 299 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping_tree.cpp"


static Kmem_slab *
allocator_for_treesize(int size)
{
  return _allocators[size];
}

#line 318 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping_tree.cpp"


void*
Mapping_tree::operator new (size_t, Mapping_tree::Size_id size_id) throw()
{ return allocator_for_treesize(size_id)->alloc(); }

#line 323 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping_tree.cpp"


void
Mapping_tree::operator delete (void* block)
{
  if (!block)
    return;

  // Try to guess right allocator object -- XXX unportable!
  Mapping_tree* t = static_cast<Mapping_tree*>(block);

  t->check_integrity();

  allocator_for_treesize(t->_size_id)->free(block);
}

#line 338 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping_tree.cpp"

//inline NEEDS[Mapping_depth, Mapping_tree::last]
Mapping_tree::Mapping_tree(Size_id size_id, Page page,
                           Space *owner)
{
  _count = 1;			// 1 valid mapping
  _size_id = size_id;   	// size is equal to Size_factor << 0
#ifndef NDEBUG
  _empty_count = 0;		// no gaps in tree representation
#endif

  _mappings[0].set_depth(Mapping::Depth_root);
  _mappings[0].set_page(page);
  _mappings[0].set_space(owner);

  _mappings[1].set_depth(Mapping::Depth_end);

  // We also always set the end tag on last entry so that we can
  // check whether it has been overwritten.
  last()->set_depth(Mapping::Depth_end);
}

#line 359 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping_tree.cpp"


Mapping_tree::~Mapping_tree()
{
  // special case for copied mapping trees
  for (Mapping *m = _mappings; m < end() && !m->is_end_tag(); ++m)
    {
      if (!m->submap() && !m->unused())
        quota(m->space())->free(sizeof(Mapping));
    }
}

#line 370 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping_tree.cpp"

//inline NEEDS[Mapping_depth, Mapping_tree::last]
Mapping_tree::Mapping_tree(Size_id size_id, Mapping_tree* from_tree)
{
  _size_id = size_id;
  last()->set_depth(Mapping::Depth_end);

  copy_compact_tree(this, from_tree);
}

#line 415 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping_tree.cpp"

// A utility function to find the tree header belonging to a mapping. 

/** Our Mapping_tree.
    @return the Mapping_tree we are in.
 */

Mapping_tree *
Mapping_tree::head_of(Mapping *m)
{
  while (m->depth() > Mapping::Depth_root)
    {
      // jump in bigger steps if this is not a free mapping
      if (m->depth() <= Mapping::Depth_max)
        {
          m -= m->depth();
          continue;
        }

      m--;
    }

  return reinterpret_cast<Mapping_tree *>
    (reinterpret_cast<char *>(m) - sizeof(Mapping_tree));
  // We'd rather like to use offsetof as follows, but it's unsupported
  // for non-POD classes.  So we instead rely on GCC's zero-length
  // array magic (sizeof(Mapping_tree) is the size of the header
  // without the array).
  // return reinterpret_cast<Mapping_tree *>
  //   (reinterpret_cast<char *>(m) - offsetof(Mapping_tree, _mappings));
}

#line 486 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping_tree.cpp"

// This function copies the elements of mapping tree src to mapping
// tree dst, ignoring empty elements (that is, compressing the
// source tree.  In-place compression is supported.

void
Mapping_tree::copy_compact_tree(Mapping_tree *dst, Mapping_tree *src)
{
  unsigned src_count = src->_count; // Store in local variable before
                                    // it can get overwritten

  // Special case: cannot in-place compact a full tree
  if (src == dst && src->number_of_entries() == src_count)
    return;

  // Now we can assume the resulting tree will not be full.
  assert (src_count < dst->number_of_entries());

  dst->_count = 0;
#ifndef NDEBUG
  dst->_empty_count = 0;
#endif

  Mapping *d = dst->mappings();

  for (Mapping *s = src->mappings();
       s && !s->is_end_tag();
       s = src->next(s))
    {
      *d++ = *s;
      dst->_count += 1;
    }

  assert (dst->_count == src_count); // Same number of entries
  assert (d < dst->end());
  // Room for one more entry (the Mapping::Depth_end entry)

  d->set_depth(Mapping::Depth_end);
  dst->last()->set_depth(Mapping::Depth_end);
} // copy_compact_tree()

#line 526 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping_tree.cpp"

// Don't inline this function -- it eats a lot of stack space!
// inline NEEDS[Mapping::data, Mapping::unused, Mapping::is_end_tag,
       //              Mapping_tree::end, Mapping_tree::number_of_entries]
void
Mapping_tree::check_integrity(Space *owner)
{
  (void)owner;
#ifndef NDEBUG
  bool enter_ke = false;
  // Sanity checking
  if (// Either each entry is used
      !(number_of_entries() == static_cast<unsigned>(_count) + _empty_count
      // Or the last used entry is end tag
        || mappings()[_count + _empty_count].is_end_tag()))
    {
      printf("mapdb consistency error: "
             "%u == %u + %u || mappings()[%u + %u].is_end_tag()=%d\n",
             number_of_entries(), static_cast<unsigned>(_count), _empty_count,
             _count, _empty_count, mappings()[_count + _empty_count].is_end_tag());
      enter_ke = true;
    }

  Mapping *m = mappings();

  if (!(m->is_end_tag()   // When the tree was copied to a new one
        || (!m->unused()  // The first entry is never unused.
            && m->depth() == 0
            && (owner == (Space *)-1 || m->space() == owner))))
    {
      printf("mapdb corrupted: owner=%p\n"
             "  m=%p (end: %s depth: %u space: %p page: %lx)\n",
             owner, m, m->is_end_tag() ? "yes" : "no", m->depth(), m->space(),
             cxx::int_value<Page>(m->page()));
      enter_ke = true;
    }

  unsigned used = 0, dead = 0;

  while (m < end() && !m->is_end_tag())
    {
      if (m->unused())
        dead++;
      else
        used++;

      m++;
    }

  if ((enter_ke |= _count != used))
    printf("mapdb: _count=%u != used=%u\n", _count, used);
  if ((enter_ke |= _empty_count != dead))
    printf("mapdb: _empty_count=%u != dead=%u\n", _empty_count, dead);

  if (enter_ke)
    {
      printf("mapdb:    from %p on CPU%u\n",
             __builtin_return_address(0),
             cxx::int_value<Cpu_number>(current_cpu()));
      kdb_ke("mapdb");
    }

#endif // ! NDEBUG
}

#line 881 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping_tree.cpp"



Mapping *
Base_mappable::lookup(Space *space, Page page)
{
  // get and lock the tree.
  if (EXPECT_FALSE(lock.lock() == Lock::Invalid))
    return 0;
  Mapping_tree *t = tree.get();
  assert (t);
  if (Mapping *m = t->lookup(space, page))
    return m;

  lock.clear();
  return 0;
}

#line 933 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping_tree.cpp"



void 
Base_mappable::pack()
{
  // Before we unlock the tree, we need to make sure that there is
  // room for at least one new mapping.  In particular, this means
  // that the last entry of the array encoding the tree must be free.

  // (1) When we use up less than a quarter of all entries of the
  // array encoding the tree, copy to a smaller tree.  Otherwise, (2)
  // if the last entry is free, do nothing.  Otherwise, (3) if less
  // than 3/4 of the entries are used, compress the tree.  Otherwise,
  // (4) copy to a larger tree.

  Mapping_tree *t = tree.get();
  bool maybe_out_of_memory = false;

  do // (this is not actually a loop, just a block we can "break" out of)
    {
      // (1) Do we need to allocate a smaller tree?
      if (t->_size_id > Mapping_tree::Size_id_min // must not be smallest size
          && (static_cast<unsigned>(t->_count) << 2) < t->number_of_entries())
        {
          Mapping_tree::Size_id sid = t->Mapping_tree::shrink();
          cxx::unique_ptr<Mapping_tree> new_t(new (sid) Mapping_tree(sid, t));

          if (new_t)
            {
              // ivalidate node 0 because we must not free the quota for it
              t->reset();
              t = new_t.get();

              // Register new tree.
              tree = cxx::move(new_t);

              break;
            }
        }

      // (2) Is last entry is free?
      if (t->last()->unused())
        break;			// OK, last entry is free.

      // Last entry is not free -- either compress current array
      // (i.e., move free entries to end of array), or allocate bigger
      // array.

      // (3) Should we compress the tree?
      // We also try to compress if we cannot allocate a bigger
      // tree because there is no bigger tree size.
      if (t->_count < (t->number_of_entries() >> 2)
                      + (t->number_of_entries() >> 1)
          || t->_size_id == Size_id_max) // cannot enlarge?
        {
          if (t->_size_id == Size_id_max)
            maybe_out_of_memory = true;

          Mapping_tree::copy_compact_tree(t, t); // in-place compression

          break;
        }

      // (4) OK, allocate a bigger array.

      Mapping_tree::Size_id sid = t->bigger();
      cxx::unique_ptr<Mapping_tree> new_t(new (sid) Mapping_tree(sid, t));

      if (new_t)
        {
          // ivalidate node 0 because we must not free the quota for it
          t->reset();
          t = new_t.get();

          // Register new tree. 
          tree = cxx::move(new_t);
        }
      else
        {
          // out of memory -- just do tree compression and hope that helps.
          maybe_out_of_memory = true;

          Mapping_tree::copy_compact_tree(t, t); // in-place compression
        }
    }
  while (false);

  // The last entry of the tree should now be free -- exept if we're
  // out of memory.
  assert (t->last()->unused() || maybe_out_of_memory);
  (void) maybe_out_of_memory;
}
