// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "paranoia.h"
#include "paranoia_i.h"

#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/cxxlib/paranoia.cpp"

char __dso_handle __attribute__((weak));

#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/cxxlib/paranoia.cpp"

extern "C" void __cxa_pure_virtual() 
{
  panic("cxa pure virtual function called");
}

#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/cxxlib/paranoia.cpp"

extern "C" void __pure_virtual()
{
  panic("pure virtual function called");
}

#line 23 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/cxxlib/paranoia.cpp"

void operator delete(void *) throw()
{
  // This must not happen: We never delete an object of the abstract
  // class slab_cache_anon.  If the compiler was clever, it wouldn't
  // generate a call to this function (because all destructors of
  // abstract base classes have been marked abstract virtual), and
  // we wouldn't need to define this.
  panic("operator delete (aka __builtin_delete) called from " L4_PTR_FMT,
      L4_PTR_ARG(__builtin_return_address(0)));
}

#line 34 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/cxxlib/paranoia.cpp"

extern "C" void __div0(void)
{
  panic("__div0");
}
