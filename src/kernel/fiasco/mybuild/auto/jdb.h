// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_h
#define jdb_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"

#include <cxx/function>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"

#include "l4_types.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "cpu_mask.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "jdb_core.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "jdb_handler_queue.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "mem.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "per_cpu_data.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "processor.h"
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "string_buffer.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

#include "l4_types.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "pic.h"
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"

#include "jdb_core.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"
#include "jdb_handler_queue.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"
#include "jdb_entry_frame.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"
#include "trap_state.h"

//
// INTERFACE definition follows 
//

#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"

class Context;
#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
class Space;
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
class Thread;
#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
class Push_console;
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"

class Jdb_entry_frame;
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-thread.cpp"

class Space;
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

class Trap_state;
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
class Thread;
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
class Console_buffer;
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
class Jdb_entry_frame;
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
class Push_console;
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"

class Space;
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"
class Thread;
#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"

class Jdb : public Jdb_core
{
public:
  struct Remote_func : cxx::functor<void (Cpu_number)>
  {
    bool running;

    Remote_func() = default;
    Remote_func(Remote_func const &) = delete;
    Remote_func operator = (Remote_func const &) = delete;

    void reset_mp_safe()
    {
      set_monitored_address(&_f, (Func)0);
    }

    void set_mp_safe(cxx::functor<void (Cpu_number)> const &rf)
    {
      Remote_func const &f = static_cast<Remote_func const &>(rf);
      running = true;
      _d = f._d;
      Mem::mp_mb();
      set_monitored_address(&_f, f._f);
      Mem::mp_mb();
    }

    void monitor_exec(Cpu_number current_cpu)
    {
      if (Func f = monitor_address(current_cpu, &_f))
        {
          _f = 0;
          f(_d, cxx::forward<Cpu_number>(current_cpu));
          Mem::mp_mb();
          running = false;
        }
    }

    void wait() const
    {
      for (;;)
        {
          Mem::mp_mb();
          if (!running)
            break;
          Proc::pause();
        }
    }
  };

  static Per_cpu<Jdb_entry_frame*> entry_frame;
  static Cpu_number current_cpu;
  static Per_cpu<Remote_func> remote_func;

  static int FIASCO_FASTCALL enter_jdb(Jdb_entry_frame *e, Cpu_number cpu);
  static void cursor_end_of_screen();
  static void cursor_home();
  static void printf_statline(const char *prompt, const char *help,
                              const char *format, ...)
  __attribute__((format(printf, 3, 4)));
  static void save_disable_irqs(Cpu_number cpu);
  static void restore_irqs(Cpu_number cpu);

protected:
  template< typename T >
  static void set_monitored_address(T *dest, T val);

  template< typename T >
  static T monitor_address(Cpu_number, T const volatile *addr);

private:
  Jdb();			// default constructors are undefined
  Jdb(const Jdb&);

  static char hide_statline;
  static char last_cmd;
  static char next_cmd;
  static Per_cpu<String_buf<81> > error_buffer;
  static bool was_input_error;

  static Thread  *current_active;

  static const char *toplevel_cmds;
  static const char *non_interactive_cmds;

  // state for traps in JDB itself
  static Per_cpu<bool> running;
  static bool in_service;
  static bool leave_barrier;
  static unsigned long cpus_in_debugger;
  static bool never_break;
  static bool jdb_active;

  static void enter_trap_handler(Cpu_number cpu);
  static void leave_trap_handler(Cpu_number cpu);
  static bool handle_conditional_breakpoint(Cpu_number cpu, Jdb_entry_frame *e);
  static void handle_nested_trap(Jdb_entry_frame *e);
  static bool handle_user_request(Cpu_number cpu);
  static bool handle_debug_traps(Cpu_number cpu);
  static bool test_checksums();

public:
  static Jdb_handler_queue jdb_enter;
  static Jdb_handler_queue jdb_leave;

  // esc sequences for highlighting
  static char  esc_iret[];
  static char  esc_bt[];
  static char  esc_emph[];
  static char  esc_emph2[];
  static char  esc_mark[];
  static char  esc_line[];
  static char  esc_symbol[];


#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"
private:

public:
  enum
  {
    NOFANCY=0,
    FANCY=1
  };

