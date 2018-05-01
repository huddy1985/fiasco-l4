// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef watchdog_h
#define watchdog_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"

#include "types.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"
#include "initcalls.h"

//
// INTERFACE definition follows 
//

#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"

class Watchdog
{
public:
  static void (*touch)(void);
  static void (*enable)(void);
  static void (*disable)(void);
  
private:
  Watchdog();                        // default constructors are undefined
  Watchdog(const Watchdog&);

  typedef struct
    {
      unsigned active:1;
      unsigned user_active:1;
      unsigned no_user_control:1;
    } Watchdog_flags;

  static Watchdog_flags flags;

public:  
#line 77 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"
  // user enables Watchdog
  
  static inline void
  user_enable();
  
#line 86 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"
  // user disables Watchdog
  
  static inline void
  user_disable();
  
#line 95 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"
  // user takes over control of Watchdog
  
  static inline void
  user_takeover_control();
  
#line 101 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"
  // user gives back control of Watchdog
  
  static inline void
  user_giveback_control();
  
#line 110 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"
  static void FIASCO_INIT
  init();

private:  
#line 48 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"
  static void
  do_nothing();
  
#line 52 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"
  static void
  perf_enable();
  
#line 63 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"
  static void
  perf_disable();
  
#line 70 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"
  static void
  perf_touch();
};
#line 26 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"

// ------------------------------------------------------------------------


//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 37 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"
#include "perf_cnt.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 76 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"

// user enables Watchdog

inline void
Watchdog::user_enable()
{
  flags.user_active = 1;
  Perf_cnt::start_watchdog();
}

#line 85 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"

// user disables Watchdog

inline void
Watchdog::user_disable()
{
  flags.user_active = 0;
  Perf_cnt::stop_watchdog();
}

#line 94 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"

// user takes over control of Watchdog

inline void
Watchdog::user_takeover_control()
{ flags.no_user_control = 0; }

#line 100 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/watchdog-ia32.cpp"

// user gives back control of Watchdog

inline void
Watchdog::user_giveback_control()
{ flags.no_user_control = 0; }

#endif // watchdog_h
