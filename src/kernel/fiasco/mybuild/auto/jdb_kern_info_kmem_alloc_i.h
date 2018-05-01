// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_kern_info_kmem_alloc_i_h
#define jdb_kern_info_kmem_alloc_i_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kern_info_kmem_alloc.cpp"

#include "static_init.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kern_info_kmem_alloc.cpp"
#include "jdb_kern_info.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kern_info_kmem_alloc.cpp"
#include "kmem_alloc.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kern_info_kmem_alloc.cpp"
#include "kmem_slab.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kern_info_kmem_alloc.cpp"

class Jdb_kern_info_memory : public Jdb_kern_info_module
{
public:  
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kern_info_kmem_alloc.cpp"
  Jdb_kern_info_memory();
  
#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kern_info_kmem_alloc.cpp"
  void
  show();
};

#endif // jdb_kern_info_kmem_alloc_i_h
