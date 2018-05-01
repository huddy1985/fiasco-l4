// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef boot_alloc_h
#define boot_alloc_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/boot_alloc.cpp"

#include <cstddef>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/boot_alloc.cpp"
#include <cxx/slist>
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/boot_alloc.cpp"
#include <cxx/type_traits>

//
// INTERFACE definition follows 
//

#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/boot_alloc.cpp"

class Boot_alloced
{
private:
  enum { Debug_boot_alloc };
  struct Block : cxx::S_list_item
  { size_t size; };

  typedef cxx::S_list_bss<Block> Block_list;

  static Block_list _free;

public:  
#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/boot_alloc.cpp"
  static void *
  alloc(size_t size);
  
#line 100 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/boot_alloc.cpp"
  template<typename T> static T *
  allocate(size_t count = 1);
  
#line 106 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/boot_alloc.cpp"
  inline void *
  operator new (size_t size) throw();
  
#line 110 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/boot_alloc.cpp"
  inline void *
  operator new[] (size_t size) throw();
  
#line 114 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/boot_alloc.cpp"
  void
  operator delete (void *b);
  
#line 120 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/boot_alloc.cpp"
  void
  operator delete[] (void *b);
};
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/boot_alloc.cpp"

template< typename Base >
class Boot_object : public Base, public Boot_alloced
{
public:
  Boot_object()  = default;

  template< typename... A >
  Boot_object(A&&... args) : Base(cxx::forward<A>(args)...) {}
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 31 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/boot_alloc.cpp"

#include <cstdio>
#line 33 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/boot_alloc.cpp"
#include <cstring>
#line 34 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/boot_alloc.cpp"

#include "kmem_alloc.h"
#line 36 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/boot_alloc.cpp"
#include "warn.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 105 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/boot_alloc.cpp"

inline void *
Boot_alloced::operator new (size_t size) throw()
{ return alloc(size); }

#line 109 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/boot_alloc.cpp"

inline void *
Boot_alloced::operator new[] (size_t size) throw()
{ return alloc(size); }

//
// IMPLEMENTATION of function templates
//


#line 98 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/boot_alloc.cpp"

 
template<typename T> T *
Boot_alloced::allocate(size_t count)
{
  return reinterpret_cast<T *>(alloc(count * sizeof(T)));
}

#endif // boot_alloc_h
