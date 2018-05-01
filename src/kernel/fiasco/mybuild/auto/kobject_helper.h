// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kobject_helper_h
#define kobject_helper_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_helper.cpp"

#include "kobject.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_helper.cpp"
#include "thread.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_helper.cpp"
#include <cxx/type_traits>

//
// INTERFACE definition follows 
//

#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_helper.cpp"

template<typename T, typename Base = Kobject> class Kobject_h;
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_helper.cpp"

class Kobject_helper_base
{
  template<typename T, typename Base> friend class Kobject_h;
protected:
  static Mword _utcb_dummy[];
  static Utcb *utcb_dummy()
  {
    char *x = reinterpret_cast<char*>(&_utcb_dummy);
    return reinterpret_cast<Utcb*>(x);
  }

};
#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kobject_helper.cpp"

template<typename T, typename Base>
class Kobject_h : public cxx::Dyn_castable<T, Base>
{
private:
  static Sender *_sender(Thread *, Sender *t) { return t; }
  static Sender *_sender(Thread *ct, ...) { return ct; }

protected:
  static L4_msg_tag no_reply() { return L4_msg_tag(L4_msg_tag::Schedule); }
  static bool have_receive(Utcb *rcv) { return rcv != Kobject_helper_base::utcb_dummy(); }

public:
  Kobject_h() = default;

  template< typename... A >
  explicit Kobject_h(A&&... args)
  : cxx::Dyn_castable<T, Base>(cxx::forward<A>(args)...)
  {}

  void invoke(L4_obj_ref self, L4_fpage::Rights rights, Syscall_frame *f, Utcb *u)
  {
    L4_msg_tag res(no_reply());
    if (EXPECT_TRUE(self.op() & L4_obj_ref::Ipc_send))
      res = static_cast<T*>(this)->T::kinvoke(self, rights, f, (Utcb const *)u,
                                              self.have_recv() ? u : Kobject_helper_base::utcb_dummy());

    if (EXPECT_FALSE(res.has_error()))
      {
        f->tag(res);
        return;
      }

    if (self.have_recv())
      {
        if (!res.do_switch())
          {
            Thread *t = current_thread();
            Sender *s = (self.op() & L4_obj_ref::Ipc_open_wait) ? 0 : _sender(t, static_cast<T*>(this));
            t->do_ipc(f->tag(), 0, 0, true, s, f->timeout(), f, rights);
            return;
          }
        else
          f->tag(res);
      }
  }

};

#endif // kobject_helper_h
