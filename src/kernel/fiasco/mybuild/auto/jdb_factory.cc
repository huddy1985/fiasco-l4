// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_factory.h"
#include "jdb_factory_i.h"

#line 45 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_factory.cpp"

static Jdb_factory jdb_factory INIT_PRIORITY(JDB_MODULE_INIT_PRIO);

#line 23 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_factory.cpp"


Jdb_factory::Jdb_factory()
  : Jdb_kobject_handler((Factory*)0)
{
  Jdb_kobject::module()->register_handler(this);
}

#line 30 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_factory.cpp"


bool
Jdb_factory::show_kobject(Kobject_common *, int )
{
  return true;
}

#line 37 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_factory.cpp"


void
Jdb_factory::show_kobject_short(String_buffer *buf, Kobject_common *o)
{
  Factory *t = cxx::dyn_cast<Factory*>(o);
  buf->printf(" c=%lu l=%lu", t->current(), t->limit());
}
