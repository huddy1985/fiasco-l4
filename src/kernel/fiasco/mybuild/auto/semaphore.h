// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef semaphore_h
#define semaphore_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/semaphore.cpp"

#include <limits.h>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/semaphore.cpp"
#include "irq.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/semaphore.cpp"
#include "kobject_helper.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/semaphore.cpp"
#include "prio_list.h"

//
// INTERFACE definition follows 
//

#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/semaphore.cpp"

class Semaphore : public Kobject_h<Semaphore, Irq>
{
public:
  friend class Jdb_kobject_irq;
  enum Op {
    Op_down = 0
  };

protected:
  Smword _queued;
  Locked_prio_list _waiting;

public:  
#line 29 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/semaphore.cpp"
  explicit Semaphore(Ram_quota *q = 0);
  
#line 107 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/semaphore.cpp"
  void
  switch_mode(bool is_edge_triggered);
  
#line 114 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/semaphore.cpp"
  static inline Sender *
  sem_partner();
  
#line 194 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/semaphore.cpp"
  L4_msg_tag
  kinvoke(L4_obj_ref, L4_fpage::Rights /*rights*/, Syscall_frame *f,
                     Utcb const *utcb, Utcb *);

private:  
#line 37 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/semaphore.cpp"
  inline Smword
  count_up(Thread **wakeup);
  
#line 61 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/semaphore.cpp"
  inline void ALWAYS_INLINE
  _hit_edge_irq(Upstream_irq const *ui);
  
#line 82 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/semaphore.cpp"
  static void
  hit_edge_irq(Irq_base *i, Upstream_irq const *ui);
  
#line 87 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/semaphore.cpp"
  inline void ALWAYS_INLINE
  _hit_level_irq(Upstream_irq const *ui);
  
#line 101 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/semaphore.cpp"
  static void
  hit_level_irq(Irq_base *i, Upstream_irq const *ui);
  
#line 119 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/semaphore.cpp"
  inline bool ALWAYS_INLINE
  down(Thread *ct);
  
#line 148 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/semaphore.cpp"
  inline L4_msg_tag ALWAYS_INLINE
  sys_down(L4_timeout t, Utcb const *utcb);
};
#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/semaphore.cpp"

//-----------------------------------------------------------------------------


//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 112 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/semaphore.cpp"


inline Sender *
Semaphore::sem_partner()
{ return reinterpret_cast<Sender *>(5); }

#endif // semaphore_h
