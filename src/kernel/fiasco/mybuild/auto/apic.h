// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef apic_h
#define apic_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

#include "per_cpu_data.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "types.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "initcalls.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "pm.h"

//
// INTERFACE definition follows 
//

#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

class Return_frame;
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
class Cpu;
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

class Apic : public Pm_object
{
public:
  static void init(bool resume = false) FIASCO_INIT_AND_PM;
  Unsigned32 apic_id() const { return _id; }
  Unsigned32 cpu_id() const { return _id >> 24; }

  static Per_cpu<Static_object<Apic> > apic;

private:
  Apic(const Apic&) = delete;
  Apic &operator = (Apic const &) = delete;

  Unsigned32 _id;
  Unsigned32 _saved_apic_timer;

  static void			error_interrupt(Return_frame *regs)
				asm ("apic_error_interrupt") FIASCO_FASTCALL;

  static int			present;
  static int			good_cpu;
  static const			Address io_base;
  static Address		phys_base;
  static unsigned		timer_divisor;
  static unsigned		frequency_khz;
  static Unsigned64		scaler_us_to_apic;

  enum
  {
    APIC_id			= 0x20,
    APIC_lvr			= 0x30,
    APIC_tpr                    = 0x80,
    APIC_tpri_mask		= 0xFF,
    APIC_eoi			= 0xB0,
    APIC_ldr			= 0xD0,
    APIC_ldr_mask		= 0xFFul << 24,
    APIC_dfr			= 0xE0,
    APIC_spiv			= 0xF0,
    APIC_isr			= 0x100,
    APIC_tmr			= 0x180,
    APIC_irr			= 0x200,
    APIC_esr			= 0x280,
    APIC_lvtt			= 0x320,
    APIC_lvtthmr		= 0x330,
    APIC_lvtpc			= 0x340,
    APIC_lvt0			= 0x350,
    APIC_timer_base_div		= 0x2,
    APIC_lvt1			= 0x360,
    APIC_lvterr			= 0x370,
    APIC_tmict			= 0x380,
    APIC_tmcct			= 0x390,
    APIC_tdcr			= 0x3E0,

    APIC_snd_pending		= 1 << 12,
    APIC_input_polarity		= 1 << 13,
    APIC_lvt_remote_irr		= 1 << 14,
    APIC_lvt_level_trigger	= 1 << 15,
    APIC_lvt_masked		= 1 << 16,
    APIC_lvt_timer_periodic	= 1 << 17,
    APIC_tdr_div_1		= 0xB,
    APIC_tdr_div_2		= 0x0,
    APIC_tdr_div_4		= 0x1,
    APIC_tdr_div_8		= 0x2,
    APIC_tdr_div_16		= 0x3,
    APIC_tdr_div_32		= 0x8,
    APIC_tdr_div_64		= 0x9,
    APIC_tdr_div_128		= 0xA,
  };

  enum
  {
    Mask			=  1,
    Trigger_mode		=  2,
    Remote_irr			=  4,
    Pin_polarity		=  8,
    Delivery_state		= 16,
    Delivery_mode		= 32,
  };

  enum
  {
    APIC_base_msr		= 0x1b,
  };

public:  
#line 108 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  inline Apic(Cpu_number cpu);
  
#line 126 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static Cpu_number
  find_cpu(Unsigned32 phys_id);
  
#line 132 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  void
  pm_on_suspend(Cpu_number);
  
#line 141 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  void
  pm_on_resume(Cpu_number);
  
#line 166 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline Unsigned32
  us_to_apic(Unsigned64 us);
  
#line 237 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline Unsigned32
  get_id();
  
#line 281 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline unsigned
  get_frequency_khz();
  
#line 288 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline Unsigned32
  reg_read(unsigned reg);
  
#line 295 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline void
  reg_write(unsigned reg, Unsigned32 val);
  
#line 302 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline int
  reg_delivery_mode(Unsigned32 val);
  
#line 309 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline int
  reg_lvt_vector(Unsigned32 val);
  
#line 316 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline Unsigned32
  timer_reg_read();
  
#line 323 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline Unsigned32
  timer_reg_read_initial();
  
#line 330 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline void
  timer_reg_write(Unsigned32 val);
  
#line 338 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline Address
  apic_page_phys();
  
#line 342 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  // set the global pagetable entry for the Local APIC device registers
  
