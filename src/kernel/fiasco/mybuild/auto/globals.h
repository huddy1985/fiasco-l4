// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef globals_h
#define globals_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/globals.cpp"

#include <cassert>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/globals.cpp"

#include "panic.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/globals.cpp"
#include "per_cpu_data.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/globals.cpp"
#include "types.h"

//
// INTERFACE definition follows 
//

#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/globals.cpp"

class Timeout;
#line 22 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/globals.cpp"

class Kobject_iface;
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/globals.cpp"

extern Per_cpu<Timeout *> timeslice_timeout;
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/globals.cpp"

/* the check macro is like assert(), but it evaluates its argument
   even if NDEBUG is defined */
#ifndef check
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/globals.cpp"
#ifdef NDEBUG
#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/globals.cpp"
# define check(expression) ((void)(expression))
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/globals.cpp"
#else /* ! NDEBUG */
#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/globals.cpp"
# define check(expression) assert(expression)
#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/globals.cpp"
#endif /* NDEBUG */
#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/globals.cpp"
#endif /* check */
#line 24 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/globals.cpp"

class Initial_kobjects
{
public:
  enum Initial_cap
  {
    Task      =  1,
    Factory   =  2,
    Thread    =  3,
    Pager     =  4,
    Log       =  5,
    Icu       =  6,
    Scheduler =  7,
    Iommu     =  8,
    Jdb       = 10,

    First_alloc_cap = Log,
    Num_alloc       = 6,
    End_alloc_cap   = First_alloc_cap + Num_alloc,
  };

  static Cap_index first() { return Cap_index(First_alloc_cap); }
  static Cap_index end() { return Cap_index(End_alloc_cap); }

  void register_obj(Kobject_iface *o, Initial_cap cap)
  {
    assert (cap >= First_alloc_cap);
    assert (cap < End_alloc_cap);

    int c = cap - First_alloc_cap;

    assert (!_v[c]);

    _v[c] = o;
  }

  Kobject_iface *obj(Cap_index cap) const
  {
    assert (cap >= first());
    assert (cap < end());

    return _v[cxx::int_value<Cap_diff>(cap - first())];
  }

private:
  Kobject_iface *_v[Num_alloc];
};
#line 71 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/globals.cpp"


extern Initial_kobjects initial_kobjects;
#line 74 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/globals.cpp"


//---------------------------------------------------------------------------


#endif // globals_h