  enum Direction
  {
    Cursor_up = 'A',
    Cursor_down = 'B',
    Cursor_right = 'C',
    Cursor_left = 'D'
  };

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-thread.cpp"
private:

public:
  /**
   * Deliver Thread object which was active at entry of kernel debugger.
   * If we came from the kernel itself, return Thread with id 0.0
   */
  static Thread *get_thread(Cpu_number cpu);

#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
private:

public:
  enum
  {
    Msr_test_default     = 0,
    Msr_test_fail_warn   = 1,
    Msr_test_fail_ignore = 2,
  };

  static void init();

  static Per_cpu<unsigned> apic_tpr;
  static Unsigned16 pic_status;
  static volatile char msr_test;
  static volatile char msr_fail;

  typedef enum
    {
      s_unknown, s_ipc, s_syscall, s_pagefault, s_fputrap,
      s_interrupt, s_timer_interrupt, s_slowtrap, s_user_invoke,
    } Guessed_thread_state;


  static int (*bp_test_log_only)();
  static int (*bp_test_sstep)();
  static int (*bp_test_break)(String_buffer *buf);
  static int (*bp_test_other)(String_buffer *buf);

private:

  static char _connected;
  static Per_cpu<char> permanent_single_step;
  static Per_cpu<char> code_ret, code_call, code_bra, code_int;

  typedef enum
    {
      SS_NONE=0, SS_BRANCH, SS_RETURN
    } Step_state;

  static Per_cpu<Step_state> ss_state;
  static Per_cpu<int> ss_level;

  static const Unsigned8 *debug_ctrl_str;
  static int              debug_ctrl_len;

  static Per_cpu<int> jdb_irqs_disabled;

public:  
#line 201 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static bool
  cpu_in_jdb(Cpu_number cpu);
  
#line 208 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  template< typename Func > static void
  foreach_cpu(Func const &f);
  
#line 218 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  template< typename Func > static bool
  foreach_cpu(Func const &f, bool positive);
  
#line 237 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static inline void
  set_next_cmd(char cmd);
  
#line 242 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static inline int
  was_last_cmd();
  
#line 247 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static inline int
  get_next_cmd();
  
#line 251 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  /** Command aborted. If we are interpreting a debug command like
   *  enter_kdebugger("*#...") this is an error
   */
  
  static void
  abort_command();
  
#line 311 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static bool is_toplevel_cmd(char c);
  
#line 327 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static int
  execute_command(const char *s, int first_char = -1);
  
#line 359 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static int
  execute_command_short(const char *s, int first_char = -1);
  
#line 366 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static int
  execute_command_long(const char *s, int first_char = -1);
  
#line 373 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static Push_console *
  push_cons();
  
#line 678 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static void
  remote_work(Cpu_number cpu, cxx::functor<void (Cpu_number)> &&func,
                   bool sync = true);
  
#line 699 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  template<typename Func> static void
  on_each_cpu(Func &&func, bool single_sync = true);
  
#line 706 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  template<typename Func> static void
  on_each_cpu_pl(Func &&func);
  
#line 715 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static int
  getchar(void);
  
#line 735 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  //-------- pretty print functions ------------------------------
  
  static void
  write_ll_ns(String_buffer *buf, Signed64 ns, bool sign);
  
#line 803 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static void
  write_ll_hex(String_buffer *buf, Signed64 x, bool sign);
  
#line 818 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static void
  write_ll_dec(String_buffer *buf, Signed64 x, bool sign);
  
#line 837 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static void
  cpu_mask_print(Cpu_mask &m);
  
#line 861 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static inline Thread*
  get_current_active();
  
#line 868 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static inline Jdb_entry_frame*
  get_entry_frame(Cpu_number cpu);
  
#line 874 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  /// handling of standard cursor keys (Up/Down/PgUp/PgDn)
  
  static int
  std_cursor_key(int c, Mword cols, Mword lines, Mword max_absy, Mword *absy,
                      Mword *addy, Mword *addx, bool *redraw);
  
#line 1014 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static inline Space *
  get_task(Cpu_number cpu);
  
#line 1024 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  //
  // memory access wrappers
  //
  
  
  
