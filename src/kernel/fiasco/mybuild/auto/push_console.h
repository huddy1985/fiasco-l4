// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef push_console_h
#define push_console_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/push_console.cpp"

#include "console.h"

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/push_console.cpp"

class Push_console : public Console
{
public:
  Push_console() : Console(ENABLED) {}
private:
  char _buffer[256];
  int _in;
  int _out;

public:  
#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/push_console.cpp"
  int
  getchar(bool /*blocking*/);
  
#line 36 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/push_console.cpp"
  int
  char_avail() const;
  
#line 43 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/push_console.cpp"
  int
  write(char const * /*str*/, size_t len);
  
#line 50 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/push_console.cpp"
  void
  push(char c);
  
#line 65 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/push_console.cpp"
  inline void
  flush();
  
#line 72 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/push_console.cpp"
  inline Mword
  get_attributes() const;
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 63 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/push_console.cpp"


inline void
Push_console::flush()
{
  _in = _out = 0;
}

#line 70 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/push_console.cpp"


inline Mword
Push_console::get_attributes() const
{
  return PUSH | IN;
}

#endif // push_console_h
