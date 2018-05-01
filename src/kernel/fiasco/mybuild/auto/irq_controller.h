// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef irq_controller_h
#define irq_controller_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_controller.cpp"

#include "irq.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_controller.cpp"
#include "ram_quota.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_controller.cpp"
#include "icu_helper.h"

//
// INTERFACE definition follows 
//

#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_controller.cpp"

class Irq_chip;
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_controller.cpp"

class Icu : public Icu_h<Icu>
{
  friend class Icu_h<Icu>;

public:  
#line 25 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_controller.cpp"
  void
  operator delete (void *);
  
#line 33 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_controller.cpp"
  inline Irq_base *
  icu_get_irq(unsigned irqnum);
  
#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_controller.cpp"
  inline L4_msg_tag
  op_icu_bind(unsigned irqnum, Ko::Cap<Irq> const &irq);
  
#line 57 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_controller.cpp"
  inline L4_msg_tag
  op_icu_set_mode(Mword pin, Irq_chip::Mode mode);
  
#line 80 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_controller.cpp"
  inline L4_msg_tag
  op_icu_get_info(Mword *features, Mword *num_irqs, Mword *num_msis);
  
#line 90 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_controller.cpp"
  inline L4_msg_tag
  op_icu_msi_info(Mword msi, Unsigned64 source, Irq_mgr::Msi_info *out);
  
#line 98 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_controller.cpp"
  inline Icu();
};
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_controller.cpp"


//----------------------------------------------------------------------------


//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_controller.cpp"
#include "irq_mgr.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 31 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_controller.cpp"


inline Irq_base *
Icu::icu_get_irq(unsigned irqnum)
{
  return Irq_mgr::mgr->irq(irqnum);
}

#line 38 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_controller.cpp"



inline L4_msg_tag
Icu::op_icu_bind(unsigned irqnum, Ko::Cap<Irq> const &irq)
{
  if (!Ko::check_rights(irq.rights, Ko::Rights::CW()))
    return commit_result(-L4_err::EPerm);

  auto g = lock_guard(irq.obj->irq_lock());
  irq.obj->unbind();

  if (!Irq_mgr::mgr->alloc(irq.obj, irqnum))
    return commit_result(-L4_err::EPerm);

  return commit_result(0);
}

#line 55 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_controller.cpp"


inline L4_msg_tag
Icu::op_icu_set_mode(Mword pin, Irq_chip::Mode mode)
{
  Irq_mgr::Irq i = Irq_mgr::mgr->chip(pin);

  if (!i.chip)
    return commit_result(-L4_err::ENodev);

  int r = i.chip->set_mode(i.pin, mode);

  Irq_base *irq = i.chip->irq(i.pin);
  if (irq)
    {
      auto g = lock_guard(irq->irq_lock());
      if (irq->chip() == i.chip && irq->pin() == i.pin)
        irq->switch_mode(i.chip->is_edge_triggered(i.pin));
    }

  return commit_result(r);
}

#line 77 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_controller.cpp"



inline L4_msg_tag
Icu::op_icu_get_info(Mword *features, Mword *num_irqs, Mword *num_msis)
{
  *num_irqs = Irq_mgr::mgr->nr_irqs();
  *num_msis = Irq_mgr::mgr->nr_msis();
  *features = *num_msis ? (unsigned)Msi_bit : 0;
  return L4_msg_tag(0);
}

#line 88 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_controller.cpp"


inline L4_msg_tag
Icu::op_icu_msi_info(Mword msi, Unsigned64 source, Irq_mgr::Msi_info *out)
{
  return commit_result(Irq_mgr::mgr->msg(msi, source, out));
}

#line 95 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_controller.cpp"



inline Icu::Icu()
{
  initial_kobjects.register_obj(this, Initial_kobjects::Icu);
}

#endif // irq_controller_h
