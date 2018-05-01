// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_screen_h
#define jdb_screen_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"

#include "types.h"

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"

class Jdb_screen
{
public:
  static const unsigned Mword_size_bmode = sizeof(Mword) * 2;
  static const unsigned Mword_size_cmode = sizeof(Mword);
  static const unsigned Col_head_size = sizeof(Mword) * 2;

  static const char *Mword_adapter;
  static const char *Mword_not_mapped;
  static const char *Mword_blank;

  static const char *const Reg_names[];
  static const char Reg_prefix;
  static const char *Line;

  static const char *Root_page_table;

private:
  static unsigned int _height;
  static unsigned int _width;
  static bool         _direct_enabled;

public:  
#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"
  static void
  set_height(unsigned int h);
  
#line 46 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"
  static void
  set_width(unsigned int w);
  
#line 51 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"
  static inline unsigned int
  width();
  
#line 56 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"
  static inline unsigned int
  height();
  
#line 61 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"
  static inline unsigned long
  cols(unsigned headsize, unsigned entrysize);
  
#line 66 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"
  static inline unsigned long
  cols();
  
#line 71 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"
  static inline unsigned long
  rows();
  
#line 76 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"
  static inline void
  enable_direct(bool enable);
  
#line 81 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"
  static inline bool
  direct_enabled();
  
#line 28 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_screen-ia32.cpp"
  static int
  num_regs();
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 49 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"


inline unsigned int
Jdb_screen::width()
{ return _width; }

#line 54 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"


inline unsigned int
Jdb_screen::height()
{ return _height; }

#line 59 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"


inline unsigned long
Jdb_screen::cols(unsigned headsize, unsigned entrysize)
{ return (width() - headsize) / (entrysize + 1) + 1; }

#line 64 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"


inline unsigned long
Jdb_screen::cols()
{ return cols(Col_head_size, Mword_size_bmode); }

#line 69 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"


inline unsigned long
Jdb_screen::rows()
{ return ((unsigned long)-1) / ((cols() - 1) * 4) + 1; }

#line 74 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"


inline void
Jdb_screen::enable_direct(bool enable)
{ _direct_enabled = enable; }

#line 79 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"


inline bool
Jdb_screen::direct_enabled()
{ return _direct_enabled; }

#endif // jdb_screen_h
