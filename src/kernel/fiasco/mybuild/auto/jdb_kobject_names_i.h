// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_kobject_names_i_h
#define jdb_kobject_names_i_h
#line 30 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"

#include <cstdio>
#line 32 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"

#include <feature.h>
#line 34 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
#include "context.h"
#line 35 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
#include "kmem_alloc.h"
#line 36 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
#include "minmax.h"
#line 37 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
#include "panic.h"
#line 38 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
#include "space.h"
#line 39 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
#include "thread.h"
#line 40 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
#include "static_init.h"
#line 123 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"

class Jdb_name_hdl : public Jdb_kobject_handler
{
public:
  virtual bool show_kobject(Kobject_common *, int) { return true; }
  virtual ~Jdb_name_hdl() {}

public:  
#line 132 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
  void
  show_kobject_short(String_buffer *buf, Kobject_common *o);
  
#line 143 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
  bool
  invoke(Kobject_common *o, Syscall_frame *f, Utcb *utcb);
};

#endif // jdb_kobject_names_i_h
