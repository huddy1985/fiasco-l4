// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef mapdb_h
#define mapdb_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"

#include "slab_cache.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
#include "l4_types.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
#include "types.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
#include "mapping.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
#include "mapping_tree.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
#include "auto_quota.h"

//
// INTERFACE definition follows 
//

#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"

struct Mapping_tree;		// forward decls
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
class Physframe;
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
class Treemap;
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
class Space;
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"

/** A mapping database.
 */
class Mapdb
{
  friend class Jdb_mapdb;

public:
  typedef ::Mapping Mapping;
  typedef Mapping::Pfn Pfn;
  typedef Mapping::Pcnt Pcnt;
  typedef Mdb_types::Order Order;

  // TYPES
  class Frame
  {
    friend class Mapdb;
    Treemap* treemap;
    Physframe* frame;

  public:
    inline Pfn vaddr(Mapping* m) const;
    inline Order page_shift() const;
  };

  // for mapdb_t
  Treemap *dbg_treemap() const
  { return _treemap; }

private:
  // DATA
  Treemap* const _treemap;

public:  
#line 812 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  template<typename F> static inline void
  foreach_mapping(Mapdb::Frame const &f, Mapping* parent,
                         Mapdb::Pfn va_begin, Mapdb::Pfn va_end, F func);
  
#line 821 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  // 
  // class Mapdb
  // 
  
  /** Constructor.
      @param End physical end address of RAM.  (Used only if 
             Config::Mapdb_ram_only is true.) 
   */
  
  Mapdb(Space *owner, Mapping::Page end_frame, size_t const *page_shifts,
               unsigned page_shifts_max);
  
#line 841 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  /** Destructor. */
  
  ~Mapdb();
  
#line 848 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  /** Insert a new mapping entry with the given values as child of
      "parent".
      We assume that there is at least one free entry at the end of the
      array so that at least one insert() operation can succeed between a
      lookup()/free() pair of calls.  This is guaranteed by the free()
      operation which allocates a larger tree if the current one becomes
      to small.
      @param parent Parent mapping of the new mapping.
      @param space  Number of the address space into which the mapping is entered
      @param va     Virtual address of the mapped page.
      @param size   Size of the mapping.  For memory mappings, 4K or 4M.
      @return If successful, new mapping.  If out of memory or mapping 
             tree full, 0.
      @post  All Mapping* pointers pointing into this mapping tree,
             except "parent" and its parents, will be invalidated.
   */
  
  Mapping *
  insert(const Mapdb::Frame& frame, Mapping* parent, Space *space,
                Pfn va, Pfn phys, Pcnt size);
  
#line 874 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  /** 
   * Lookup a mapping and lock the corresponding mapping tree.  The returned
   * mapping pointer, and all other mapping pointers derived from it, remain
   * valid until free() is called on one of them.  We guarantee that at most 
   * one insert() operation succeeds between one lookup()/free() pair of calls 
   * (it succeeds unless the mapping tree is fu68,ll).
   * @param space Number of virtual address space in which the mapping 
   *              was entered
   * @param va    Virtual address of the mapping
   * @param phys  Physical address of the mapped pag frame
   * @return mapping, if found; otherwise, 0
   */
  
  bool
  lookup(Space *space, Pfn va, Pfn phys,
               Mapping** out_mapping, Mapdb::Frame* out_lock);
  
#line 895 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  /** Unlock the mapping tree to which the mapping belongs.  Once a tree
      has been unlocked, all Mapping instances pointing into it become
      invalid.
  
      A mapping tree is locked during lookup().  When the tree is
      locked, the tree may be traversed (using member functions of
      Mapping, which serves as an iterator over the tree) or
      manipulated (using insert(), free(), flush(), grant()).  Note that
      only one insert() is allowed during each locking cycle.
  
      @param mapping_of_tree Any mapping belonging to a mapping tree.
   */
  
