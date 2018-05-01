// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_kern_info_data_i_h
#define jdb_kern_info_data_i_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kern_info_data.cpp"

#include "jdb_kern_info.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kern_info_data.cpp"
#include "static_init.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kern_info_data.cpp"

class Jdb_kern_info_data : public Jdb_kern_info_module
{

public:  
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kern_info_data.cpp"
  Jdb_kern_info_data();
  
#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kern_info_data.cpp"
  void
  show();

private:  
#line 30 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kern_info_data.cpp"
  void
  show_percpu_offsets();
};

#endif // jdb_kern_info_data_i_h
