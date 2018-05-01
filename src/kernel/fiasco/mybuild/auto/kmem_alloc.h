// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kmem_alloc_h
#define kmem_alloc_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"

#include <auto_quota.h>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
#include <cxx/slist>
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"

#include "spin_lock.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
#include "lock_guard.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
#include "initcalls.h"

//
// INTERFACE definition follows 
//

#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"

class Buddy_alloc;
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
class Mem_region_map_base;
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
class Kip;
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"

template<typename Q> class Kmem_q_alloc;
#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"

class Kmem_alloc
{
  Kmem_alloc();

public:
  typedef Buddy_alloc Alloc;
private:
  typedef Spin_lock<> Lock;
  static Lock lock;
  static Alloc *a;
  static unsigned long _orig_free;
  static Kmem_alloc *_alloc;

public:  
#line 94 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
  static inline Kmem_alloc *
  allocator();
  
#line 103 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
  template<typename Q> static inline Kmem_q_alloc<Q>
  q_allocator(Q *quota);
  
#line 117 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
  static FIASCO_INIT
  void
  init();
  
#line 126 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
  void
  dump() const;
  
#line 131 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
  inline void *
  alloc(size_t o);
  
#line 139 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
  inline void
  free(size_t o, void *p);
  
#line 146 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
  template<typename T> inline T *
  alloc_array(unsigned elems);
  
#line 153 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
  template<typename T> inline void
  free_array(T *b, unsigned elems);
  
#line 162 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
  void *
  unaligned_alloc(unsigned long size);
  
#line 185 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
  void
  unaligned_free(unsigned long size, void *page);
  
#line 248 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
  template< typename Q > inline void *
  q_alloc(Q *quota, size_t order);
  
#line 265 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
  template< typename Q > inline void *
  q_unaligned_alloc(Q *quota, size_t size);
  
#line 282 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
  inline void free_phys(size_t s, Address p);
  
#line 291 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
  template< typename Q > inline void 
  q_free_phys(Q *quota, size_t order, Address obj);
  
#line 300 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
  template< typename Q > inline void 
  q_free(Q *quota, size_t order, void *obj);
  
#line 309 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
  template< typename Q > inline void 
  q_unaligned_free(Q *quota, size_t size, void *obj);
  
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem_alloc-ia32.cpp"
  static inline Phys_mem_addr::Value
  to_phys(void *v);
  
#line 22 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem_alloc-ia32.cpp"
  static FIASCO_INIT
  bool
  base_init();
  
#line 175 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem_alloc-ia32.cpp"
  void
  debug_dump();

protected:  
#line 111 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
  static void
  allocator(Kmem_alloc *a);

private:  
#line 194 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
  static FIASCO_INIT
  unsigned long
  create_free_map(Kip const *kip, Mem_region_map_base *map);
  
#line 188 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem_alloc-ia32.cpp"
  inline unsigned long
  orig_free();
};
#line 29 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"


class Kmem_alloc_reaper : public cxx::S_list_item
{
  size_t (*_reap)(bool desperate);

private:
  typedef cxx::S_list_bss<Kmem_alloc_reaper> Reaper_list;
  static Reaper_list mem_reapers;

public:  
#line 323 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
  inline Kmem_alloc_reaper(size_t (*reap)(bool desperate));
  
#line 330 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
  static size_t
  morecore(bool desperate = false);
};
#line 39 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"

template<typename Q>
class Kmem_q_alloc
{
public:
  Kmem_q_alloc(Q *q, Kmem_alloc *a) : _a(a), _q(q) {}
  bool valid() const { return _a && _q; }
  void *alloc(unsigned long size) const
  {
    Auto_quota<Q> q(_q, size);
    if (EXPECT_FALSE(!q))
      return 0;

    void *b;
    if (EXPECT_FALSE(!(b=_a->unaligned_alloc(size))))
      return 0;

    q.release();
    return b;
  }

  void free(void *block, unsigned long size) const
  {
    _a->unaligned_free(size, block);
    _q->free(size);
  }

  template<typename V>
  Phys_mem_addr::Value to_phys(V v) const
  { return _a->to_phys(v); }

private:
  Kmem_alloc *_a;
  Q *_q;
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 77 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"

#include <cassert>
#line 82 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"
#include "mem_layout.h"
#line 315 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"



#include "atomic.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 92 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"


inline Kmem_alloc *
Kmem_alloc::allocator()
{
  assert (_alloc /* uninitialized use of Kmem_alloc */);
  return _alloc;
}

#line 100 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"


 
template<typename Q> inline Kmem_q_alloc<Q>
Kmem_alloc::q_allocator(Q *quota)
{
  assert (_alloc /* uninitialized use of Kmem_alloc */);
  return Kmem_q_alloc<Q>(quota, _alloc);
}

#line 129 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"


inline void *
Kmem_alloc::alloc(size_t o)
{
  return unaligned_alloc(1UL << o);
}

#line 136 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"



inline void
Kmem_alloc::free(size_t o, void *p)
{
  unaligned_free(1UL << o, p);
}

#line 144 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"

 
template<typename T> inline T *
Kmem_alloc::alloc_array(unsigned elems)
{
  return new (this->unaligned_alloc(sizeof(T) * elems)) T[elems];
}

#line 151 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"

 
template<typename T> inline void
Kmem_alloc::free_array(T *b, unsigned elems)
{
  for (unsigned i = 0; i < elems; ++i)
    b[i].~T();
  this->unaligned_free(b, sizeof(T) * elems);
}

#line 244 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"




template< typename Q > inline void *
Kmem_alloc::q_alloc(Q *quota, size_t order)
{
  Auto_quota<Q> q(quota, 1UL<<order);
  if (EXPECT_FALSE(!q))
    return 0;

  void *b = alloc(order);
  if (EXPECT_FALSE(!b))
    return 0;

  q.release();
  return b;
}

#line 262 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"



template< typename Q > inline void *
Kmem_alloc::q_unaligned_alloc(Q *quota, size_t size)
{
  Auto_quota<Q> q(quota, size);
  if (EXPECT_FALSE(!q))
    return 0;

  void *b;
  if (EXPECT_FALSE(!(b=unaligned_alloc(size))))
    return 0;

  q.release();
  return b;
}

#line 279 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"



inline void Kmem_alloc::free_phys(size_t s, Address p)
{
  void *va = (void*)Mem_layout::phys_to_pmem(p);
  if((unsigned long)va != ~0UL)
    free(s, va);
}

#line 288 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"



template< typename Q > inline void 
Kmem_alloc::q_free_phys(Q *quota, size_t order, Address obj)
{
  free_phys(order, obj);
  quota->free(1UL<<order);
}

#line 297 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"



template< typename Q > inline void 
Kmem_alloc::q_free(Q *quota, size_t order, void *obj)
{
  free(order, obj);
  quota->free(1UL<<order);
}

#line 306 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"



template< typename Q > inline void 
Kmem_alloc::q_unaligned_free(Q *quota, size_t size, void *obj)
{
  unaligned_free(size, obj);
  quota->free(size);
}

#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem_alloc-ia32.cpp"


inline Phys_mem_addr::Value
Kmem_alloc::to_phys(void *v)
{
  return Mem_layout::pmem_to_phys(v);
}

#line 321 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kmem_alloc.cpp"


inline Kmem_alloc_reaper::Kmem_alloc_reaper(size_t (*reap)(bool desperate))
  : _reap(reap)
{
  mem_reapers.add(this, mp_cas<cxx::S_list_item*>);
}

#endif // kmem_alloc_h
