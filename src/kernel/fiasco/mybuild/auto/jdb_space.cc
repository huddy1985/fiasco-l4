// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_space.h"
#include "jdb_space_i.h"


#line 88 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
static bool space_filter(Kobject_common const *o);

#line 120 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
static bool
filter_task_thread(Kobject_common const *o);
#line 28 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"

Task *Jdb_space::task;
#line 125 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
static Jdb_space jdb_space INIT_PRIORITY(JDB_MODULE_INIT_PRIO);
#line 126 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
static Jdb_kobject_list::Mode INIT_PRIORITY(JDB_MODULE_INIT_PRIO) tnt("[Tasks + Threads]", filter_task_thread);

#line 30 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"


Jdb_space::Jdb_space()
  : Jdb_module("INFO"), Jdb_kobject_handler((Task*)0)
{
  Jdb_kobject::module()->register_handler(this);
}

#line 37 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"


bool
Jdb_space::show_kobject(Kobject_common *o, int lvl)
{
  Task *t = cxx::dyn_cast<Task*>(o);
  show(t);
  if (lvl)
    {
      Jdb::getchar();
      return true;
    }

  return false;
}

#line 52 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"


void
Jdb_space::show_kobject_short(String_buffer *buf, Kobject_common *o)
{
  Task *t = cxx::dyn_cast<Task*>(o);
  if (t == Kernel_task::kernel_task())
    buf->printf(" {KERNEL}");

  buf->printf(" R=%ld", t->ref_cnt());
}

#line 63 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"


void
Jdb_space::print_space(Space *s)
{
  printf("%p", s);
}

#line 70 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"


void
Jdb_space::show(Task *t)
{
  printf("Space %p (Kobject*)%p\n", t, static_cast<Kobject*>(t));

  for (Space::Ku_mem_list::Const_iterator m = t->_ku_mem.begin(); m != t->_ku_mem.end();
       ++m)
    printf("  utcb area: user_va=%p kernel_va=%p size=%x\n",
           m->u_addr.get(), m->k_addr, m->size);

  unsigned long m = t->ram_quota()->current();
  unsigned long l = t->ram_quota()->limit();
  printf("  mem usage:  %lu (%luKB) of %lu (%luKB) @%p\n", 
         m, m/1024, l, l/1024, t->ram_quota());
}

#line 87 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"

static bool space_filter(Kobject_common const *o)
{ return cxx::dyn_cast<Task const *>(o); }

#line 90 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"


Jdb_module::Action_code
Jdb_space::action(int cmd, void *&, char const *&, int &)
{
  if (cmd == 0)
    {
      Jdb_kobject_list list(space_filter);
      list.do_list();
    }
  return NOTHING;
}

#line 102 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"


Jdb_module::Cmd const *
Jdb_space::cmds() const
{
  static Cmd cs[] =
    {
	{ 0, "s", "spacelist", "", "s\tshow task list", 0 },
    };
  return cs;
}

#line 113 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"
  

int
Jdb_space::num_cmds() const
{ return 1; }

#line 118 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_space.cpp"


static bool
filter_task_thread(Kobject_common const *o)
{
  return cxx::dyn_cast<Task const *>(o) || cxx::dyn_cast<Thread const *>(o);
}
