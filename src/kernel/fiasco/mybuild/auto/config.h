// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef config_h
#define config_h
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"

#include <globalconfig.h>
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
#include "config_tcbsize.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
#include "l4_types.h"
#line 3 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/config-ia32.cpp"

#include "idt_init.h"

//
// INTERFACE definition follows 
//

#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"

// special magic to allow old compilers to inline constants

#if defined(__clang__)
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
# define COMPILER "clang " __clang_version__
#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
# define GCC_VERSION 409
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
#else
#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
#if defined(__GNUC__)
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
# define COMPILER "gcc " __VERSION__
#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
# define GCC_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)
#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
#else
#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
# define COMPILER "Non-GCC"
#line 22 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
# define GCC_VERSION 0
#line 23 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
#endif
#line 24 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
#endif
#line 25 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"

#define GREETING_COLOR_ANSI_OFF    "\033[0m"
#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"

#define FIASCO_KERNEL_SUBVERSION 3
#line 29 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"

class Config
{
public:

  static const char *const kernel_warn_config_string;
  enum User_memory_access_type
  {
    No_access_user_mem = 0,
    Access_user_mem_direct,
    Must_access_user_mem_direct
  };

  enum {
    SERIAL_ESC_IRQ	= 2,
    SERIAL_ESC_NOIRQ	= 1,
    SERIAL_NO_ESC	= 0,
  };

  static void init();
  static void init_arch();

  // global kernel configuration
  enum
  {
    Kernel_version_id = 0x87004444 | (FIASCO_KERNEL_SUBVERSION << 16), // "DD....."
    // kernel (idle) thread prio
    Kernel_prio = 0,
    // default prio
    Default_prio = 1,

    Warn_level = CONFIG_WARN_LEVEL,

    Kip_syscalls = 1,

    One_shot_min_interval_us =   200,
    One_shot_max_interval_us = 10000,


#ifdef CONFIG_FINE_GRAINED_CPUTIME
    Fine_grained_cputime = true,
#else
    Fine_grained_cputime = false,
#endif

#ifdef CONFIG_STACK_DEPTH
    Stack_depth = true,
#else
    Stack_depth = false,
#endif
#ifdef CONFIG_NO_FRAME_PTR
    Have_frame_ptr = 0,
#else
    Have_frame_ptr = 1,
#endif
    Mapdb_ram_only = 0,
#ifdef CONFIG_DEBUG_KERNEL_PAGE_FAULTS
    Log_kernel_page_faults = 1,
#else
    Log_kernel_page_faults = 0,
#endif
#ifdef CONFIG_JDB
    Jdb = 1,
#else
    Jdb = 0,
#endif
#ifdef CONFIG_JDB_LOGGING
    Jdb_logging = 1,
#else
    Jdb_logging = 0,
#endif
#ifdef CONFIG_JDB_ACCOUNTING
    Jdb_accounting = 1,
#else
    Jdb_accounting = 0,
#endif
#ifdef CONFIG_MP
    Max_num_cpus = CONFIG_MP_MAX_CPUS,
#else
    Max_num_cpus = 1,
#endif
  };

  static Cpu_number max_num_cpus() { return Cpu_number(Max_num_cpus); }

  static bool getchar_does_hlt_works_ok;
  static bool esc_hack;
  static unsigned tbuf_entries;
  static unsigned num_ap_cpus asm("config_num_ap_cpus");

#line 158 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
private:

public:
  // 8 percent of total RAM, >=750MB RAM => 60MB kmem
  static const unsigned kernel_mem_per_cent = 8;
  enum
  {
    kernel_mem_max      = 60 << 20
  };

#line 186 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
private:

public:
  static int  serial_esc;

#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/config-ia32-32.cpp"
private:

public:

  enum {
    PAGE_SHIFT          = ARCH_PAGE_SHIFT,
    PAGE_SIZE           = 1 << PAGE_SHIFT,
    PAGE_MASK           = ~( PAGE_SIZE - 1),

