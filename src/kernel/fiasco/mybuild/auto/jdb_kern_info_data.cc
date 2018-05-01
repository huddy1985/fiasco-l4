// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_kern_info_data.h"
#include "jdb_kern_info_data_i.h"

#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kern_info_data.cpp"

static Jdb_kern_info_data k_a INIT_PRIORITY(JDB_MODULE_INIT_PRIO+1);
#line 25 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kern_info_data.cpp"

// ------------------------------------------------------------------------


#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kern_info_data.cpp"


Jdb_kern_info_data::Jdb_kern_info_data()
  : Jdb_kern_info_module('s', "Kernel Data Info")
{
  Jdb_kern_info::register_subcmd(this);
}

#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kern_info_data.cpp"


void
Jdb_kern_info_data::show()
{
  show_percpu_offsets();
}

#line 28 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kern_info_data.cpp"


void
Jdb_kern_info_data::show_percpu_offsets()
{}
