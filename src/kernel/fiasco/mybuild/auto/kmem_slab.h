// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kmem_slab_h
#define kmem_slab_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_slab.cpp"

#include <cstddef>		// size_t
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_slab.cpp"
#include "buddy_alloc.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_slab.cpp"
#include "kmem_alloc.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_slab.cpp"
#include "config.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_slab.cpp"
#include "lock_guard.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_slab.cpp"
#include "spin_lock.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_slab.cpp"

#include "slab_cache.h"		// Slab_cache
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_slab.cpp"
#include <cxx/slist>
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_slab.cpp"
#include <cxx/type_traits>

//
// INTERFACE definition follows 
//

#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_slab.cpp"

class Kmem_slab : public Slab_cache, public cxx::S_list_item
{
  friend class Jdb_kern_info_memory;
  typedef cxx::S_list_bss<Kmem_slab> Reap_list;

  // STATIC DATA
  static Reap_list reap_list;

public:  
#line 187 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_slab.cpp"
  // Specializations providing their own block_alloc()/block_free() can
  // also request slab sizes larger than one page.
  
  Kmem_slab(unsigned elem_size,
                       unsigned alignment,
                       char const *name,
                       unsigned long min_size = Buddy_alloc::Min_size,
                       unsigned long max_size = Buddy_alloc::Max_size);
  
#line 201 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_slab.cpp"
  ~Kmem_slab();
  
#line 226 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_slab.cpp"
  // 
  // Memory reaper
  // 
  
  static size_t
  reap_all (bool desperate);

protected:  
#line 175 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_slab.cpp"
  // Specializations providing their own block_alloc()/block_free() can
  // also request slab sizes larger than one page.
  
  Kmem_slab(unsigned long slab_size,
  				   unsigned elem_size,
  				   unsigned alignment,
  				   char const *name);

private:  
#line 207 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_slab.cpp"
  // Callback functions called by our super class, Slab_cache, to
  // allocate or free blocks
  
  virtual void *
  block_alloc(unsigned long size, unsigned long);
  
#line 220 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_slab.cpp"
  virtual void
  block_free(void *block, unsigned long size);
};
#line 22 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_slab.cpp"


/**
 * Slab allocator for the given size and alignment.
 * \tparam SIZE   Size of an object in bytes.
 * \tparam ALIGN  Alignment of an object in bytes.
 *
 * This class provides a per-size instance of a slab cache.
 */
template< unsigned SIZE, unsigned ALIGN = 8 >
class Kmem_slab_for_size
{
public:
  static void *alloc() { return _s.alloc(); }

  template<typename Q> static
  void *q_alloc(Q *q) { return _s.template q_alloc<Q>(q); }

  static void free(void *e) { _s.free(e); }

  template<typename Q> static
  void q_free(Q *q, void *e) { _s.template q_free<Q>(q, e); }

  static Slab_cache *slab() { return &_s; }

protected:
  static Kmem_slab _s;
};
#line 50 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_slab.cpp"

template< unsigned SIZE, unsigned ALIGN >
Kmem_slab Kmem_slab_for_size<SIZE, ALIGN>::_s(SIZE, ALIGN, "fixed size");
#line 53 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_slab.cpp"


/**
 * Allocator for fixed-size objects based on the buddy allocator.
 * \tparam SIZE  The size and the alignment of an object in bytes.
 *
 * Note: This allocator uses the buddy allocator and allocates memory in sizes
 * supported by the buddy allocator.
 *
 * Note: Kmem_buddy_for_size and Kmem_slab_for_size must provide compatible
 * interfaces in order to be used interchangeably.
 */
template<unsigned SIZE>
class Kmem_buddy_for_size
{
public:
  static void *alloc()
  { return Kmem_alloc::allocator()->unaligned_alloc(SIZE); }

  template<typename Q> static
  void *q_alloc(Q *q)
  { return Kmem_alloc::allocator()->q_unaligned_alloc(q, SIZE); }

  static void free(void *e)
  { Kmem_alloc::allocator()->unaligned_free(SIZE, e); }

  template<typename Q> static
  void q_free(Q *q, void *e)
  { Kmem_alloc::allocator()->q_unaligned_free(q, SIZE, e); }
};
#line 83 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_slab.cpp"

/**
 * Meta allocator to select between Kmem_slab_for_size and Kmem_buddy_for_size.
 *
 * \tparam BUDDY  If true the allocator will use Kmem_buddy_for_size, if
 *                false Kmem_slab_for_size.
 * \tparam SIZE   Size of an object (in bytes) that shall be allocated.
 * \tparam ALIGN  Alignment for each object in bytes.
 */
template<bool BUDDY, unsigned SIZE, unsigned ALIGN>
struct _Kmem_alloc : Kmem_slab_for_size<SIZE, ALIGN> {};
#line 94 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_slab.cpp"

/* Specialization using the buddy allocator */
template<unsigned SIZE, unsigned ALIGN>
struct _Kmem_alloc<true, SIZE, ALIGN> : Kmem_buddy_for_size<SIZE> {};
#line 98 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_slab.cpp"

/**
 * Generic allocator for objects of the given size and alignment.
 * \tparam SIZE   The size of an object in bytes.
 * \tparam ALIGN  The alignment of each allocated object (in bytes).
 *
 * This allocator uses _Kmem_alloc<> to select between a slab allocator or
 * the buddy allocator depending on the given size of the objects.
 * (Currently all objects bigger that 1KB (0x400) are allocated using the
 * buddy allocator.)
 */
template<unsigned SIZE, unsigned ALIGN = 8>
struct Kmem_slab_s : _Kmem_alloc<(SIZE >= 0x400), SIZE, ALIGN> {};
#line 111 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_slab.cpp"

/**
 * Allocator for objects of the given type.
 * \tparam T      Type of the object to be allocated.
 * \tparam ALIGN  Alignment of the objects (in bytes, usually alignof(T)).
 */
template< typename T, unsigned ALIGN = __alignof(T) >
struct Kmem_slab_t : Kmem_slab_s<sizeof(T), ALIGN>
{
  typedef Kmem_slab_s<sizeof(T), ALIGN> Slab;
public:
  explicit Kmem_slab_t(char const *) {}
  Kmem_slab_t() = default;

  template<typename ...ARGS> static
  T *new_obj(ARGS &&...args)
  {
    void *c = Slab::alloc();
    if (EXPECT_TRUE(c != 0))
      return new (c) T(cxx::forward<ARGS>(args)...);
    return 0;
  }

  template<typename Q, typename ...ARGS> static
  T *q_new(Q *q, ARGS &&...args)
  {
    void *c = Slab::template q_alloc<Q>(q);
    if (EXPECT_TRUE(c != 0))
      return new (c) T(cxx::forward<ARGS>(args)...);
    return 0;
  }

  static void del(T *e)
  {
    e->~T();
    Slab::free(e);
  }

  template<typename Q> static
  void q_del(Q *q, T *e)
  {
    e->~T();
    Slab::template q_free<Q>(q, e);
  }
};

#endif // kmem_slab_h
