// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef scheduler_h
#define scheduler_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"

#include "context.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"
#include "icu_helper.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"
#include "types.h"

//
// INTERFACE definition follows 
//

#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"

class Scheduler : public Icu_h<Scheduler>, public Irq_chip_soft
{
  typedef Icu_h<Scheduler> Icu;

public:
  enum Operation
  {
    Info       = 0,
    Run_thread = 1,
    Idle_time  = 2,
  };

  static Scheduler scheduler;
private:
  Irq_base *_irq;

  L4_RPC(Info,      sched_info, (L4_cpu_set_descr set, Mword *rm, Mword *max_cpus));
  L4_RPC(Idle_time, sched_idle, (L4_cpu_set cpus, Cpu_time *time));

public:  
#line 39 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"
  void
  operator delete (void *);
  
#line 47 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"
  inline Scheduler();
  
#line 150 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"
  inline Irq_base *
  icu_get_irq(unsigned irqnum);
  
#line 160 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"
  inline L4_msg_tag
  op_icu_get_info(Mword *features, Mword *num_irqs, Mword *num_msis);
  
#line 170 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"
  L4_msg_tag
  op_icu_bind(unsigned irqnum, Ko::Cap<Irq> const &irq);
  
#line 188 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"
  L4_msg_tag
  op_icu_set_mode(Mword pin, Irq_chip::Mode);
  
#line 200 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"
  inline void
  trigger_hotplug_event();
  
#line 208 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"
  L4_msg_tag
  kinvoke(L4_obj_ref ref, L4_fpage::Rights rights, Syscall_frame *f,
                     Utcb const *iutcb, Utcb *outcb);

private:  
#line 54 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"
  L4_msg_tag
  sys_run(L4_fpage::Rights, Syscall_frame *f, Utcb const *utcb);
  
#line 114 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"
  L4_msg_tag
  op_sched_idle(L4_cpu_set const &cpus, Cpu_time *time);
  
#line 126 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"
  L4_msg_tag
  op_sched_info(L4_cpu_set_descr const &s, Mword *m, Mword *max_cpus);
};
#line 26 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"

// ----------------------------------------------------------------------------


//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 45 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"


inline Scheduler::Scheduler() : _irq(0)
{
  initial_kobjects.register_obj(this, Initial_kobjects::Scheduler);
}

#line 148 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"


inline Irq_base *
Scheduler::icu_get_irq(unsigned irqnum)
{
  if (irqnum > 0)
    return 0;

  return _irq;
}

#line 158 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"


inline L4_msg_tag
Scheduler::op_icu_get_info(Mword *features, Mword *num_irqs, Mword *num_msis)
{
  *features = 0; // supported features (only normal irqs)
  *num_irqs = 1;
  *num_msis = 0;
  return L4_msg_tag(0);
}

#line 198 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"


inline void
Scheduler::trigger_hotplug_event()
{
  if (_irq)
    _irq->hit(0);
}

#endif // scheduler_h
