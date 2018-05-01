// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_utcb.h"
#include "jdb_utcb_i.h"

#line 1 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"
/**
 * @brief Jdb-Utcb module
 *
 * This module shows the user tcbs and the vCPU state of a thread/vcpu
 */


#line 28 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"


static Jdb_utcb Jdb_utcb INIT_PRIORITY(JDB_MODULE_INIT_PRIO);
#line 31 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"

Kobject *Jdb_utcb::thread;
#line 132 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"

STATIC_INITIALIZE(Jdb_kobject_utcb_hdl);

#line 33 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"


Jdb_utcb::Jdb_utcb()
  : Jdb_module("INFO")
{}

#line 38 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"


void
Jdb_utcb::print(Thread *t)
{
  if (t->utcb().kern())
    {
      printf("\nUtcb-addr: %p\n", t->utcb().kern());
      t->utcb().kern()->print();
    }

  if (t->state(false) & Thread_vcpu_enabled)
    {
      Vcpu_state *v = t->vcpu_state().kern();
      printf("\nVcpu-state-addr: %p\n", v);
      printf("state: %x    saved-state:  %x  sticky: %x\n",
             (unsigned)v->state, (unsigned)v->_saved_state,
             (unsigned)v->sticky_flags);
      printf("entry_sp = %lx    entry_ip = %lx  sp = %lx\n",
             v->_entry_sp, v->_entry_ip, v->_sp);
      v->_regs.dump();
    }
}

#line 61 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"


Jdb_module::Action_code
Jdb_utcb::action( int cmd, void *&, char const *&, int &)
{
  if (cmd)
    return NOTHING;

  Thread *t = cxx::dyn_cast<Thread *>(thread);
  if (!t)
    {
      printf(" Invalid thread\n");
      return NOTHING;
    }

  print(t);

  return NOTHING;
}

#line 80 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"


int
Jdb_utcb::num_cmds() const
{ return 1; }

#line 85 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"


Jdb_module::Cmd
const * Jdb_utcb::cmds() const
{
  static Cmd cs[] =
    {
      { 0, "z", "z", "%q", "z<thread>\tshow UTCB and vCPU state", &thread }
    };
  return cs;
}

#line 106 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"

FIASCO_INIT
void
Jdb_kobject_utcb_hdl::init()
{
  static Jdb_kobject_utcb_hdl hdl;
  Jdb_kobject::module()->register_handler(&hdl);
}

#line 114 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_utcb.cpp"


bool
Jdb_kobject_utcb_hdl::handle_key(Kobject_common *o, int keycode)
{
  if (keycode == 'z')
    {
      Thread *t = cxx::dyn_cast<Thread *>(o);
      if (!t)
        return false;

      Jdb_utcb::print(t);
      Jdb::getchar();
      return true;
    }

  return false;
}