  template< typename T > static bool
  peek(T const *addr, Space *task, T &value);
  
#line 1044 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  template< typename T > static bool
  poke(T *addr, Space *task, T const &value);
  
#line 33 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"
  static inline void
  cursor( Direction d, unsigned n = 1);
  
#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"
  static void
  cursor (unsigned int row=0, unsigned int col=0);
  
#line 51 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"
  static inline void
  blink_cursor (unsigned int row, unsigned int col);
  
#line 58 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"
  static inline void
  cursor_save();
  
#line 65 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"
  static inline void
  cursor_restore();
  
#line 72 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"
  static inline void
  screen_erase();
  
#line 79 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"
  static void
  screen_scroll (unsigned int start, unsigned int end);
  
#line 89 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"
  static inline void
  clear_to_eol();
  
#line 95 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"
  // preserve the history of the serial console if fancy != 0
  
  static void
  clear_screen(int fancy=FANCY);
  
#line 57 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-thread.cpp"
  static void
  get_current(Cpu_number cpu);
  
#line 64 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-thread.cpp"
  static inline Space*
  get_current_space();
  
#line 198 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  static inline bool
  connected();
  
#line 332 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  static Space *
  translate_task(Address addr, Space *task);
  
#line 339 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  static void
  peek_phys(Address phys, void *value, int width);
  
#line 350 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  static void
  poke_phys(Address phys, void const *value, int width);
  
#line 362 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  static int
  peek_task(Address addr, Space *task, void *value, int width);
  
#line 402 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  static int
  poke_task(Address addr, Space *task, void const *value, int width);
  
#line 440 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  // The content of apdapter memory is not shown by default because reading
  // memory-mapped I/O registers may confuse the hardware. We assume that all
  // memory above the end of the RAM is adapter memory.
  
  static int
  is_adapter_memory(Address virt, Space *task);
  
#line 480 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  // Try to guess the thread state of t by walking down the kernel stack and
  // locking at the first return address we find.
  
  static Jdb::Guessed_thread_state
  guess_thread_state(Thread *t);
  
#line 533 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  static void
  set_single_step(Cpu_number cpu, int on);
  
#line 980 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  static inline void
  enter_getchar();
  
#line 985 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  static inline void
  leave_getchar();
  
#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"
  static void
  write_tsc_s(String_buffer *buf, Signed64 tsc, bool sign);
  
#line 79 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"
  static void
  write_tsc(String_buffer *buf, Signed64 tsc, bool sign);
  
#line 89 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"
  static int
  get_register(char *reg);

private:  
#line 348 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static int
  execute_command_mode(bool is_short, const char *s, int first_char = -1);
  
#line 380 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  // Interprete str as non interactive commands for Jdb. We allow mostly 
  // non-interactive commands here (e.g. we don't allow d, t, l, u commands)
  
  static int
  execute_command_ni(Space *task, char const *str, int len = 1000);
  
#line 427 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static bool
  input_short_mode(Jdb::Cmd *cmd, char const **args, int &cmd_key);
  
#line 521 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static bool
  input_long_mode(Jdb::Cmd *cmd, char const **args);
  
#line 600 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static int
  execute_command();
  
#line 632 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static bool
  open_debug_console(Cpu_number cpu);
  
#line 653 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static void
  close_debug_console(Cpu_number cpu);
  
#line 1106 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static inline void
  rcv_uart_enable();
  
#line 1279 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static bool
  stop_all_cpus(Cpu_number);
  
#line 1285 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static void
  leave_wait_for_others();
  
#line 1290 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static bool
  check_for_cpus(bool);
  
#line 1295 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
  static inline int
  remote_work_ipi_process(Cpu_number);
  
#line 77 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  static void init_serial_console();
  
#line 220 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  static inline void
  backspace();
  
#line 545 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  static bool
  handle_special_cmds(int c);
  
#line 591 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  // take a look at the code of the current thread eip
  // set global indicators code_call, code_ret, code_bra, code_int
  // This can fail if the current page is still not mapped
  static void
  analyze_code(Cpu_number cpu);
  
#line 647 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  // entered debugger because of single step trap
  static inline int
  handle_single_step(Cpu_number cpu);
  
#line 706 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  // entered debugger due to debug exception
  static inline int
  handle_trap1(Cpu_number cpu);
  
#line 729 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  // entered debugger due to software breakpoint
  static inline int
  handle_trap3(Cpu_number cpu);
  
#line 797 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
  // entered debugger due to other exception
  static inline int
  handle_trapX(Cpu_number cpu);
};
#line 135 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"

