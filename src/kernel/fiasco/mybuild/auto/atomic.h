// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef atomic_h
#define atomic_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"

#include "types.h"

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"

extern "C" void cas_error_type_with_bad_size_used(void);
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"

#define MACRO_CAS_ASSERT(rs, cs) \
  if ((rs) != (cs)) \
    cas_error_type_with_bad_size_used()
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"


template< typename A, typename B >
struct Pair
{
  A first;
  B second;

  Pair() {}
  Pair(A const &a, B const &b) : first(a), second(b) {}
};
#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"


//---------------------------------------------------------------------------


#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"
template< typename Type > inline bool
cas(Type *ptr, Type oldval, Type newval);

#line 37 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"
template <typename T> inline T
atomic_change(T *ptr, T mask, T bits);

#line 53 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"
inline void
atomic_mp_and(Mword *l, Mword value);

#line 60 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"
inline void
atomic_mp_or(Mword *l, Mword value);

#line 68 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"
inline void
atomic_mp_add(Mword *l, Mword value);

#line 75 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"
inline void
atomic_add(Mword *l, Mword value);

#line 82 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"
inline void
atomic_and(Mword *l, Mword mask);

#line 89 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"
inline void
atomic_or(Mword *l, Mword bits);

#line 95 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"
// ``unsafe'' stands for no safety according to the size of the given type.
// There are type safe versions of the cas operations in the architecture
// independent part of atomic that use the unsafe versions and make a type
// check.


inline bool
cas_unsafe(Mword *ptr, Mword oldval, Mword newval);

#line 117 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"
inline bool
mp_cas_arch(Mword *m, Mword o, Mword n);

#line 180 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"
template< typename T > inline bool
mp_cas(T *m, T o, T n);

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 25 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"

 
template< typename Type > inline bool
cas(Type *ptr, Type oldval, Type newval)
{
  MACRO_CAS_ASSERT(sizeof(Type), sizeof(Mword));
  return cas_unsafe(reinterpret_cast<Mword *>(ptr),
                    (Mword)oldval, (Mword)newval);
}

#line 34 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"


 
template <typename T> inline T
atomic_change(T *ptr, T mask, T bits)
{
  T old;
  do
    {
      old = *ptr;
    }
  while (!cas(ptr, old, (old & mask) | bits));
  return old;
}

#line 51 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"


inline void
atomic_mp_and(Mword *l, Mword value)
{
  asm volatile ("lock; andl %1, %2" : "=m"(*l) : "ir"(value), "m"(*l));
}

#line 58 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"


inline void
atomic_mp_or(Mword *l, Mword value)
{
  asm volatile ("lock; orl %1, %2" : "=m"(*l) : "ir"(value), "m"(*l));
}

#line 65 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"



inline void
atomic_mp_add(Mword *l, Mword value)
{
  asm volatile ("lock; addl %1, %2" : "=m"(*l) : "ir"(value), "m"(*l));
}

#line 73 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"


inline void
atomic_add(Mword *l, Mword value)
{
  asm volatile ("addl %1, %2" : "=m"(*l) : "ir"(value), "m"(*l));
}

#line 80 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"


inline void
atomic_and(Mword *l, Mword mask)
{
  asm volatile ("andl %1, %2" : "=m"(*l) : "ir"(mask), "m"(*l));
}

#line 87 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"


inline void
atomic_or(Mword *l, Mword bits)
{
  asm volatile ("orl %1, %2" : "=m"(*l) : "ir"(bits), "m"(*l));
}

#line 94 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"

// ``unsafe'' stands for no safety according to the size of the given type.
// There are type safe versions of the cas operations in the architecture
// independent part of atomic that use the unsafe versions and make a type
// check.


inline bool
cas_unsafe(Mword *ptr, Mword oldval, Mword newval)
{
  Mword tmp;

  asm volatile
    ("cmpxchgl %1, %2"
     : "=a" (tmp)
     : "r" (newval), "m" (*ptr), "a" (oldval)
     : "memory");

  return tmp == oldval;
}

#line 114 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"



inline bool
mp_cas_arch(Mword *m, Mword o, Mword n)
{
  Mword tmp;

  asm volatile
    ("lock; cmpxchgl %1, %2"
     : "=a" (tmp)
     : "r" (n), "m" (*m), "a" (o)
     : "memory");

  return tmp == o;
}

#line 178 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/atomic.cpp"

 
template< typename T > inline bool
mp_cas(T *m, T o, T n)
{ return cas(m,o,n); }

#endif // atomic_h
