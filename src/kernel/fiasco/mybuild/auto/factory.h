// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef factory_h
#define factory_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/factory.cpp"

#include "fiasco_defs.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/factory.cpp"
#include "ram_quota.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/factory.cpp"
#include "slab_cache.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/factory.cpp"
#include "kobject_helper.h"
#line 191 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/factory.cpp"

#include "tb_entry.h"

//
// INTERFACE definition follows 
//

#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/factory.cpp"

class Factory : public Ram_quota, public Kobject_h<Factory>
{
  typedef Slab_cache Self_alloc;

#line 193 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/factory.cpp"
private:

private:
  struct Log_entry : public Tb_entry
  {
    Smword op;
    Cap_index buffer;
    Mword id;
    Mword ram;
    Mword newo;
    void print(String_buffer *buf) const;
  };

public:  
#line 31 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/factory.cpp"
  inline Factory();
  
#line 49 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/factory.cpp"
  static inline Factory * FIASCO_PURE
  root();
  
#line 55 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/factory.cpp"
  inline Factory *
  create_factory(unsigned long max);
  
#line 71 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/factory.cpp"
  void operator delete (void *_f);
  
#line 117 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/factory.cpp"
  L4_msg_tag
  kinvoke(L4_obj_ref ref, L4_fpage::Rights rights, Syscall_frame *f,
                   Utcb const *utcb, Utcb *);

private:  
#line 36 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/factory.cpp"
  inline Factory(Ram_quota *q, unsigned long max);
  
#line 44 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/factory.cpp"
  static Factory::Self_alloc *
  allocator();
  
#line 87 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/factory.cpp"
  L4_msg_tag
  map_obj(Kobject_iface *o, Cap_index cap, Task *_c_space,
                   Obj_space *o_space, Utcb const *utcb);
};
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/factory.cpp"

//---------------------------------------------------------------------------

#line 207 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/factory.cpp"

// ------------------------------------------------------------------------

#line 212 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/factory.cpp"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 29 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/factory.cpp"


inline Factory::Factory()
  : Ram_quota()
{}

#line 47 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/factory.cpp"


inline Factory * FIASCO_PURE
Factory::root()
{ return nonull_static_cast<Factory*>(Ram_quota::root); }

#line 34 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/factory.cpp"


inline Factory::Factory(Ram_quota *q, unsigned long max)
  : Ram_quota(q, max)
{}

#line 52 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/factory.cpp"



inline Factory *
Factory::create_factory(unsigned long max)
{
  Auto_quota<Ram_quota> q(this, sizeof(Factory) + max);
  if (EXPECT_FALSE(!q))
    return 0;

  void *nq = allocator()->alloc();
  if (EXPECT_FALSE(!nq))
    return 0;

  q.release();
  return new (nq) Factory(this, max);
}

#endif // factory_h
