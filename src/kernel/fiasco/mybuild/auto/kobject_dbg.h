// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kobject_dbg_h
#define kobject_dbg_h
#line 3 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"

#include "spin_lock.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
#include "lock_guard.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
#include <cxx/dlist>
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
#include <cxx/hlist>
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
#include <cxx/dyn_cast>

//
// INTERFACE definition follows 
//

#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"

struct Kobject_typeinfo_name
{
  cxx::Type_info const *type;
  char const *name;
};
#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"

#define JDB_DEFINE_TYPENAME(type, name) \
  static __attribute__((used, section(".debug.jdb.typeinfo_table"))) \
  Kobject_typeinfo_name const typeinfo_name__ ## type ## __entry =   \
    { cxx::Typeid<type>::get(), name }
#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"

class Kobject_dbg : public cxx::D_list_item
{
  friend class Jdb_kobject;
  friend class Jdb_kobject_list;
  friend class Jdb_mapdb;

public:
  class Dbg_extension : public cxx::H_list_item
  {
  public:
    virtual ~Dbg_extension() = 0;
  };

public:
  typedef cxx::H_list<Dbg_extension> Dbg_ext_list;
  Dbg_ext_list _jdb_data;

private:
  Mword _dbg_id;

public:
  Mword dbg_id() const { return _dbg_id; }

  virtual cxx::_dyn::Type _cxx_dyn_type() const = 0;
  virtual ~Kobject_dbg() = 0;


  typedef cxx::D_list<Kobject_dbg> Kobject_list;
  typedef Kobject_list::Iterator Iterator;
  typedef Kobject_list::Const_iterator Const_iterator;

  static Spin_lock<> _kobjects_lock;
  static Kobject_list _kobjects;

  static Iterator begin() { return _kobjects.begin(); }
  static Iterator end() { return _kobjects.end(); }

private:
  static unsigned long _next_dbg_id;

public:  
#line 85 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
  static Kobject_dbg::Iterator
  pointer_to_obj(void const *p);
  
#line 99 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
  static unsigned long
  pointer_to_id(void const *p);
  
#line 109 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
  static bool
  is_kobj(void const *o);
  
#line 116 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
  static Kobject_dbg::Iterator
  id_to_obj(unsigned long id);
  
#line 128 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
  static unsigned long
  obj_to_id(void const *o);

protected:  
#line 136 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"
  Kobject_dbg();
};
#line 81 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 143 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"


inline Kobject_dbg::~Kobject_dbg()
{
    {
      auto guard = lock_guard(_kobjects_lock);
      _kobjects.remove(this);
    }

  while (Dbg_extension *ex = _jdb_data.front())
    delete ex;
}

#line 81 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_dbg.cpp"

inline Kobject_dbg::Dbg_extension::~Dbg_extension() {}

#endif // kobject_dbg_h