  static void
  free(const Mapdb::Frame& f);
  
#line 914 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  /** Delete mappings from a tree.  This function deletes mappings
      recusively.
      @param m Mapping that denotes the subtree that should be deleted.
      @param me_too If true, delete m as well; otherwise, delete only 
             submappings.
   */
  
  static void
  flush(const Mapdb::Frame& f, Mapping *m, L4_map_mask mask,
               Pfn va_start, Pfn va_end);
  
#line 936 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  /** Change ownership of a mapping.
      @param m Mapping to be modified.
      @param new_space Number of address space the mapping should be 
                       transferred to
      @param va Virtual address of the mapping in the new address space
   */
  
  bool
  grant(const Mapdb::Frame& f, Mapping *m, Space *new_space,
               Pfn va);
  
#line 950 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  /** Return page size of given mapping and frame. */
  
  static inline Mapdb::Order
  shift(const Mapdb::Frame& f, Mapping * /*m*/);
  
#line 960 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  static inline Mapdb::Pfn
  vaddr(const Mapdb::Frame& f, Mapping* m);
  
#line 981 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline bool
  valid_address(Pfn phys);
  
#line 991 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Mapdb::Mapping *
  check_for_upgrade(Pfn phys,
                           Space *from_id, Pfn snd_addr,
                           Space *to_id, Pfn rcv_addr,
                           Frame *mapdb_frame);
  
#line 1069 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  bool
  find_space(Space *s);

private:  
#line 758 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  //
  // class Mapdb_iterator
  //
   
  template<typename F> static inline void
  _foreach_mapping(Mapping_tree *tree, Mapping *parent, bool me_too, Mapdb::Order size,
                          Mapdb::Pfn va_begin, Mapdb::Pfn va_end, F func);
};
#line 47 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"

// 
// class Physframe
// 

/** Array elements for holding frame-specific data. */
class Physframe : public Base_mappable
{
  friend class Mapdb;
  friend class Treemap;
  friend class Jdb_mapdb;

public:  
#line 216 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  static inline unsigned long
  mem_size(size_t size);

private:  
#line 223 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  static inline Physframe *
  alloc(size_t size);
  
#line 244 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline ~Physframe();
  
#line 263 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  // inline NEEDS[Physframe::~Physframe]
  static void 
  free(Physframe *block, size_t size);
}; // struct Physframe
#line 59 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


// 
// class Treemap
// 

class Treemap
{
public:
  typedef Mapping_tree::Page Page;
  typedef Mapdb::Pfn Pfn;
  typedef Mapdb::Pcnt Pcnt;
  typedef Mapdb::Order Order;

private:
  friend class Jdb_mapdb;
  friend class Treemap_ops;

