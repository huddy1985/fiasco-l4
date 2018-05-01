// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "vlog.h"
#include "vlog_i.h"

#line 48 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"

JDB_DEFINE_TYPENAME(Vlog, "Vlog");
#line 256 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"


static Vlog __vlog;

#line 65 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"



inline void
Vlog::log_string(Syscall_frame *f, Utcb const *u)
{
  L4_snd_item_iter snd_items(u, f->tag().words());

  unsigned len = u->values[1];
  char const *str = (char const *)&u->values[2];

  if (len > sizeof(u->values) - sizeof(u->values[0]) * 2)
    return;

  while (len--)
    {
      int c = *str++;

      // the kernel does this anyway
#if 0
      if (_o_flags & F_ONLCR && c == '\n')
	putchar('\r');
#endif

      if (_o_flags & F_OCRNL && c == '\r')
	c = '\n';

      if (_o_flags & F_ONLRET && c == '\r')
	continue;

      putchar(c);
    }
}

#line 98 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"


inline L4_msg_tag
Vlog::get_input(L4_fpage::Rights rights, Syscall_frame *f, Utcb *u)
{
  (void)f;

  if (!have_receive(u))
    return commit_result(0);

  if (!(rights & L4_fpage::Rights::X()))
    return commit_result(-L4_err::EPerm);

  char *buffer = reinterpret_cast<char *>(&u->values[1]);
  long cnt_down = min<Mword>(u->values[0] >> 16,
                             sizeof(u->values) - sizeof(u->values[0]));
  int i;
  while ((i = Vkey::get()) != -1 && cnt_down)
    {
      Vkey::clear();

      if (_i_flags & F_INLCR && i == '\n')
	i = '\r';

      if (_i_flags & F_IGNCR && i == '\r')
	continue;

      if (_i_flags & F_ICRNL && i == '\r')
	i = '\n';

      *buffer = i;
      ++buffer;
      --cnt_down;
    }

  u->values[0] = buffer - reinterpret_cast<char *>(&u->values[1]);
  if (i == -1)
    u->values[0] |= 1UL<<31;
  return commit_result(0);
}

#line 176 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"


inline L4_msg_tag
Vlog::set_attr(L4_fpage::Rights, Syscall_frame const *, Utcb const *u)
{
  _i_flags = u->values[1];
  _o_flags = u->values[2] | F_ONLCR;
  _l_flags = u->values[3];
  Vkey::set_echo((!(_l_flags & F_ECHO))
                  ? Vkey::Echo_off
                  : (_o_flags & F_OCRNL
                    ? Vkey::Echo_crnl
                    : Vkey::Echo_on));

  return commit_result(0);
}

#line 192 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"


inline L4_msg_tag
Vlog::get_attr(L4_fpage::Rights, Syscall_frame *, Utcb *u)
{
  if (!have_receive(u))
    return commit_result(0);

  u->values[1] = _i_flags;
  u->values[2] = _o_flags;
  u->values[3] = _l_flags;
  return commit_result(0, 4);
}

#line 50 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"


Vlog::Vlog()
: _irq(0),
  _i_flags(F_ICRNL), _o_flags(F_ONLCR), _l_flags(F_ECHO)
{
  Vkey::set_echo(Vkey::Echo_crnl);
  initial_kobjects.register_obj(this, Initial_kobjects::Log);
}

#line 59 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"

void
Vlog::operator delete (void *)
{
  printf("WARNING: tried to delete kernel Vlog object.\n");
}

#line 138 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"


void
Vlog::bind(Irq_base *irq, Mword irqnum)
{
  Irq_chip_soft::bind(irq, irqnum);
  _irq = irq;
  Vkey::irq(irq);
}

#line 147 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"


L4_msg_tag
Vlog::op_icu_bind(unsigned irqnum, Ko::Cap<Irq> const &irq)
{
  if (irqnum > 0)
    return commit_result(-L4_err::EInval);

  if (_irq)
    _irq->unbind();

  if (!Ko::check_rights(irq.rights, Ko::Rights::CW()))
    return commit_result(-L4_err::EPerm);

  bind(irq.obj, irqnum);
  return commit_result(0);
}

#line 164 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"


L4_msg_tag
Vlog::op_icu_set_mode(Mword pin, Irq_chip::Mode)
{
  if (pin != 0)
    return commit_result(-L4_err::EInval);

  if (_irq)
    _irq->switch_mode(true);
  return commit_result(0);
}

#line 226 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vlog.cpp"



L4_msg_tag
Vlog::kinvoke(L4_obj_ref ref, L4_fpage::Rights rights, Syscall_frame *f,
              Utcb const *r_msg, Utcb *s_msg)
{
  L4_msg_tag const t = f->tag();

  if (t.proto() == L4_msg_tag::Label_irq)
    return Icu_h<Vlog>::icu_invoke(ref, rights, f, r_msg, s_msg);
  else if (t.proto() != L4_msg_tag::Label_log)
    return commit_result(-L4_err::EBadproto);

  switch (r_msg->values[0])
    {
    case 0:
      log_string(f, r_msg);
      return no_reply();

    case 2: // set attr
      return set_attr(rights, f, r_msg);

    case 3: // get attr
      return get_attr(rights, f, s_msg);

    default:
      return get_input(rights, f, s_msg);
    }
}
