// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef vlog_h
#define vlog_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"

#include "icu_helper.h"

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"

class Irq;
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"

class Vlog :
  public cxx::Dyn_castable<Vlog, Icu_h<Vlog> >,
  public Irq_chip_soft
{
public:
  enum O_flags
  {
    F_ONLCR  = 000004, ///< Map NL to CR-NL on output
    F_OCRNL  = 000010, ///< Map CR to NL on output
    F_ONLRET = 000040, ///< Do not ouput CR
  };

  enum I_flags
  {
    F_INLCR = 000100,
    F_IGNCR = 000200,
    F_ICRNL = 000400,
  };

  enum L_flags
  {
    F_ECHO = 000010,
  };

private:
  Irq_base *_irq;
  Mword _i_flags;
  Mword _o_flags;
  Mword _l_flags;

public:  
#line 52 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"
  Vlog();
  
#line 60 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"
  void
  operator delete (void *);
  
#line 140 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"
  void
  bind(Irq_base *irq, Mword irqnum);
  
#line 149 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"
  L4_msg_tag
  op_icu_bind(unsigned irqnum, Ko::Cap<Irq> const &irq);
  
#line 166 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"
  L4_msg_tag
  op_icu_set_mode(Mword pin, Irq_chip::Mode);
  
#line 207 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"
  inline Irq_base *
  icu_get_irq(unsigned irqnum);
  
#line 218 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"
  inline L4_msg_tag
  op_icu_get_info(Mword *features, Mword *num_irqs, Mword *num_msis);
  
#line 229 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"
  L4_msg_tag
  kinvoke(L4_obj_ref ref, L4_fpage::Rights rights, Syscall_frame *f,
                Utcb const *r_msg, Utcb *s_msg);

private:  
#line 68 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"
  inline void
  log_string(Syscall_frame *f, Utcb const *u);
  
#line 100 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"
  inline L4_msg_tag
  get_input(L4_fpage::Rights rights, Syscall_frame *f, Utcb *u);
  
#line 178 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"
  inline L4_msg_tag
  set_attr(L4_fpage::Rights, Syscall_frame const *, Utcb const *u);
  
#line 194 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"
  inline L4_msg_tag
  get_attr(L4_fpage::Rights, Syscall_frame *, Utcb *u);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 205 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"


inline Irq_base *
Vlog::icu_get_irq(unsigned irqnum)
{
  if (irqnum > 0)
    return 0;

  return _irq;
}

#line 215 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"



inline L4_msg_tag
Vlog::op_icu_get_info(Mword *features, Mword *num_irqs, Mword *num_msis)
{
  *features = 0; // supported features (only normal irqs)
  *num_irqs = 1;
  *num_msis = 0;
  return L4_msg_tag(0);
}

#endif // vlog_h
