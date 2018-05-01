// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_input_h
#define jdb_input_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input.cpp"

#include "types.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input.cpp"
#include "l4_types.h"

//
// INTERFACE definition follows 
//

#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input.cpp"

class Jdb_input
{

public:  
#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input.cpp"
  static int
  get_mword(Mword *mword, int digits, int base, int first_char = 0);
  
#line 91 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input.cpp"
  static int
  get_string(char *string, unsigned size);
};

#endif // jdb_input_h