  static FIASCO_INIT_AND_PM
  void
  map_apic_page();
  
#line 391 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline void
  timer_enable_irq();
  
#line 402 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline void
  timer_disable_irq();
  
#line 413 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline int
  timer_is_irq_enabled();
  
#line 420 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline void
  timer_set_periodic();
  
#line 429 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline void
  timer_set_one_shot();
  
#line 438 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline void
  timer_assign_irq_vector(unsigned vector);
  
#line 448 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline void
  irq_ack();
  
#line 503 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline int
  have_pcint();
  
#line 510 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline int
  have_tsint();
  
#line 554 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline void
  tpr(unsigned prio);
  
#line 559 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline unsigned
  tpr();
  
#line 646 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  // give us a hint if we have an APIC but it is disabled
  
  static int
  test_present_but_disabled();
  
#line 658 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  // activate APIC by writing to appropriate MSR
  static FIASCO_INIT_CPU_AND_PM
  void
  activate_by_msr();
  
#line 674 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  // check if we still receive interrupts after we changed the IRQ routing
  static FIASCO_INIT_CPU
  int
  check_still_getting_interrupts();
  
#line 701 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline int
  is_present();
  
#line 708 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static void
  set_perf_nmi();
  
#line 799 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  // deactivate APIC by writing to appropriate MSR
  
  static void
  done();
  
#line 828 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static void
  dump_info();
  
#line 48 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-debug.cpp"
  static void
  reg_show(unsigned reg);
  
#line 63 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-debug.cpp"
  static void
  regs_show(void);
  
#line 84 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-debug.cpp"
  static void
  timer_show(void);
  
#line 94 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-debug.cpp"
  static void
  id_show(void);
  
#line 122 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-debug.cpp"
  static void
  irr_show();
  
#line 129 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-debug.cpp"
  static void
  isr_show();

private:  
#line 112 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static Cpu &
  cpu();
  
#line 244 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline Unsigned32
  get_version();
  
#line 251 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline int
  is_integrated();
  
#line 258 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline Unsigned32
  get_max_lvt_local();
  
#line 265 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline Unsigned32
  get_num_errors();
  
#line 273 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static inline void
  clear_num_errors();
  
#line 361 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  // check CPU type if APIC could be present
  static FIASCO_INIT_AND_PM
  int
  test_cpu();
  
#line 382 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  // test if APIC present
  
  static inline int
  test_present();
  
#line 456 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static void
  timer_set_divisor(unsigned newdiv);
  
#line 496 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static int
  get_max_lvt();
  
#line 516 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  // check if APIC is working (check timer functionality)
  static FIASCO_INIT_AND_PM
  int
  check_working();
  
#line 538 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static FIASCO_INIT_CPU_AND_PM
  void
  init_spiv();
  
#line 563 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static FIASCO_INIT_CPU_AND_PM
  void
  init_tpr();
  
#line 570 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  // activate APIC error interrupt
  static FIASCO_INIT_CPU_AND_PM
  void
  enable_errors();
  
#line 597 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  // activate APIC after activating by MSR was successful
  // see "Intel Architecture Software Developer's Manual,
  //      Volume 3: System Programming Guide, Appendix E"
  static FIASCO_INIT_AND_PM
  void
  route_pic_through_apic();
  
#line 628 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static FIASCO_INIT_CPU_AND_PM
  void
  init_lvt();
  
#line 715 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static FIASCO_INIT_CPU_AND_PM
  void
  calibrate_timer();
  
#line 818 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
  static FIASCO_INIT_CPU_AND_PM
  void
  init_timer();
  
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-debug.cpp"
  static const char*
  reg_lvt_bit_str(unsigned reg, Unsigned32 val, int bit);
  
#line 101 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-debug.cpp"
  static void
  bitfield_show(unsigned reg, const char *name, char flag);
};
#line 95 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

extern unsigned apic_spurious_interrupt_bug_cnt;
#line 97 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
extern unsigned apic_spurious_interrupt_cnt;
#line 98 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
extern unsigned apic_error_cnt;
#line 99 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


//----------------------------------------------------------------------------


//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 207 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
#include "cpu.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 106 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline Apic::Apic(Cpu_number cpu) : _id(get_id()) { register_pm(cpu); }

