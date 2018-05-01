// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_bp_h
#define jdb_bp_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"

#include "initcalls.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
#include "l4_types.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
#include "string_buffer.h"
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"

#include "string_buffer.h"

//
// INTERFACE definition follows 
//

#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"

class Thread;
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
class Task;
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
class Space;
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"

class Breakpoint
{
public:
  enum Mode { INSTRUCTION=0, WRITE=1, PORTIO=2, ACCESS=3 };
  enum Log  { BREAK=0, LOG=1 };

private:
  typedef struct
    {
      int other;
      Mword thread;
    } Bp_thread_res;

  typedef struct
    {
      int other;
      Mword task;
    } Bp_task_res;

  typedef struct
    {
      char reg;
      Address y, z;
    } Bp_reg_res;

  typedef struct
    {
      unsigned char len;
      Address addr;
      Address y, z;
    } Bp_mem_res;

  typedef struct
    {
      Bp_thread_res thread;
      Bp_task_res   task;
      Bp_reg_res    reg;
      Bp_mem_res    mem;
    } Restriction;

  Address      addr;
  Unsigned8    len;
  Address_type user;
  Mode         mode;
  Log          log;
  Restriction  restrict;
  static char const * const mode_names[4];

public:  
#line 134 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  Breakpoint();
  
#line 141 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  inline void
  kill();
  
#line 148 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  inline int
  unused();
  
#line 155 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  inline int
  break_at_instruction();
  
#line 162 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  inline int
  match_addr(Address virt, Mode m);
  
#line 169 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  inline void
  set_logmode(char m);
  
#line 176 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  inline int
  is_break();
  
#line 183 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  inline void
  restrict_task(int other, Mword task);
  
#line 191 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  inline void
  restrict_thread(int other, Mword thread);
  
#line 199 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  inline void
  restrict_register(char reg, Mword y, Mword z);
  
#line 208 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  inline void
  restrict_memory(Mword addr, Mword len, Mword y, Mword z);
  
#line 218 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  inline void
  clear_restriction();
  
#line 228 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  void
  show();
  
#line 291 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  // return TRUE  if the breakpoint does NOT match
  // return FALSE if all restrictions do match
  
  int
  restricted(Thread *t);
  
#line 348 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  int
  test_break(String_buffer *buf, Thread *t);
  
#line 376 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  // Create log entry if breakpoint matches
  
  void
  test_log(Thread *t);
  
#line 28 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"
  inline void
  set(Address _addr, Mword _len, Mode _mode, Log _log);
};
#line 59 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"

class Jdb_bp
{
public:
  static int		global_breakpoints();
  static void		init_arch();

private:
  static void		at_jdb_enter();
  static void		at_jdb_leave();
  static Breakpoint	bps[4];

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"
private:

private:
  static int		test_sstep();
  static int		test_break(String_buffer *buf);
  static int		test_other(String_buffer *buf);
  static int		test_log_only();
  static Mword		dr7;

#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/32/jdb_bp-ia32.cpp"
private:

  enum
  {
    Val_enter      = 0x0000ff00,
    Val_leave      = 0x00000000,
    Val_test_sstep = 0x00004000,
    Val_test       = 0x0000000f,
    Val_test_other = 0x0000e00f,
  };

public:  
#line 413 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static FIASCO_INIT
  void
  init();
  
#line 446 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static int
  set_breakpoint(int num, Address addr, Mword len,
  		       Breakpoint::Mode mode, Breakpoint::Log log,
  		       Task *task);
  
#line 461 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static void
  clr_breakpoint(int num);
  
#line 469 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static inline void
  logmode_breakpoint(int num, char mode);
  
#line 476 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static int
  first_unused();
  
#line 487 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  // Return 1 if a breakpoint hits
  
  static int
  test_break(String_buffer *buf, Mword dr6);
  
#line 507 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  // Create log entry if breakpoint matches.
  // Return 1 if debugger should stop
  
  static void
  test_log(Mword &dr6);
  
#line 533 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static Mword
  test_match(Address addr, Breakpoint::Mode mode);
  
#line 544 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static int
  instruction_bp_at_addr(Address addr);
  
#line 550 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static inline void
  restrict_task(int num, int other, Mword task);
  
#line 557 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static inline void
  restrict_thread(int num, int other, Mword thread);
  
#line 564 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static inline void
  restrict_register(int num, char reg, Mword y, Mword z);
  
#line 571 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static inline void
  restrict_memory(int num, Mword addr, Mword len, Mword y, Mword z);
  
#line 578 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static inline void
  clear_restriction(int num);
  
#line 585 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static void
  list();
  
#line 39 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"
  static inline Mword
  get_dr(Mword i);

private:  
#line 427 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static inline void
  clr_dr7(int num, Mword &dr7);
  
#line 434 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"
  static inline void
  set_dr7(int num, Mword len, Breakpoint::Mode mode, Mword &dr7);
  
#line 62 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"
  static int
  set_debug_address_register(int num, Mword addr, Mword len,
  				   Breakpoint::Mode mode, Space *);
  
#line 80 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"
  static void
  clr_debug_address_register(int num);
};
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"

#define write_debug_register(num, val) \
    asm volatile("mov %0, %%db" #num : : "r" ((Mword)val))
#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"

#define read_debug_register(num) \
    ({Mword val; asm volatile("mov %%db" #num ",%0" : "=r"(val)); val;})

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 22 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"

#include "kmem.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 181 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-ux.cpp"


inline void
Breakpoint::restrict_task(int other, Mword task)
{
  restrict.task.other = other;
  restrict.task.task  = task;
}

#line 26 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"


inline void
Breakpoint::set(Address _addr, Mword _len, Mode _mode, Log _log)
{
  addr = _addr;
  mode = _mode;
  user = Kmem::is_kmem_page_fault(_addr, 0) ? ADDR_KERNEL : ADDR_USER;
  log  = _log;
  len  = _len;
}

#line 37 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"


inline Mword
Jdb_bp::get_dr(Mword i)
{
  switch (i)
    {
    case 0: return read_debug_register(0);
    case 1: return read_debug_register(1);
    case 2: return read_debug_register(2);
    case 3: return read_debug_register(3);
    case 6: return read_debug_register(6);
    case 7: return dr7;
    default: return 0;
    }
}

#endif // jdb_bp_h
