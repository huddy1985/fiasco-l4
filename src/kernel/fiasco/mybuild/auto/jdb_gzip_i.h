// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_gzip_i_h
#define jdb_gzip_i_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"

#include <cstring>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
#include <cstdio>
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"

#include "config.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
#include "console.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
#include "gzip.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
#include "kernel_console.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
#include "kmem_alloc.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
#include "panic.h"
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
#include "static_init.h"
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"

class Jdb_gzip : public Console
{
  static const unsigned heap_pages = 28;
  char   active;
  char   init_done;
  static Console *uart;

public:  
#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
  inline void
  enable();
  
#line 55 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
  inline void
  disable();
  
#line 65 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
  void
  state(Mword new_state);
  
#line 80 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
  int
  write(char const *str, size_t len);
  
#line 88 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
  static Console*
  console();
  
#line 96 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
  Mword
  get_attributes() const;
  
#line 102 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
  static FIASCO_INIT
  void
  init();

private:  
#line 24 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
  Jdb_gzip();
  
#line 33 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_gzip.cpp"
  static void
  raw_write(const char *s, size_t len);
};

#endif // jdb_gzip_i_h
