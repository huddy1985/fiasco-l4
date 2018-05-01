// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "uart.h"
#include "uart_i.h"

#line 120 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/uart.cpp"

//---------------------------------------------------------------------------


#line 113 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/uart.cpp"


Mword
Uart::get_attributes() const
{
  return UART | IN | OUT;
}

#line 191 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/uart.cpp"


void Uart::enable_rcv_irq()
{
  uart()->enable_rx_irq(true);
}

#line 197 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/uart.cpp"


void Uart::disable_rcv_irq()
{
  uart()->enable_rx_irq(false);
}

#line 203 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/uart.cpp"


void Uart::irq_ack()
{
  uart()->irq_ack();
}