//---------------------------------------------------------------------------

#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-thread.cpp"

//---------------------------------------------------------------------------

#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"

// ------------------------------------------------------------------------


//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 138 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"

#include <cstdio>
#line 140 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
#include <cstring>
#line 141 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
#include <ctype.h>
#line 142 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
#include <simpleio.h>
#line 143 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"

#include "config.h"
#line 145 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "delayloop.h"
#line 146 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "feature.h"
#line 147 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "jdb_core.h"
#line 148 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "jdb_entry_frame.h"
#line 149 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "jdb_screen.h"
#line 150 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "kernel_console.h"
#line 151 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "processor.h"
#line 152 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "push_console.h"
#line 153 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "static_init.h"
#line 154 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "keycodes.h"
#line 155 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "libc_backend.h"
#line 1102 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"

#include "kernel_uart.h"
#line 1115 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"

#include "ipi.h"
#line 1117 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"
#include "logdefs.h"
#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"

#include <cstdio>
#line 29 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"
#include <simpleio.h>
#line 30 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"
#include "jdb_screen.h"
#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-thread.cpp"

#include "jdb_prompt_ext.h"
#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-thread.cpp"
#include "jdb.h"
#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-thread.cpp"
#include "thread.h"
#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-thread.cpp"
#include "mem_layout.h"
#line 72 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

#include <cstdio>
#line 74 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "kernel_uart.h"
#line 98 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

#include <cstring>
#line 100 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include <csetjmp>
#line 101 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include <cstdarg>
#line 102 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include <climits>
#line 103 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include <cstdlib>
#line 104 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include <cstdio>
#line 105 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "simpleio.h"
#line 106 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

#include "apic.h"
#line 108 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "boot_info.h"
#line 109 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "checksum.h"
#line 110 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "config.h"
#line 111 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "cpu.h"
#line 112 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "initcalls.h"
#line 113 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "idt.h"
#line 114 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "io_apic.h"
#line 115 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "jdb_core.h"
#line 116 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "jdb_screen.h"
#line 117 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "kernel_console.h"
#line 118 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "keycodes.h"
#line 119 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "kernel_uart.h"
#line 120 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "kernel_task.h"
#line 121 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "kmem.h"
#line 122 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "koptions.h"
#line 123 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "logdefs.h"
#line 124 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "mem_layout.h"
#line 125 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "pic.h"
#line 126 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "push_console.h"
#line 127 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "processor.h"
#line 128 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "regdefs.h"
#line 129 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "static_init.h"
#line 130 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "terminate.h"
#line 131 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "thread.h"
#line 132 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "thread_state.h"
#line 133 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "timer.h"
#line 134 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "timer_tick.h"
#line 135 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "trap_state.h"
#line 136 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "vkey.h"
#line 137 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"
#include "watchdog.h"
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"

#include "config.h"
#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"
#include "div32.h"
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"
#include "kernel_console.h"
#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"
#include "paging.h"
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-ux.cpp"
#include "jdb_screen.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 235 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"


inline void
Jdb::set_next_cmd(char cmd)
{ next_cmd = cmd; }

#line 240 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"


inline int
Jdb::was_last_cmd()
{ return last_cmd; }

#line 245 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"


inline int
Jdb::get_next_cmd()
{ return next_cmd; }

#line 859 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"


inline Thread*
Jdb::get_current_active()
{
  return current_active;
}

#line 866 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"


inline Jdb_entry_frame*
Jdb::get_entry_frame(Cpu_number cpu)
{
  return entry_frame.cpu(cpu);
}

