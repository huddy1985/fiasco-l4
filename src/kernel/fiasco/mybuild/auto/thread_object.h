// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef thread_object_h
#define thread_object_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"

#include "kobject.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
#include "thread.h"

//
// INTERFACE definition follows 
//

#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"

class Thread_object : public Thread
{
private:
  struct Remote_syscall
  {
    Thread *thread;
    L4_msg_tag result;
  };

public:  
#line 72 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
  explicit Thread_object(Ram_quota *q);
  
#line 75 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
  explicit Thread_object(Ram_quota *q, Context_mode_kernel k);
  
#line 79 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
  virtual bool
  put();
  
#line 86 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
  void
  operator delete(void *_t);
  
#line 102 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
  void
  destroy(Kobject ***rl);
  
#line 112 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
  void
  invoke(L4_obj_ref /*self*/, L4_fpage::Rights rights, Syscall_frame *f, Utcb *utcb);
  
#line 508 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
  // -------------------------------------------------------------------
  // Thread::ex_regs class system calls
  
  
  bool
  ex_regs(Address ip, Address sp,
                  Address *o_ip = 0, Address *o_sp = 0, Mword *o_flags = 0,
                  Mword ops = 0);

private:  
#line 171 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
  inline L4_msg_tag
  sys_vcpu_resume(L4_msg_tag const &tag, Utcb *utcb);
  
#line 299 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
  inline L4_msg_tag
  sys_modify_senders(L4_msg_tag tag, Utcb const *in, Utcb * /*out*/);
  
#line 342 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
  inline L4_msg_tag
  sys_register_delete_irq(L4_msg_tag tag, Utcb const *in, Utcb * /*out*/);
  
#line 372 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
  inline L4_msg_tag
  sys_control(L4_fpage::Rights rights, L4_msg_tag tag, Utcb *utcb);
  
#line 451 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
  inline L4_msg_tag
  sys_vcpu_control(L4_fpage::Rights, L4_msg_tag const &tag,
                                  Utcb *utcb);
  
#line 563 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
  inline L4_msg_tag
  ex_regs(Utcb *utcb);
  
#line 586 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
  static Context::Drq::Result
  handle_remote_ex_regs(Drq *, Context *self, void *p);
  
#line 595 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
  inline L4_msg_tag
  sys_ex_regs(L4_msg_tag const &tag, Utcb *utcb);
  
#line 612 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
  inline L4_msg_tag
  sys_thread_switch(L4_msg_tag const &/*tag*/, Utcb *utcb);
  
#line 650 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
  // -------------------------------------------------------------------
  // Gather statistics information about thread execution
  
  
  inline Context::Drq::Result
  sys_thread_stats_remote(void *data);
  
#line 663 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
  static Context::Drq::Result FIASCO_FLATTEN
  handle_sys_thread_stats_remote(Drq *, Context *self, void *data);
  
#line 670 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
  inline L4_msg_tag
  sys_thread_stats(L4_msg_tag const &/*tag*/, Utcb *utcb);
};
#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"

class Obj_cap : public L4_obj_ref
{

public:  
#line 36 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
  inline Obj_cap(L4_obj_ref const &o);
  
#line 39 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
  inline Kobject_iface *
  deref(L4_fpage::Rights *rights = 0, bool dbg = false);
  
#line 65 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
  inline bool
  revalidate(Kobject_iface *o);
};
#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"


// ---------------------------------------------------------------------------


//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 28 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
#include "processor.h"
#line 31 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"
#include "timer.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 32 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"




inline Obj_cap::Obj_cap(L4_obj_ref const &o) : L4_obj_ref(o) {}

#line 37 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"


inline Kobject_iface *
Obj_cap::deref(L4_fpage::Rights *rights, bool dbg)
{
  Thread *current = current_thread();
  if (op() & L4_obj_ref::Ipc_reply)
    {
      if (rights) *rights = current->caller_rights();
      Thread *ca = static_cast<Thread*>(current->caller());
      if (EXPECT_TRUE(!dbg && ca))
        current->reset_caller();
      return ca;
    }

  if (EXPECT_FALSE(special()))
    {
      if (!self())
	return 0;

      if (rights) *rights = L4_fpage::Rights::RWX();
      return current;
    }

  return current->space()->lookup_local(cap(), rights);
}

#line 63 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/thread_object.cpp"


inline bool
Obj_cap::revalidate(Kobject_iface *o)
{
  return deref() == o;
}

#endif // thread_object_h
