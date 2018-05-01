// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef filter_console_h
#define filter_console_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/filter_console.cpp"

#include "console.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/filter_console.cpp"
#include "types.h"

//
// INTERFACE definition follows 
//

#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/filter_console.cpp"

class Filter_console : public Console
{
public:
  ~Filter_console() {}

private:
  Console *const _o;
  int csi_timeout;
  enum State
  {
    NORMAL,
    UNKNOWN_ESC,
    GOT_CSI, ///< control sequence introducer
  };

  State state;
  unsigned pos;
  char ibuf[32];
  unsigned arg;
  int args[4];

public:  
#line 38 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/filter_console.cpp"
  int char_avail() const;
  
#line 50 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/filter_console.cpp"
  explicit inline Filter_console(Console *o, int to = 10);
  
#line 59 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/filter_console.cpp"
  int
  write(char const *str, size_t len);
  
#line 123 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/filter_console.cpp"
  int
  getchar(bool b = true);
  
#line 267 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/filter_console.cpp"
  Mword
  get_attributes() const;

private:  
#line 110 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/filter_console.cpp"
  inline int
  getchar_timeout(unsigned timeout);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 48 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/filter_console.cpp"


inline Filter_console::Filter_console(Console *o, int to)
: Console(ENABLED), _o(o), csi_timeout(to), state(NORMAL), pos(0), arg(0)
{
  if (o->failed())
    fail();
}

#endif // filter_console_h
