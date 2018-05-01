// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_ipc_gate.h"
#include "jdb_ipc_gate_i.h"

#line 54 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_ipc_gate.cpp"

static Jdb_ipc_gate jdb_space INIT_PRIORITY(JDB_MODULE_INIT_PRIO);

#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_ipc_gate.cpp"


Jdb_ipc_gate::Jdb_ipc_gate()
  : Jdb_kobject_handler((Ipc_gate_obj*)0)
{
  Jdb_kobject::module()->register_handler(this);
}

#line 28 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_ipc_gate.cpp"


Kobject_common *
Jdb_ipc_gate::follow_link(Kobject_common *o)
{
  Ipc_gate_obj *g = cxx::dyn_cast<Ipc_gate_obj *>(Kobject::from_dbg(o->dbg_info()));
  return g->thread() ? Kobject::from_dbg(g->thread()->dbg_info()) : o;
}

#line 36 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_ipc_gate.cpp"


bool
Jdb_ipc_gate::show_kobject(Kobject_common *, int)
{ return true; }

#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_ipc_gate.cpp"


void
Jdb_ipc_gate::show_kobject_short(String_buffer *buf, Kobject_common *o)
{
  Ipc_gate_obj *g = cxx::dyn_cast<Ipc_gate_obj*>(Kobject::from_dbg(o->dbg_info()));
  if (!g)
    return;

  buf->printf(" L=%s%08lx\033[0m D=%lx",
              (g->id() & 3) ? JDB_ANSI_COLOR(lightcyan) : "",
              g->id(), g->thread() ? g->thread()->dbg_info()->dbg_id() : 0);
}
