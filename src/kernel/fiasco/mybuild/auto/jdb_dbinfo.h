// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_dbinfo_h
#define jdb_dbinfo_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dbinfo.cpp"

#include "initcalls.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dbinfo.cpp"
#include "types.h"

//
// INTERFACE definition follows 
//

#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dbinfo.cpp"

class Jdb_symbol_info;
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dbinfo.cpp"
class Jdb_lines_info;
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dbinfo.cpp"

class Jdb_dbinfo
{

public:  
#line 67 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dbinfo.cpp"
  static FIASCO_INIT
  void
  init();
  
#line 158 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dbinfo.cpp"
  static bool
  map(Address phys, size_t &size, Address &virt);
  
#line 179 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dbinfo.cpp"
  static void
  unmap(Address virt, size_t size);
  
#line 194 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dbinfo.cpp"
  static void
  set(Jdb_symbol_info *sym, Address phys, size_t size);
  
#line 224 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dbinfo.cpp"
  static void
  set(Jdb_lines_info *lin, Address phys, size_t size);

private:  
#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dbinfo.cpp"
  // We have to do this here because Jdb_symbol and Jdb_lines must not depend
  // on Kmem_alloc.
  
  static inline void
  init_symbols_lines ();
  
#line 81 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dbinfo.cpp"
  static Address
  reserve_pages(unsigned pages);
  
#line 134 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dbinfo.cpp"
  static void
  return_pages(Address addr, unsigned pages);
};
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_dbinfo.cpp"


//---------------------------------------------------------------------------


#endif // jdb_dbinfo_h
