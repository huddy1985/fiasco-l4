// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_tbuf_init_h
#define jdb_tbuf_init_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_init.cpp"

#include "jdb_tbuf.h"

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_init.cpp"

class Jdb_tbuf_init : public Jdb_tbuf
{
private:
  static unsigned allocate(unsigned size);

public:
  static void init();
};

#endif // jdb_tbuf_init_h
