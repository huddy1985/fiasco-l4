// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_kobject_names_h
#define jdb_kobject_names_h
#line 3 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"

#include "config.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
#include "jdb_kobject.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
#include "l4_types.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
#include "initcalls.h"

//
// INTERFACE definition follows 
//

#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"


class Jdb_kobject_name : public Jdb_kobject_extension
{
public:
  static char const *const static_type;
  virtual char const *type() const { return static_type; }

  ~Jdb_kobject_name() {}

  void *operator new (size_t) throw();
  void operator delete (void *);

private:

  char _name[16];

  static Jdb_kobject_name *_names;

public:  
#line 56 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
  int
  max_len();
  
#line 61 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
  Jdb_kobject_name();
  
#line 101 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
  void
  name(char const *name, int size);
  
#line 115 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
  inline char const *
  name() const;
  
#line 120 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
  inline char *
  name();
  
#line 199 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
  static FIASCO_INIT
  void
  init();
};
#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"

//-----------------------------------------------------------------------


//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 113 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"


inline char const *
Jdb_kobject_name::name() const
{ return _name; }

#line 118 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"


inline char *
Jdb_kobject_name::name()
{ return _name; }

#endif // jdb_kobject_names_h
