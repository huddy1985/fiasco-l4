// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef timer_tick_h
#define timer_tick_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timer_tick.cpp"

#include "irq_chip.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timer_tick.cpp"
#include "thread.h"
#line 42 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timer_tick.cpp"

#include "tb_entry.h"

//
// INTERFACE definition follows 
//

#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timer_tick.cpp"

class Timer_tick : public Irq_base
{
public:
  enum Mode
  {
    Any_cpu, ///< Might hit on any CPU
    Sys_cpu, ///< Hit only on the CPU that manages the system time
    App_cpu, ///< Hit only on application CPUs
  };
  /// Create a timer IRQ object
  explicit Timer_tick(Mode mode)
  {
    switch (mode)
      {
      case Any_cpu: set_hit(&handler_all); break;
      case Sys_cpu: set_hit(&handler_sys_time); break;
      case App_cpu: set_hit(&handler_app); break;
      }
  }

  static void setup(Cpu_number cpu);
  static void enable(Cpu_number cpu);
  static void disable(Cpu_number cpu);

  static Timer_tick *boot_cpu_timer_tick();

protected:
  static bool allocate_irq(Irq_base *irq, unsigned irqnum);

private:
  // we do not support triggering modes
  void switch_mode(bool) {}

#line 44 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timer_tick.cpp"
private:

public:
  struct Log : public Tb_entry
  {
    Irq_base *obj;
    Address user_ip;
    void print(String_buffer *) const;
  };

public:  
#line 86 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timer_tick.cpp"
  static inline void
  handler_all(Irq_base *_s, Upstream_irq const *ui);
  
#line 94 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timer_tick.cpp"
  static inline void
  handler_sys_time(Irq_base *_s, Upstream_irq const *ui);
  
#line 102 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timer_tick.cpp"
  static inline void
  handler_app(Irq_base *_s, Upstream_irq const *ui);
  
#line 135 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timer_tick.cpp"
  inline void
  log_timer();
  
#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/timer_tick-apic.cpp"
  static inline void
  ack();
  
#line 34 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/timer_tick-apic.cpp"
  static void
  set_vectors_stop();

private:  
#line 66 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timer_tick.cpp"
  static inline void
  handle_timer(Irq_base *_s, Upstream_irq const *ui,
                           Thread *t, Cpu_number cpu);
};
#line 39 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timer_tick.cpp"

// ------------------------------------------------------------------------

#line 55 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timer_tick.cpp"

// ------------------------------------------------------------------------

#line 126 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timer_tick.cpp"

#line 55 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/timer_tick-apic.cpp"
// We are entering with disabled interrupts!
extern "C" FIASCO_FASTCALL
void
thread_timer_interrupt(Address ip);

#line 64 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/timer_tick-apic.cpp"
/** Extra version of timer interrupt handler which is used when the jdb is
    active to prevent busy waiting. */
extern "C"
void
thread_timer_interrupt_stop(void);

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 58 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timer_tick.cpp"

#include "timer.h"
#line 60 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timer_tick.cpp"

#include "kdb_ke.h"
#line 62 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timer_tick.cpp"
#include "kernel_console.h"
#line 63 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timer_tick.cpp"
#include "vkey.h"
#line 122 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timer_tick.cpp"

#include "logdefs.h"
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/timer_tick-apic.cpp"

#include "apic.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 64 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timer_tick.cpp"



inline void
Timer_tick::handle_timer(Irq_base *_s, Upstream_irq const *ui,
                         Thread *t, Cpu_number cpu)
{
  Timer_tick *self = nonull_static_cast<Timer_tick *>(_s);
  self->ack();
  if (ui)
    ui->ack();
  Timer::update_system_clock(cpu);
  if (Config::esc_hack && cpu == Cpu_number::boot_cpu())
    {
      if (Kconsole::console()->char_avail() && !Vkey::check_())
        kdb_ke("SERIAL_ESC");
    }
  self->log_timer();
  t->handle_timer_interrupt();
}

#line 84 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timer_tick.cpp"


inline void
Timer_tick::handler_all(Irq_base *_s, Upstream_irq const *ui)
{
  Thread *t = current_thread();
  handle_timer(_s, ui, t, current_cpu());
}

#line 92 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timer_tick.cpp"


inline void
Timer_tick::handler_sys_time(Irq_base *_s, Upstream_irq const *ui)
{
  // assume the boot CPU to be the CPU that manages the system time
  handle_timer(_s, ui, current_thread(), Cpu_number::boot_cpu());
}

#line 100 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timer_tick.cpp"


inline void
Timer_tick::handler_app(Irq_base *_s, Upstream_irq const *ui)
{
  Timer_tick *self = nonull_static_cast<Timer_tick *>(_s);
  self->ack();
  ui->ack();
  self->log_timer();
  current_thread()->handle_timer_interrupt();
}

#line 133 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/timer_tick.cpp"


inline void
Timer_tick::log_timer()
{
  Context *c = current();
  LOG_TRACE("Timer IRQs (kernel scheduling)", "timer", c, Log,
      l->user_ip  = c->regs()->ip();
      l->obj      = this;
  );
}

#line 25 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/timer_tick-apic.cpp"


inline void
Timer_tick::ack()
{
  Apic::irq_ack();
}

#endif // timer_tick_h