#line 164 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline Unsigned32
Apic::us_to_apic(Unsigned64 us)
{
  Unsigned32 apic, dummy1, dummy2;
  asm ("movl  %%edx, %%ecx		\n\t"
       "mull  %4			\n\t"
       "movl  %%ecx, %%eax		\n\t"
       "movl  %%edx, %%ecx		\n\t"
       "mull  %4			\n\t"
       "addl  %%ecx, %%eax		\n\t"
       "shll  $11, %%eax		\n\t"
      :"=a" (apic), "=d" (dummy1), "=&c" (dummy2)
      : "A" (us),   "g" ((Unsigned32)scaler_us_to_apic)
        // scaler_us_to_apic is actually 32-bit
       );
  return apic;
}

#line 235 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline Unsigned32
Apic::get_id()
{
  return reg_read(APIC_id) & 0xff000000;
}

#line 279 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline unsigned
Apic::get_frequency_khz()
{
  return frequency_khz;
}

#line 286 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline Unsigned32
Apic::reg_read(unsigned reg)
{
  return *((volatile Unsigned32*)(io_base + reg));
}

#line 293 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline void
Apic::reg_write(unsigned reg, Unsigned32 val)
{
  *((volatile Unsigned32*)(io_base + reg)) = val;
}

#line 300 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline int
Apic::reg_delivery_mode(Unsigned32 val)
{
  return (val >> 8) & 7;
}

#line 307 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline int
Apic::reg_lvt_vector(Unsigned32 val)
{
  return val & 0xff;
}

#line 314 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline Unsigned32
Apic::timer_reg_read()
{
  return reg_read(APIC_tmcct);
}

#line 321 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline Unsigned32
Apic::timer_reg_read_initial()
{
  return reg_read(APIC_tmict);
}

#line 328 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline void
Apic::timer_reg_write(Unsigned32 val)
{
  reg_read(APIC_tmict);
  reg_write(APIC_tmict, val);
}

#line 336 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline Address
Apic::apic_page_phys()
{ return Cpu::rdmsr(APIC_base_msr) & 0xfffff000; }

#line 389 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline void
Apic::timer_enable_irq()
{
  Unsigned32 tmp_val;

  tmp_val = reg_read(APIC_lvtt);
  tmp_val &= ~(APIC_lvt_masked);
  reg_write(APIC_lvtt, tmp_val);
}

#line 400 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline void
Apic::timer_disable_irq()
{
  Unsigned32 tmp_val;

  tmp_val = reg_read(APIC_lvtt);
  tmp_val |= APIC_lvt_masked;
  reg_write(APIC_lvtt, tmp_val);
}

#line 411 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline int
Apic::timer_is_irq_enabled()
{
  return ~reg_read(APIC_lvtt) & APIC_lvt_masked;
}

#line 418 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline void
Apic::timer_set_periodic()
{
  Unsigned32 tmp_val = reg_read(APIC_lvtt);
  tmp_val |= APIC_lvt_timer_periodic;
  reg_write(APIC_lvtt, tmp_val);
}

#line 427 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline void
Apic::timer_set_one_shot()
{
  Unsigned32 tmp_val = reg_read(APIC_lvtt);
  tmp_val &= ~APIC_lvt_timer_periodic;
  reg_write(APIC_lvtt, tmp_val);
}

#line 436 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline void
Apic::timer_assign_irq_vector(unsigned vector)
{
  Unsigned32 tmp_val = reg_read(APIC_lvtt);
  tmp_val &= 0xffffff00;
  tmp_val |= vector;
  reg_write(APIC_lvtt, tmp_val);
}

#line 446 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline void
Apic::irq_ack()
{
  reg_read(APIC_spiv);
  reg_write(APIC_eoi, 0);
}

#line 501 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline int
Apic::have_pcint()
{
  return (present && (get_max_lvt() >= 4));
}

#line 508 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline int
Apic::have_tsint()
{
  return (present && (get_max_lvt() >= 5));
}

#line 552 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline void
Apic::tpr(unsigned prio)
{ reg_write(APIC_tpr, prio); }

#line 557 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline unsigned
Apic::tpr()
{ return reg_read(APIC_tpr); }

#line 699 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline int
Apic::is_present()
{
  return present;
}

#endif // apic_h