  // DATA
  Page _key_end;		///< Number of Physframe entries
  Space *_owner_id;	///< ID of owner of mapping trees 
  Pfn _page_offset;	///< Virt. page address in owner's addr space
  Order _page_shift;		///< Page size of mapping trees
  Physframe* _physframe;	///< Pointer to Physframe array
  const size_t* const _sub_shifts; ///< Pointer to array of sub-page sizes
  const unsigned _sub_shifts_max;  ///< Number of valid _page_sizes entries

public:
  Page end() const { return _key_end; }
  Pfn page_offset() const { return _page_offset; }

public:  
#line 420 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Treemap::Page
  round_to_page(Pcnt v) const;
  
#line 428 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Treemap::Page
  trunc_to_page(Pcnt v) const;
  
#line 433 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Treemap::Page
  trunc_to_page(Pfn v) const;
  
#line 438 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Treemap::Pfn
  to_vaddr(Page v) const;
  
#line 443 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Treemap::Pcnt
  page_size() const;
  
#line 453 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  static Treemap *
  create(Page key_end, Space *owner_id,
                  Pfn page_offset, Order page_shift,
                  const size_t* sub_shifts, unsigned sub_shifts_max);
  
#line 483 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline ~Treemap();
  
#line 497 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline void
  operator delete (void *block);
  
#line 507 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Treemap::Order
  page_shift() const;
  
#line 514 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Space *
  owner() const;
  
#line 522 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Treemap::Pcnt
  size() const;
  
#line 529 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Treemap::Pfn
  end_addr() const;
  
#line 536 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline Treemap::Pfn
  vaddr(Mapping* m) const;
  
#line 543 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  inline void
  set_vaddr(Mapping* m, Pfn address) const;
  
#line 550 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  Physframe*
  tree(Page key);
  
#line 587 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  Physframe*
  frame(Page key) const;
  
#line 596 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  bool
  lookup(Pcnt key, Space *search_space, Pfn search_va,
                  Mapping** out_mapping, Treemap** out_treemap,
                  Physframe** out_frame);
  
#line 647 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  Mapping *
  insert(Physframe* frame, Mapping* parent, Space *space,
                  Pfn va, Pcnt phys, Pcnt size);
  
#line 721 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  void 
  free(Physframe* f);
  
#line 733 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  void
  flush(Physframe* f, Mapping* parent, bool me_too,
                 Pcnt offs_begin, Pcnt offs_end);
  
#line 749 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  bool
  grant(Physframe* f, Mapping* m, Space *new_space, Pfn va);
  
#line 1017 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  bool
  find_space(Space *s);

private:  
#line 399 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  //
  // Treemap members
  //
  
  
  inline Treemap(Page key_end, Space *owner_id,
                   Pfn page_offset, Order page_shift,
                   const size_t* sub_shifts, unsigned sub_shifts_max,
                   Physframe *physframe);
  
#line 448 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  static inline unsigned long
  quota_size(Page key_end);
  
#line 491 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
  static Slab_cache *
  allocator();
};
#line 965 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 93 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"

/* The mapping database.

 * This implementation encodes mapping trees in very compact arrays of
 * fixed sizes, prefixed by a tree header (Mapping_tree).  Array
 * sizes can vary from 4 mappings to 4<<15 mappings.  For each size,
 * we set up a slab allocator.  To grow or shrink the size of an
 * array, we have to allocate a larger or smaller tree from the
 * corresponding allocator and then copy the array elements.
 * 
 * The array elements (Mapping) contain a tree depth element.  This
 * depth and the relative position in the array is all information we
 * need to derive tree structure information.  Here is an example:
 * 
 * array
 * element   depth
 * number    value    comment
 * --------------------------
 * 0         0        Sigma0 mapping
 * 1         1        child of element #0 with depth 0
 * 2         2        child of element #1 with depth 1
 * 3         2        child of element #1 with depth 1
 * 4         3        child of element #3 with depth 2
 * 5         2        child of element #1 with depth 1
 * 6         3        child of element #5 with depth 2
 * 7         1        child of element #0 with depth 0
 * 
 * This array is a pre-order encoding of the following tree:
 * 
 *                   0
 * 	          /     \ 
 *               1       7
 *            /  |  \                   
 *           2   3   5
 *               |   |
 *        	 4   6
       	       	   
 * The mapping database (Mapdb) is organized in a hierarchy of
 * frame-number-keyed maps of Mapping_trees (Treemap).  The top-level
 * Treemap contains mapping trees for superpages.  These mapping trees
 * may contain references to Treemaps for subpages.  (Original credits
 * for this idea: Christan Szmajda.)
 *
 *        Treemap
 *        -------------------------------
 *     	  | | | | | | | | | | | | | | | | array of ptr to 4M Mapping_tree's
 *        ---|---------------------------
 *           |
 *           v a Mapping_tree
 *           ---------------
 *           |             | tree header
 *           |-------------|
 *           |             | 4M Mapping *or* ptr to nested Treemap
 *           |             | e.g.
 *           |      ----------------| Treemap
 *           |             |        v array of ptr to 4K Mapping_tree's
 *           ---------------        -------------------------------
 *                                  | | | | | | | | | | | | | | | |
 *                                  ---|---------------------------
 *                                     |
 *                                     v a Mapping_tree
 *                             	       ---------------
 *                                     |             | tree header
 *                                     |-------------|
 *                                     |             | 4K Mapping
 *                                     |             |
 *                                     |             |
 *                                     |             |
 *                                     ---------------

 * IDEAS for enhancing this implementation: 

 * We often have to find a tree header corresponding to a mapping.
 * Currently, we do this by iterating backwards over the array
 * containing the mappings until we find the Sigma0 mapping, from
 * whose address we can compute the address of the tree header.  If
 * this becomes a problem, we could add one more byte to the mappings
 * with a hint (negative array offset) where to find the sigma0
 * mapping.  (If the hint value overflows, just iterate using the hint
 * value of the mapping we find with the first hint value.)  Another
 * idea (from Adam) would be to just look up the tree header by using
 * the physical address from the page-table lookup, but we would need
 * to change the interface of the mapping database for that (pass in
 * the physical address at all times), or we would have to include the
 * physical address (or just the address of the tree header) in the
 * Mapdb-user-visible Mapping (which could be different from the
 * internal tree representation).  (XXX: Implementing one of these
 * ideas is probably worthwile doing!)

 * Instead of copying whole trees around when they grow or shrink a
 * lot, or copying parts of trees when inserting an element, we could
 * give up the array representation and add a "next" pointer to the
 * elements -- that is, keep the tree of mappings in a
 * pre-order-encoded singly-linked list (credits to: Christan Szmajda
 * and Adam Wiggins).  24 bits would probably be enough to encode that
 * pointer.  Disadvantages: Mapping entries would be larger, and the
 * cache-friendly space-locality of tree entries would be lost.
 */

