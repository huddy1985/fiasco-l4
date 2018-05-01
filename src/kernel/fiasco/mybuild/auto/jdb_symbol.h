// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_symbol_h
#define jdb_symbol_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_symbol.cpp"

#include <globalconfig.h>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_symbol.cpp"
#include "l4_types.h"

//
// INTERFACE definition follows 
//

#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_symbol.cpp"

class Space;
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_symbol.cpp"

class Jdb_symbol_info
{
private:
  Address  _virt;
  size_t   _size;
  Address  _beg_sym;
  Address  _end_sym;

public:  
#line 61 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_symbol.cpp"
  inline char*
  str ();
  
#line 68 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_symbol.cpp"
  inline void
  get (Address &virt, size_t &size);
  
#line 76 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_symbol.cpp"
  inline void
  reset ();
  
#line 83 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_symbol.cpp"
  inline bool
  in_range (Address addr);
  
#line 179 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_symbol.cpp"
  // register symbols for a specific task (called by user mode application)
  
  bool
  set (Address virt, size_t size);

private:  
#line 89 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_symbol.cpp"
  // read address from current position and return its value
  
  static inline Address
  string_to_addr (const char *symstr);
  
#line 117 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_symbol.cpp"
  // Optimize symbol table to speed up address-to-symbol search.
  // Replace stringified address (8/16 characters) by 2/4 dwords of 32/64 bit:
  // The symbol value and the absolute address of the next symbol (or 0 if end
  // of list)
  
  bool
  transform ();
};
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_symbol.cpp"

class Jdb_symbol
{
public:
  enum
  {
    // don't allow more than 2048 tasks to register their symbols to save space
    Max_tasks = 2048,
#ifdef CONFIG_BIT32
    Digits = 8,
    Start  = 11,
#else
    Digits = 16,
    Start  = 19,
#endif
  };

private:
  static Jdb_symbol_info *_task_symbols;

public:  
#line 50 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_symbol.cpp"
  static void
  init (void *mem, Mword pages);
  
#line 235 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_symbol.cpp"
  static Jdb_symbol_info*
  lookup (Space *task);
  
#line 278 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_symbol.cpp"
  // Search a symbol in symbols of a specific task. If the symbol
  // was not found, search in kernel symbols too (if exists)
  
  static Address
  match_symbol_to_addr (const char *symbol, bool search_instr,
  				  Space *task);
  
#line 312 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_symbol.cpp"
  // try to search a possible symbol completion
  
  static bool
  complete_symbol (char *symbol, unsigned size, Space *task);
  
#line 393 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_symbol.cpp"
  // search symbol name that matches for a specific address
  
  static const char*
  match_addr_to_symbol (Address addr, Space *task);
  
#line 422 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_symbol.cpp"
  // search last symbol before eip
  
  static bool
  match_addr_to_symbol_fuzzy (Address *addr_ptr, Space *task,
  				        char *t_symbol, int s_symbol);

private:  
#line 251 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_symbol.cpp"
  // search symbol in task's symbols, return pointer to symbol name
  
  static const char*
  match_symbol (const char *symbol, bool search_instr, Space *task);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 66 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_symbol.cpp"


inline void
Jdb_symbol_info::get (Address &virt, size_t &size)
{
  virt = _virt;
  size = _size;
}

#line 74 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_symbol.cpp"


inline void
Jdb_symbol_info::reset ()
{
  _virt = 0;
}

#endif // jdb_symbol_h
