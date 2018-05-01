// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb.h"
#include "jdb_i.h"

#line 69 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-thread.cpp"
// Inside Jdb the method Jdb::get_thread() should be used instead of
// Thread::current_thread(). The latter function cannot not handle the
// case when we came from the kernel stack context!



#line 29 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-thread.cpp"


void
Jdb_tid_ext::ext()
{
  if (Jdb::get_current_active())
    printf("(%p) ", Jdb::get_current_active());
}

#line 37 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-thread.cpp"


void
Jdb_tid_ext::update()
{
  Jdb::get_current(Jdb::current_cpu);
}

#line 55 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-thread.cpp"


void
Jdb::get_current(Cpu_number cpu)
{
  current_active = get_thread(cpu);
}
