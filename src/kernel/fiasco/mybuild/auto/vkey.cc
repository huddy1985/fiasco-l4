// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "vkey.h"
#include "vkey_i.h"

#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"

static Irq_base *vkey_irq;
#line 23 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"

// ------------------------------------------------------------------------

#line 54 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"

static Vkey::Echo_type vkey_echo;
#line 56 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"
static char     vkey_buffer[256];
#line 57 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"
static unsigned vkey_tail, vkey_head;

#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"


void
Vkey::irq(Irq_base *i)
{ vkey_irq = i; }

#line 58 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"


void
Vkey::set_echo(Echo_type echo)
{
  vkey_echo = echo;
}

#line 65 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"


bool
Vkey::add(int c)
{
  bool hit = false;
  unsigned nh = (vkey_head + 1) % sizeof(vkey_buffer);
  unsigned oh = vkey_head;
  if (nh != vkey_tail)
    {
      vkey_buffer[vkey_head] = c;
      vkey_head = nh;
    }

  if (oh == vkey_tail)
    hit = true;

  if (vkey_echo == Vkey::Echo_crnl && c == '\r')
    c = '\n';

  if (vkey_echo)
    putchar(c);

  return hit;
}

#line 90 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"


bool
Vkey::add(const char *seq)
{
  bool hit = false;
  for (; *seq; ++seq)
    hit |= add(*seq);
  return hit;
}

#line 100 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"


void
Vkey::trigger()
{
  if (vkey_irq)
    vkey_irq->hit(0);
}

#line 108 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"


void
Vkey::add_char(int v)
{
  if (add(v))
    trigger();
}

#line 116 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"


int
Vkey::check_()
{
  int  ret = 1;
  bool hit = false;

  // disable last branch recording, branch trace recording ...
  Cpu::cpus.cpu(current_cpu()).debugctl_disable();

  while (1)
    {
      int c = Kconsole::console()->getchar(false);

      if (c == -1)
	break;

      if (is_debugger_entry_key(c))
	{
	  ret = 0;  // break into kernel debugger
	  break;
	}

      switch (c)
	{
	case KEY_CURSOR_UP:    hit |= add("\033[A"); break;
	case KEY_CURSOR_DOWN:  hit |= add("\033[B"); break;
	case KEY_CURSOR_LEFT:  hit |= add("\033[D"); break;
	case KEY_CURSOR_RIGHT: hit |= add("\033[C"); break;
	case KEY_CURSOR_HOME:  hit |= add("\033[1~"); break;
	case KEY_CURSOR_END:   hit |= add("\033[4~"); break;
	case KEY_PAGE_UP:      hit |= add("\033[5~"); break;
	case KEY_PAGE_DOWN:    hit |= add("\033[6~"); break;
	case KEY_INSERT:       hit |= add("\033[2~"); break;
	case KEY_DELETE:       hit |= add("\033[3~"); break;
	case KEY_F1:           hit |= add("\033OP"); break;
	case KEY_BACKSPACE:    hit |= add(127); break;
	case KEY_TAB:          hit |= add(9); break;
	case KEY_ESC:          hit |= add(27); break;
	case KEY_SINGLE_ESC:   hit |= add(27); break;
	case KEY_RETURN:       hit |= add(13); break;
	case KEY_RETURN_2:     hit |= add(13); break;
	default:               hit |= add(c); break;
	}
    }

  if (hit)
    trigger();

  // reenable debug stuff (undo debugctl_disable)
  Cpu::cpus.cpu(current_cpu()).debugctl_enable();

  return ret;
}

#line 171 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"


int
Vkey::get()
{
  if (vkey_tail != vkey_head)
    return vkey_buffer[vkey_tail];

  return -1;
}

#line 181 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"


void
Vkey::clear()
{
  if (vkey_tail != vkey_head)
    vkey_tail = (vkey_tail + 1) % sizeof(vkey_buffer);
}
