// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_tbuf_output_h
#define jdb_tbuf_output_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"

#include "initcalls.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"
#include "l4_types.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"
#include "thread.h"

//
// INTERFACE definition follows 
//

#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"

class Tb_entry;
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"
class String_buffer;
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"

class Jdb_tbuf_output
{
private:
  typedef void (Format_entry_fn)(String_buffer *, Tb_entry *tb, const char *tidstr,
                                 int tidlen);
  static Format_entry_fn *_format_entry_fn[];
  static bool show_names;

public:  
#line 87 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"
  static void FIASCO_INIT
  init();
  
#line 99 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"
  static void
  register_ff(Unsigned8 type, Format_entry_fn format_entry_fn);
  
#line 111 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"
  // return thread+ip of entry <e_nr>
  
  static int
  thread_ip(int e_nr, Thread const **th, Mword *ip);
  
#line 129 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"
  static void
  toggle_names();
  
#line 162 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"
  static void
  print_entry(String_buffer *buf, int e_nr);
  
#line 172 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"
  static void
  print_entry(String_buffer *buf, Tb_entry *tb);
  
#line 205 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"
  static bool
  set_filter(const char *filter_str, Mword *entries);

private:  
#line 78 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf_output.cpp"
  static void
  dummy_format_entry(String_buffer *buf, Tb_entry *tb, const char *, int);
};

#endif // jdb_tbuf_output_h