#line 1012 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"


inline Space *
Jdb::get_task(Cpu_number cpu)
{
  if (!get_thread(cpu))
    return 0;
  else
    return get_thread(cpu)->space();
}

#line 31 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"


inline void
Jdb::cursor( Direction d, unsigned n)
{
  printf("\033[%u%c", n, (char)d);
}

#line 49 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"


inline void
Jdb::blink_cursor (unsigned int row, unsigned int col)
{
  printf ("\033[%u;%uf", row, col);
}

#line 56 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"


inline void
Jdb::cursor_save()
{
  putstr ("\0337");
}

#line 63 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"


inline void
Jdb::cursor_restore()
{
  putstr ("\0338");
}

#line 70 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"


inline void
Jdb::screen_erase()
{
  putstr ("\033[2J");
}   

#line 87 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-ansi.cpp"


inline void
Jdb::clear_to_eol()
{
  putstr("\033[K");
}

#line 62 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb-thread.cpp"


inline Space*
Jdb::get_current_space()
{
  return current_active ? current_active->space() : 0;
}

#line 197 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"

inline bool
Jdb::connected()
{
  return _connected;
}

#line 978 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"


inline void
Jdb::enter_getchar()
{}

#line 983 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"


inline void
Jdb::leave_getchar()
{}

#line 187 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"



template< typename T > inline void
Jdb::set_monitored_address(T *dest, T val)
{ *const_cast<T volatile *>(dest) = val; }

#line 203 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb-ia32-amd64.cpp"


template< typename T > inline T
Jdb::monitor_address(Cpu_number current_cpu, T volatile const *addr)
{
  if (!*addr && Cpu::cpus.cpu(current_cpu).has_monitor_mwait())
    {
      asm volatile ("monitor \n" : : "a"(addr), "c"(0), "d"(0) );
      Mword irq_sup = Cpu::cpus.cpu(current_cpu).has_monitor_mwait_irq() ? 1 : 0;
      asm volatile ("mwait   \n" : : "a"(0x00), "c"(irq_sup) );
    }

  return *addr;
}

//
// IMPLEMENTATION of function templates
//


#line 204 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"




template< typename Func > void
Jdb::foreach_cpu(Func const &f)
{
  for (Cpu_number i = Cpu_number::first(); i < Config::max_num_cpus(); ++i)
    if (cpu_in_jdb(i))
      f(i);
}

#line 215 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"



template< typename Func > bool
Jdb::foreach_cpu(Func const &f, bool positive)
{
  bool r = positive;
  for (Cpu_number i = Cpu_number::first(); i < Config::max_num_cpus(); ++i)
    if (cpu_in_jdb(i))
      {
        bool res = f(i);

        if (positive)
          r = r && res;
        else
          r = r || res;
      }

  return r;
}

#line 697 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"

 
template<typename Func> void
Jdb::on_each_cpu(Func &&func, bool single_sync)
{
  foreach_cpu([&](Cpu_number cpu){ remote_work(cpu, cxx::forward<Func>(func), single_sync); });
}

#line 704 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"

 
template<typename Func> void
Jdb::on_each_cpu_pl(Func &&func)
{
  foreach_cpu([&](Cpu_number cpu){ remote_work(cpu, cxx::forward<Func>(func), false); });

  foreach_cpu([](Cpu_number cpu){ Jdb::remote_func.cpu(cpu).wait(); });
}

#line 1022 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"


//
// memory access wrappers
//



template< typename T > bool
Jdb::peek(T const *addr, Space *task, T &value)
{
  // use an Mword here instead of T as some implementations of peek_task use
  // an Mword in their operation which is potentially bigger than T
  // XXX: should be fixed
  Mword tmp;
  bool ret = peek_task((Address)addr, task, &tmp, sizeof(T)) == 0;
  value = tmp;
  return ret;
}

#line 1041 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb.cpp"



template< typename T > bool
Jdb::poke(T *addr, Space *task, T const &value)
{ return poke_task((Address)addr, task, &value, sizeof(T)) == 0; }

#endif // jdb_h
