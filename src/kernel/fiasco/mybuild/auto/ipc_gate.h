// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef ipc_gate_h
#define ipc_gate_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"

#include "kobject.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"
#include "kobject_helper.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"
#include "slab_cache.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"
#include "thread_object.h"
#line 51 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"

#include "tb_entry.h"

//
// INTERFACE definition follows 
//

#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"

class Ram_quota;
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"

class Ipc_gate_obj;
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"

class Ipc_gate_ctl : public Kobject_h<Ipc_gate_ctl, Kobject_iface>
{
private:
  enum Operation
  {
    Op_bind     = 0x10,
    Op_get_info = 0x11,
  };

public:  
#line 267 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  void
  invoke(L4_obj_ref self, L4_fpage::Rights rights, Syscall_frame *f, Utcb *utcb);
  
#line 278 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  L4_msg_tag
  kinvoke(L4_obj_ref self, L4_fpage::Rights rights,
                        Syscall_frame *f, Utcb const *in, Utcb *out);

private:  
#line 208 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  inline L4_msg_tag
  bind_thread(L4_obj_ref, L4_fpage::Rights,
                            Syscall_frame *f, Utcb const *in, Utcb *);
  
#line 257 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  inline L4_msg_tag
  get_infos(L4_obj_ref, L4_fpage::Rights,
                          Syscall_frame *, Utcb const *, Utcb *out);
};
#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"

class Ipc_gate : public cxx::Dyn_castable<Ipc_gate, Kobject>
{
  friend class Ipc_gate_ctl;
  friend class Jdb_sender_list;
protected:

  Thread *_thread;
  Mword _id;
  Ram_quota *_quota;
  Locked_prio_list _wait_q;

#line 53 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"
private:

protected:
  struct Log_ipc_gate_invoke : public Tb_entry
  {
    Mword gate_dbg_id;
    Mword thread_dbg_id;
    Mword label;
    void print(String_buffer *buf) const;
  };


public:  
#line 102 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  inline Ipc_gate(Ram_quota *q, Thread *t, Mword id);
  
#line 180 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  static Ipc_gate_obj *
  create(Ram_quota *q, Thread *t, Mword id);
  
#line 346 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  void
  invoke(L4_obj_ref /*self*/, L4_fpage::Rights rights, Syscall_frame *f, Utcb *utcb);

private:  
#line 302 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  inline L4_error
  block(Thread *ct, L4_timeout const &to, Utcb *u);
};
#line 33 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"

class Ipc_gate_obj :
  public cxx::Dyn_castable<Ipc_gate_obj, Ipc_gate, Ipc_gate_ctl>
{
  friend class Ipc_gate;
  typedef Slab_cache Self_alloc;

public:
  bool put() { return Ipc_gate::put(); }

  Thread *thread() const { return _thread; }
  Mword id() const { return _id; }
  Mword obj_id() const { return _id; }
  bool is_local(Space *s) const { return _thread && _thread->space() == s; }

public:  
#line 87 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  ::Kobject_mappable *
  map_root();
  
#line 92 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  Kobject_iface *
  downgrade(unsigned long attr);
  
#line 113 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  inline Ipc_gate_obj(Ram_quota *q, Thread *t, Mword id);
  
#line 118 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  void
  unblock_all();
  
#line 138 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  virtual void
  initiate_deletion(Kobject ***r);
  
#line 148 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  virtual void
  destroy(Kobject ***r);
  
#line 162 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  ~Ipc_gate_obj();
  
#line 168 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  inline void *
  operator new (size_t, void *b) throw();
  
#line 197 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  void operator delete (void *_f);
  
#line 438 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  ::Kobject_dbg *
  dbg_info() const;

private:  
#line 175 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"
  static Ipc_gate_obj::Self_alloc *
  allocator();
};
#line 48 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"

//---------------------------------------------------------------------------

#line 66 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"

//---------------------------------------------------------------------------

#line 441 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 69 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"

#include <cstddef>
#line 71 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"

#include "assert_opt.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 100 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"


inline Ipc_gate::Ipc_gate(Ram_quota *q, Thread *t, Mword id)
  : _thread(0), _id(id), _quota(q), _wait_q()
{
  if (t)
    {
      t->inc_ref();
      _thread = t;
    }
}

#line 111 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"


inline Ipc_gate_obj::Ipc_gate_obj(Ram_quota *q, Thread *t, Mword id)
  : Dyn_castable_class(q, t, id)
{}

#line 166 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ipc_gate.cpp"


inline void *
Ipc_gate_obj::operator new (size_t, void *b) throw()
{ return b; }

#endif // ipc_gate_h
