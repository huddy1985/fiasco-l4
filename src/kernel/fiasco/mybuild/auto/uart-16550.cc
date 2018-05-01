// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "uart.h"
#include "uart_i.h"

#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/uart-16550.cpp"

Static_object<L4::Uart_16550> _the_uart;

#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/uart-16550.cpp"


Uart::Uart() : Console(DISABLED) {}

#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/uart-16550.cpp"

bool
Uart::startup(const L4::Io_register_block *r, int irq,
              Unsigned32 base_baud)
{
  _irq = irq;
  _the_uart.construct(base_baud, L4::Uart_16550::F_skip_init);
  if (!_the_uart->startup(r))
    return false;

  add_state(ENABLED);
  return true;
}

#line 39 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/uart-16550.cpp"

L4::Uart *Uart::uart()
{
  return _the_uart.get();
}
