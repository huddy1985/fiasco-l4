// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_thread_h
#define jdb_thread_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread.cpp"

#include "thread_object.h"

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread.cpp"

class Jdb_thread
{

public:  
#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread.cpp"
  static void
  print_state_long(Thread *t, unsigned cut_on_len = 0);
  
#line 65 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread.cpp"
  static bool
  has_partner(Thread *t);
  
#line 72 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread.cpp"
  static bool
  has_snd_partner(Thread *t);
  
#line 79 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread.cpp"
  static void
  print_snd_partner(Thread *t, int task_format = 0);
  
#line 90 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread.cpp"
  static void
  print_partner(Thread *t, int task_format = 0);
};

#endif // jdb_thread_h
