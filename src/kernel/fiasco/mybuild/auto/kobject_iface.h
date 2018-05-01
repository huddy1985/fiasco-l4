// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kobject_iface_h
#define kobject_iface_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"

#include "l4_types.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"
#include <cxx/dyn_cast>

//
// INTERFACE definition follows 
//

#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"

class Kobject;
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"
class Kobject_dbg;
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"
class Kobject_mappable;
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"

class Space;
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"
class Ram_quota;
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"
class Syscall_frame;
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"
class Utcb;
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"

class Kobject_common : public cxx::Dyn_castable<Kobject_common>
{
public:
  Kobject_common() = default;
  Kobject_common(Kobject_common const &) = delete;
  Kobject_common &operator = (Kobject_common const &) = delete;

  virtual bool is_local(Space *) const  = 0;
  virtual Mword obj_id() const  = 0;
  virtual void initiate_deletion(Kobject ***) = 0;

  virtual Kobject_mappable *map_root() = 0;
  virtual ~Kobject_common() = 0;

public:  
#line 105 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"
  virtual Kobject_dbg *dbg_info() const = 0;
};
#line 29 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"

class Kobject_iface : public cxx::Dyn_castable<Kobject_iface, Kobject_common>
{
public:
  virtual void invoke(L4_obj_ref self, L4_fpage::Rights rights, Syscall_frame *, Utcb *) = 0;

  typedef Kobject_iface *Factory_func(Ram_quota *q,
                                      Space *current_space,
                                      L4_msg_tag tag,
                                      Utcb const *utcb, int *err);
  enum { Max_factory_index = -L4_msg_tag::Max_factory_label };
  static Factory_func *factory[Max_factory_index + 1];

public:  
#line 52 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"
  static inline L4_msg_tag
  commit_result(Mword error,
                               unsigned words = 0, unsigned items = 0);
  
#line 60 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"
  static inline L4_msg_tag
  commit_error(Utcb const *utcb, L4_error const &e,
                              L4_msg_tag const &tag = L4_msg_tag(0, 0, 0, 0));
  
#line 69 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"
  virtual Kobject_iface *
  downgrade(unsigned long del_attribs);
  
#line 74 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"
  static void
  set_factory(long label, Factory_func *f);
  
#line 89 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"
  static inline Kobject_iface *
  manufacture(long label, Ram_quota *q,
                             Space *current_space,
                             L4_msg_tag tag, Utcb const *utcb, int *err);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 46 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"

inline Kobject_common::~Kobject_common() {}

#line 50 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"


inline L4_msg_tag
Kobject_iface::commit_result(Mword error,
                             unsigned words, unsigned items)
{
  return L4_msg_tag(words, items, 0, error);
}

#line 58 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"


inline L4_msg_tag
Kobject_iface::commit_error(Utcb const *utcb, L4_error const &e,
                            L4_msg_tag const &tag)
{
  const_cast<Utcb*>(utcb)->error = e;
  return L4_msg_tag(tag, L4_msg_tag::Error);
}

#line 87 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_iface.cpp"


inline Kobject_iface *
Kobject_iface::manufacture(long label, Ram_quota *q,
                           Space *current_space,
                           L4_msg_tag tag, Utcb const *utcb, int *err)
{
  *err = L4_err::ENodev;
  if (EXPECT_FALSE(label > 0 || -label > Max_factory_index
                   || !factory[-label]))
    return 0;

  return factory[-label](q, current_space, tag, utcb, err);
}

#endif // kobject_iface_h
