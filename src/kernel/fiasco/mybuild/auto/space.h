// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef space_h
#define space_h
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"

#include "config.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"
#include "io_space.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"
#include "l4_types.h"
#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"

#include "mem_space.h"
#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"
#include "member_offs.h"
#line 22 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"
#include "obj_space.h"
#line 23 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"
#include "spin_lock.h"
#line 24 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"
#include "ref_obj.h"
#line 25 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"
#include "slab_cache.h"
#line 26 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"
#include <cxx/slist>
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space-io.cpp"

#include "config.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space-io.cpp"
#include "io_space.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space-io.cpp"
#include "l4_types.h"

//
// INTERFACE definition follows 
//

#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"

class Space;
#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"

class Ram_quota;
#line 29 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"
class Context;
#line 30 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"
class Kobject;
#line 31 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"

class Space;
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"

/** Global definition of Io_space for map_util stuff. */
typedef Generic_io_space<Space> Io_space;
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"

//--------------------------------------------------------------------------

#line 33 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"

typedef Generic_obj_space<Space> Obj_space;
#line 35 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"

class Space
: public Ref_cnt_obj,
  public Mem_space,
  public Generic_obj_space<Space>

, public Generic_io_space<Space>
{
  MEMBER_OFFSET();
  friend class Jdb_space;

public:

  struct Caps
  : cxx::int_type_base<unsigned char, Caps>,
    cxx::int_bit_ops<Caps>,
    cxx::int_null_chk<Caps>
  {
    Caps() = default;
    explicit constexpr Caps(unsigned char v)
    : cxx::int_type_base<unsigned char, Caps>(v) {}

    static constexpr Caps none() { return Caps(0); }
    static constexpr Caps mem() { return Caps(1); }
    static constexpr Caps obj() { return Caps(2); }
    static constexpr Caps io() { return Caps(4); }
    static constexpr Caps threads() { return Caps(8); }
    static constexpr Caps all() { return Caps(0xf); }
  };

  explicit Space(Ram_quota *q, Caps c) : Mem_space(q), _caps(c) {}
  virtual ~Space() = 0;

  enum State
  { // we must use values with the two lest significant bits == 0
    Starting    = 0x00,
    Ready       = 0x08,
    In_deletion = 0x10
  };

  struct Ku_mem : public cxx::S_list_item
  {
    User<void>::Ptr u_addr;
    void *k_addr;
    unsigned size;

    static Slab_cache *a;

    void *operator new (size_t, Ram_quota *q) throw()
    { return a->q_alloc(q); }

    void free(Ram_quota *q) throw()
    { a->q_free(q, this); }

    template<typename T>
    T *kern_addr(Smart_ptr<T, Simple_ptr_policy, User_ptr_discr> ua) const
    {
      typedef Address A;
      return (T*)((A)ua.get() - (A)u_addr.get() + (A)k_addr);
    }
  };

  Caps caps() const { return _caps; }

  void switchin_context(Space *from);

protected:
  Space(Ram_quota *q, Mem_space::Dir_type* pdir, Caps c)
  : Mem_space(q, pdir), _caps(c) {}

  const Caps _caps;

protected:
  typedef cxx::S_list<Ku_mem> Ku_mem_list;
  Ku_mem_list _ku_mem;

#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space-io.cpp"
private:

public:  
#line 121 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"
  //
  // class Space
  //
  
  inline Ram_quota * ram_quota() const;
  
#line 131 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"
  Space::Ku_mem const *
  find_ku_mem(User<void>::Ptr p, unsigned size);
  
#line 163 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"
  static inline bool
  is_user_memory(Address address, Mword len);
};
#line 109 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"


//---------------------------------------------------------------------------


//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 120 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"

//
// class Space
//

inline Ram_quota * Space::ram_quota() const
{ return Mem_space::ram_quota(); }

#line 160 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"



inline bool
Space::is_user_memory(Address address, Mword len)
{
  return    address <= Mem_layout::User_max && len > 0
         && Mem_layout::User_max - address >= len - 1;
}

#line 127 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"

inline Space::~Space() {}

#line 153 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/space.cpp"


inline void
Space::switchin_context(Space *from)
{
  Mem_space::switchin_context(from);
}

#endif // space_h
