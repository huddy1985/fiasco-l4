// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_list_h
#define jdb_list_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"

#include "string_buffer.h"

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"

class Jdb_list
{
public:
  virtual char const *get_mode_str() const { return "[std mode]"; }
  virtual void next_mode() {}
  virtual void next_sort() {}
  virtual void *get_head() const = 0;
  virtual void show_item(String_buffer *buffer, void *item) const = 0;
  virtual char const *show_head() const = 0;
  virtual int seek(int cnt, void **item) = 0;
  virtual bool enter_item(void * /*item*/) const { return true; }
  virtual void *follow_link(void *a) { return a; }
  virtual bool handle_key(void * /*item*/, int /*keycode*/) { return false; }
  virtual void *parent(void * /*item*/) { return 0; }
  virtual void *get_valid(void *a) { return a; }

private:
  typedef String_buf<256> Line_buf;
  void *_start, *_last;
  void *_current;
  char _filter_str[20];

public:  
#line 49 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  Jdb_list();
  
#line 55 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  // set _t_start element of list
  
  void
  set_start(void *start);
  
#line 63 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  // _t_start-- if possible
  
  inline bool
  line_back();
  
#line 69 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  // _t_start++ if possible
  
  inline bool
  line_forw();
  
#line 87 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  // _t_start -= 24 if possible
  
  bool
  page_back();
  
#line 93 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  // _t_start += 24 if possible
  
  bool
  page_forw();
  
#line 112 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  // _t_start = first element of list
  
  bool
  goto_home();
  
#line 118 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  // _t_start = last element of list
  
  bool
  goto_end();
  
#line 293 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  // show complete page using show callback function
  
  int
  page_show();
  
#line 404 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  void
  show_header();
  
#line 412 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  void
  do_list();

private:  
#line 131 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  // search index of search starting from _start
  
  int
  lookup_in_visible_area(void *search);
  
#line 150 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  // get y'th element of thread list starting from _t_start
  
  void *
  index(int y);
  
#line 162 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  void
  handle_string_filter_input();
  
#line 184 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  Jdb_list::Line_buf *
  render_visible(void *i);
  
#line 213 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  int
  print_limit(const char *s, int visible_len);
  
#line 242 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  void
  show_line(Jdb_list::Line_buf *b);
  
#line 255 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  void *
  get_visible(void *i);
  
#line 267 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"
  int
  filtered_seek(int cnt, void **item, Jdb_list::Line_buf **buf = 0);
};
#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"


// ---------------------------------------------------------------------------


//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 62 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"

// _t_start-- if possible

inline bool
Jdb_list::line_back()
{ return filtered_seek(-1, &_start); }

#line 68 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"

// _t_start++ if possible

inline bool
Jdb_list::line_forw()
{
  if (filtered_seek(1, &_last))
    return filtered_seek(1, &_start);
  else
    return false;
}

#endif // jdb_list_h
