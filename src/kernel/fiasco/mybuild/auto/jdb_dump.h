// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_dump_h
#define jdb_dump_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"

#include "types.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
#include "l4_types.h"

//
// INTERFACE definition follows 
//

#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"

class Space;

#line 425 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dump.cpp"
int
jdb_dump_addr_task(Address addr, Space *task, int level);

#endif // jdb_dump_h
