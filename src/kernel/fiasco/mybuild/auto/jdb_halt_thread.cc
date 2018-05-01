// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_halt_thread.h"
#include "jdb_halt_thread_i.h"

#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_halt_thread.cpp"

Kobject *Jdb_halt_thread::threadid;
#line 65 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_halt_thread.cpp"

static Jdb_halt_thread jdb_halt_thread INIT_PRIORITY(JDB_MODULE_INIT_PRIO);

#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_halt_thread.cpp"


Jdb_module::Action_code
Jdb_halt_thread::action(int cmd, void *&, char const *&, int &)
{
  if (cmd != 0)
    return NOTHING;

  Thread *t = cxx::dyn_cast<Thread*>(threadid);

  if (!t)
    return NOTHING;

  t->regs()->cs(Gdt::gdt_code_kernel | Gdt::Selector_kernel);
  t->regs()->ip(reinterpret_cast<Address>(&Thread::halt_current));
  t->regs()->flags(0);  // disable interrupts
  putchar('\n');

  return NOTHING;
}

#line 40 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_halt_thread.cpp"


Jdb_module::Cmd const *
Jdb_halt_thread::cmds() const
{
  static Cmd cs[] =
    {
	{ 0, "H", "halt", "%q", "H<threadid>\thalt a specific thread",
	  &threadid },
    };

  return cs;
}

#line 53 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_halt_thread.cpp"


int
Jdb_halt_thread::num_cmds() const
{
  return 1;
}

#line 60 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_halt_thread.cpp"


Jdb_halt_thread::Jdb_halt_thread()
  : Jdb_module("MISC")
{}