#include <cassert>
#line 193 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
#include <cstring>
#line 194 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"

#include "config.h"
#line 196 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
#include "globals.h"
#line 197 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
#include "helping_lock.h"
#line 198 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
#include "kmem_alloc.h"
#line 199 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
#include "kmem_slab.h"
#line 200 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
#include "ram_quota.h"
#line 201 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
#include "std_macros.h"
#line 202 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"
#include <new>

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 418 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Treemap::Page
Treemap::round_to_page(Pcnt v) const
{
  return Page(cxx::int_value<Pcnt>((v + ((Pcnt(1) << _page_shift) - Pcnt(1)))
                                   >> _page_shift));
}

#line 810 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"

 
template<typename F> inline void
Mapdb::foreach_mapping(Mapdb::Frame const &f, Mapping* parent,
                       Mapdb::Pfn va_begin, Mapdb::Pfn va_end, F func)
{
  _foreach_mapping(f.frame->tree.get(), parent, false, f.treemap->page_shift(),
                   va_begin, va_end, func);
}

#line 505 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Treemap::Order
Treemap::page_shift() const
{
  return _page_shift;
}

#line 949 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"

/** Return page size of given mapping and frame. */

inline Mapdb::Order
Mapdb::shift(const Mapdb::Frame& f, Mapping * /*m*/)
{
  // XXX add special case for _mappings[0]: Return superpage size.
  return f.treemap->page_shift();
}

#line 436 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Treemap::Pfn
Treemap::to_vaddr(Page v) const
{ return Pfn(cxx::int_value<Page>(v << _page_shift)); }

#line 534 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Treemap::Pfn
Treemap::vaddr(Mapping* m) const
{
  return to_vaddr(m->page());
}

#line 958 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Mapdb::Pfn
Mapdb::vaddr(const Mapdb::Frame& f, Mapping* m)
{
  return f.treemap->vaddr(m);
}

#line 519 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"



inline Treemap::Pcnt
Treemap::size() const
{
  return to_vaddr(_key_end) - Pfn(0);
}

#line 527 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Treemap::Pfn
Treemap::end_addr() const
{
  return _page_offset + size();
}

#line 979 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


inline bool
Mapdb::valid_address(Pfn phys)
{
  // on the root level physical and virtual frame numbers
  // are the same
  return phys < _treemap->end_addr();
}

#line 988 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"