    SUPERPAGE_SHIFT     = 22,
    SUPERPAGE_SIZE      = 1 << SUPERPAGE_SHIFT,
    SUPERPAGE_MASK      = ~( SUPERPAGE_SIZE - 1 ),

    Irq_shortcut        = 1,
  };

#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/config-ia32.cpp"
private:

public:

  enum
  {
#ifdef CONFIG_KERNEL_ISOLATION
    Access_user_mem = No_access_user_mem,
#else
    // can access user memory directly
    Access_user_mem = Access_user_mem_direct,
#endif

    /// Timer vector used with APIC timer or IOAPIC
    Apic_timer_vector = APIC_IRQ_BASE + 0,
  };

  static unsigned scheduler_irq_vector;

  enum Scheduler_config
  {
    SCHED_PIT = 0,
    SCHED_RTC,
    SCHED_APIC,
    SCHED_HPET,

#ifdef CONFIG_SCHED_PIT
    Scheduler_mode        = SCHED_PIT,
    Scheduler_granularity = 1000U,
    Default_time_slice    = 10 * Scheduler_granularity,
#endif

#ifdef CONFIG_ONE_SHOT
    Scheduler_one_shot = true,
#else
    Scheduler_one_shot = false,
#endif

#ifdef CONFIG_SCHED_RTC
    Scheduler_mode = SCHED_RTC,
#  ifdef CONFIG_SLOW_RTC
    Scheduler_granularity = 15625U,
#  else
    Scheduler_granularity = 976U,
#  endif
    Default_time_slice = 10 * Scheduler_granularity,
#endif

#ifdef CONFIG_SCHED_APIC
    Scheduler_mode = SCHED_APIC,
#  ifdef CONFIG_ONE_SHOT
    Scheduler_granularity = 1U,
    Default_time_slice = 10000 * Scheduler_granularity,
#  else
    Scheduler_granularity = 1000U,
    Default_time_slice = 10 * Scheduler_granularity,
#  endif
#endif

#ifdef CONFIG_SCHED_HPET
    Scheduler_mode = SCHED_HPET,
    Scheduler_granularity = 1000U,
    Default_time_slice = 10 * Scheduler_granularity,
#endif
  };

  enum
  {
    Pic_prio_modify = true,
#ifdef CONFIG_SYNC_TSC
    Kip_timer_uses_rdtsc = true,
#else
    Kip_timer_uses_rdtsc = false,
#endif
  };

  static bool apic;

#ifdef CONFIG_WATCHDOG
  static bool watchdog;
#else
  static const bool watchdog = false;
#endif

//  static const bool hlt_works_ok = false;
  static bool hlt_works_ok;

  // the default uart to use for serial console
  static const unsigned default_console_uart = 1;
  static const unsigned default_console_uart_baudrate = 115200;

  static char const char_micro;

  static bool found_vmware;

  enum {
    Is_ux = 0,
  };
};
#line 119 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"

#define GREETING_COLOR_ANSI_TITLE  "\033[1;32m"
#line 121 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
#define GREETING_COLOR_ANSI_INFO   "\033[0;32m"
#line 124 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"
#define TARGET_NAME "x86-32"
#line 133 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"

#define CONFIG_KERNEL_VERSION_STRING \
  GREETING_COLOR_ANSI_TITLE "Welcome to L4/Fiasco.OC!\\n"                      \
  GREETING_COLOR_ANSI_INFO "L4/Fiasco.OC microkernel on " CONFIG_XARCH "\\n"      \
                           "Rev: " CODE_VERSION " compiled with " COMPILER \
                           TARGET_NAME_PHRASE "    [" CONFIG_LABEL "]\\n"    \
                           "Build: #" BUILD_NR " " BUILD_DATE "\\n"            \
  GREETING_COLOR_ANSI_OFF
#line 205 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/config.cpp"

#define FIASCO_SPACE_VIRTUAL
#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/config-ia32-32.cpp"
/* IA32/AMD64 specific */


#endif // config_h
