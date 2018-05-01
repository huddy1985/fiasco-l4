// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef delayloop_h
#define delayloop_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/delayloop.cpp"

#include "std_macros.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/delayloop.cpp"
#include "initcalls.h"

//
// INTERFACE definition follows 
//

#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/delayloop.cpp"

class Delay
{
private:
  static unsigned count;

public:
  static void init() FIASCO_INIT;

public:  
#line 54 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/delayloop.cpp"
  /**
   * Hint: ms is actually the timer granularity, which
   *       currently happens to be milliseconds
   */
  static void
  delay(unsigned ms);

private:  
#line 24 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/delayloop.cpp"
  static unsigned
  measure();
};

#endif // delayloop_h
