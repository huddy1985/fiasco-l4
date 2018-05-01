// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kernel_uart_h
#define kernel_uart_h
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"

#include "uart.h"
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include "std_macros.h"
#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include "pm.h"

//
// INTERFACE definition follows 
//

#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"

class Kernel_uart

: public Uart, public Pm_object
{
public:
  enum Init_mode
  {
    Init_before_mmu,
    Init_after_mmu
  };
  Kernel_uart();
  static void enable_rcv_irq();

#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"
private:

private:
  /**
   * Prototype for the UART specific startup implementation.
   * @param uart, the instantiation to start.
   * @param port, the com port number.
   */
  bool startup(unsigned port, int irq=-1);

  static bool init_for_mode(Init_mode init_mode);

public:  
#line 60 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"
  static FIASCO_CONST
  Uart *
  uart();
  
#line 72 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"
  static bool
  init(Init_mode init_mode = Init_before_mmu);
  
#line 89 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"
  void
  setup();
  
#line 119 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"
  void
  pm_on_suspend(Cpu_number cpu);
  
#line 131 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"
  void
  pm_on_resume(Cpu_number cpu);
};
#line 36 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"

//---------------------------------------------------------------------------


#endif // kernel_uart_h