inline Mapdb::Mapping *
Mapdb::check_for_upgrade(Pfn phys,
                         Space *from_id, Pfn snd_addr,
                         Space *to_id, Pfn rcv_addr,
                         Frame *mapdb_frame)
{
  // Check if we can upgrade mapping.  Otherwise, flush target
  // mapping.
  Mapping* receiver_mapping;
  if (valid_address(phys) // Can lookup in mapdb
      && lookup(to_id, rcv_addr, phys, &receiver_mapping, mapdb_frame))
    {
      Mapping* receiver_parent = receiver_mapping->parent();
      if (receiver_parent->space() == from_id
	  && vaddr(*mapdb_frame, receiver_parent) == snd_addr)
	return receiver_parent;
      else		// Not my child -- cannot upgrade
	free(*mapdb_frame);
    }
  return 0;
}

#line 214 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


inline unsigned long
Physframe::mem_size(size_t size)
{
  return (size*sizeof(Physframe) + 1023) & ~1023;
}

#line 426 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Treemap::Page
Treemap::trunc_to_page(Pcnt v) const
{ return Page(cxx::int_value<Pcnt>(v >> _page_shift)); }

#line 431 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Treemap::Page
Treemap::trunc_to_page(Pfn v) const
{ return Page(cxx::int_value<Pfn>(v >> _page_shift)); }

#line 441 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Treemap::Pcnt
Treemap::page_size() const
{ return Pcnt(1) << _page_shift; }

#line 479 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"




inline Treemap::~Treemap()
{
  Physframe::free(_physframe, cxx::int_value<Page>(_key_end));
}

#line 446 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


inline unsigned long
Treemap::quota_size(Page key_end)
{ return Physframe::mem_size(cxx::int_value<Page>(key_end)) + sizeof(Treemap); }

#line 494 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"



inline void
Treemap::operator delete (void *block)
{
  Treemap *t = reinterpret_cast<Treemap*>(block);
  Space *id = t->_owner_id;
  allocator()->free(block);
  Mapping_tree::quota(id)->free(Treemap::quota_size(t->_key_end));
}

#line 512 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Space *
Treemap::owner() const
{
  return _owner_id;
}

#line 541 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


inline void
Treemap::set_vaddr(Mapping* m, Pfn address) const
{
  m->set_page(trunc_to_page(address));
}

#line 965 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"

// 
// class Mapdb::Frame
// 


inline Mapdb::Pfn
Mapdb::Frame::vaddr(Mapping* m) const
{ return treemap->vaddr(m); }

#line 974 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"


inline Mapdb::Order
Mapdb::Frame::page_shift() const
{ return treemap->page_shift(); }

//
// IMPLEMENTATION of function templates
//


#line 755 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapdb.cpp"



//
// class Mapdb_iterator
//
 
template<typename F> inline void
Mapdb::_foreach_mapping(Mapping_tree *tree, Mapping *parent, bool me_too, Mapdb::Order size,
                        Mapdb::Pfn va_begin, Mapdb::Pfn va_end, F func)
{
  typedef Mapping::Page Page;

  for (Mapping *cursor = tree->next_child(parent, parent); cursor;
       cursor = tree->next_child(parent,cursor))
    {
      if (cursor && !cursor->submap())
        {
          func(cursor, size);
          me_too = true;
        }
      else
        {
          Treemap *submap = cursor->submap();
          Order ps = submap->page_shift();
          Pfn po = submap->page_offset();
          Page start(0);
          Page end(submap->end());

          if (!me_too)
            {
              if (va_begin > po)
                start = Page(cxx::int_value<Pcnt>((va_begin - po) >> ps));

              if (va_end < po + submap->size())
                end = submap->round_to_page(va_end - po);
            }

          for (Page sub_page = start; sub_page < end; ++sub_page)
            {
              Physframe *f = submap->frame(sub_page);
              if (!f->tree)
                continue;

              auto guard = lock_guard(f->lock);

              _foreach_mapping(f->tree.get(), f->tree->mappings(), me_too, submap->page_shift(),
                               va_begin, va_end, func);
            }

        }


    }
}

#endif // mapdb_h
