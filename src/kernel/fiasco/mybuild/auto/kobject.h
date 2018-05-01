// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kobject_h
#define kobject_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"

#include "lock.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"
#include "obj_space.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"
#include <cxx/hlist>
#line 40 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"

#include "context.h"
#line 42 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"
#include "kobject_dbg.h"
#line 43 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"
#include "kobject_iface.h"
#line 44 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"
#include "l4_error.h"
#line 45 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"
#include "rcupdate.h"
#line 46 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"
#include "space.h"
#line 219 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"

#include "tb_entry.h"

//
// INTERFACE definition follows 
//

#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"


class Kobject_mappable
{
private:
  friend class Kobject_mapdb;
  friend class Jdb_mapdb;

  Obj::Mapping::List _root;
  Smword _cnt;
  Lock _lock;

public:
  Kobject_mappable() : _cnt(0) {}
  bool no_mappings() const { return _root.empty(); }

  /**
   * Insert the root mapping of an object.
   */
  template<typename M>
  bool insert(void *, Space *, M &m)
  {
    m._c->put_as_root();
    _root.add(m._c);
    _cnt = 1;
    return true;
  }

  Smword cap_ref_cnt() const { return _cnt; }

public:  
#line 118 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"
  inline Smword
  dec_cap_refcnt(Smword diff);
};
#line 36 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"


//----------------------------------------------------------------------------

#line 47 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"

class Kobject :
  public cxx::Dyn_castable<Kobject, Kobject_iface>,
  private Kobject_mappable,
  private Kobject_dbg
{
  template<typename T>
  friend class Map_traits;

private:
  template<typename T>
  class Tconv {};

  template<typename T>
  class Tconv<T*> { public: typedef T Base; };

public:
  using Dyn_castable<Kobject, Kobject_iface>::_cxx_dyn_type;

  class Reap_list
  {
  private:
    Kobject *_h;
    Kobject **_t;

  public:
    Reap_list() : _h(0), _t(&_h) {}
    ~Reap_list() { del(); }
    Kobject ***list() { return &_t; }
    bool empty() const { return _h == nullptr; }
    void del_1();
    void del_2();
    void del()
    {
      if (EXPECT_TRUE(empty()))
        return;

      del_1();
      current()->rcu_wait();
      del_2();
    }
  };

  using Kobject_dbg::dbg_id;

  Lock existence_lock;

public:
  Kobject *_next_to_reap;

public:
  enum Op {
    O_dec_refcnt = 0,
  };


#line 221 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"
private:

protected:
  struct Log_destroy : public Tb_entry
  {
    Kobject    *obj;
    Mword       id;
    cxx::Type_info const *type;
    Mword       ram;
    void print(String_buffer *buf) const;
  };

public:  
#line 112 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"
  bool  is_local(Space *) const;
  
#line 113 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"
  Mword obj_id() const;
  
#line 114 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"
  virtual bool  put();
  
#line 115 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"
  inline Kobject_mappable *map_root();
  
#line 127 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"
  void
  initiate_deletion(Kobject ***reap_list);
  
#line 138 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"
  virtual void
  destroy(Kobject ***);
  
#line 149 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"
  virtual ~Kobject();
  
#line 171 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"
  L4_msg_tag
  kobject_invoke(L4_obj_ref, L4_fpage::Rights /*rights*/,
                          Syscall_frame *f,
                          Utcb const *in, Utcb *out);
  
#line 241 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"
  static inline Kobject *
  from_dbg(Kobject_dbg *d);
  
#line 246 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"
  static inline Kobject *
  from_dbg(Kobject_dbg::Iterator const &d);
  
#line 255 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"
  Kobject_dbg *
  dbg_info() const;

private:  
#line 159 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"
  inline L4_msg_tag
  sys_dec_refcnt(L4_msg_tag tag, Utcb const *in, Utcb *out);
};
#line 103 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"

//---------------------------------------------------------------------------

#line 190 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"
#line 234 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"

//---------------------------------------------------------------------------

#line 258 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 109 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"
#include "lock_guard.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 116 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"


inline Smword
Kobject_mappable::dec_cap_refcnt(Smword diff)
{
  auto g = lock_guard(_lock);
  _cnt -= diff;
  return _cnt;
}

#line 115 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"
inline Kobject_mappable *Kobject::map_root() { return this; }

#line 239 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"


inline Kobject *
Kobject::from_dbg(Kobject_dbg *d)
{ return static_cast<Kobject*>(d); }

#line 244 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"


inline Kobject *
Kobject::from_dbg(Kobject_dbg::Iterator const &d)
{
  if (d != Kobject_dbg::end())
    return static_cast<Kobject*>(*d);
  return 0;
}

#line 190 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"



inline void
Kobject::Reap_list::del_1()
{
  for (Kobject *reap = _h; reap; reap = reap->_next_to_reap)
    reap->destroy(list());
}

#line 199 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject.cpp"


inline void
Kobject::Reap_list::del_2()
{
  for (Kobject *reap = _h; reap;)
    {
      Kobject *d = reap;
      reap = reap->_next_to_reap;
      if (d->put())
        delete d;
    }

  _h = 0;
  _t = &_h;
}

#endif // kobject_h
