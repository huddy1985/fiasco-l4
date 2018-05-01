// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "kobject_dbg.h"
#include "kobject_dbg_i.h"

#line 1 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
//----------------------------------------------------------------------------

#line 77 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"

Spin_lock<> Kobject_dbg::_kobjects_lock;
#line 79 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
Kobject_dbg::Kobject_list Kobject_dbg::_kobjects INIT_PRIORITY(101);
#line 80 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
unsigned long Kobject_dbg::_next_dbg_id;

#line 83 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"


Kobject_dbg::Iterator
Kobject_dbg::pointer_to_obj(void const *p)
{
  for (Iterator l = _kobjects.begin(); l != _kobjects.end(); ++l)
    {
      auto ti = l->_cxx_dyn_type();
      Mword a = (Mword)ti.base;
      if (a <= Mword(p) && Mword(p) < (a + ti.type->size))
        return l;
    }
  return _kobjects.end();
}

#line 97 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"


unsigned long
Kobject_dbg::pointer_to_id(void const *p)
{
  Iterator o = pointer_to_obj(p);
  if (o != _kobjects.end())
    return o->dbg_id();
  return ~0UL;
}

#line 107 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"


bool
Kobject_dbg::is_kobj(void const *o)
{
  return pointer_to_obj(o) != _kobjects.end();
}

#line 114 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"


Kobject_dbg::Iterator
Kobject_dbg::id_to_obj(unsigned long id)
{
  for (Iterator l = _kobjects.begin(); l != _kobjects.end(); ++l)
    {
      if (l->dbg_id() == id)
	return l;
    }
  return end();
}

#line 126 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"


unsigned long
Kobject_dbg::obj_to_id(void const *o)
{
  return pointer_to_id(o);
}

#line 133 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"



Kobject_dbg::Kobject_dbg()
{
  auto guard = lock_guard(_kobjects_lock);

  _dbg_id = _next_dbg_id++;
  _kobjects.push_back(this);
}
