// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_factory_i_h
#define jdb_factory_i_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_factory.cpp"

#include <climits>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
#include <cstring>
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
#include <cstdio>
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_factory.cpp"

#include "jdb.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
#include "jdb_core.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
#include "jdb_module.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
#include "jdb_screen.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
#include "jdb_kobject.h"
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
#include "kernel_console.h"
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
#include "keycodes.h"
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
#include "factory.h"
#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
#include "simpleio.h"
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
#include "static_init.h"
#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_factory.cpp"

class Jdb_factory : public Jdb_kobject_handler
{
public:
  Jdb_factory() FIASCO_INIT;

public:  
#line 32 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
  bool
  show_kobject(Kobject_common *, int );
  
#line 39 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_factory.cpp"
  void
  show_kobject_short(String_buffer *buf, Kobject_common *o);
};

#endif // jdb_factory_i_h
