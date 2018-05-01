// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "kernel_uart.h"
#include "kernel_uart_i.h"

#line 56 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"

static Static_object<Filter_console> _fcon;
#line 58 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"
static Static_object<Kernel_uart> _kernel_uart;

#line 59 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"

FIASCO_CONST
Uart *
Kernel_uart::uart()
{ return _kernel_uart; }

#line 70 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"


bool
Kernel_uart::init(Init_mode init_mode)
{
  if (!init_for_mode(init_mode))
    return false;

  if (Koptions::o()->opt(Koptions::F_noserial)) // do not use serial uart
    return true;

  _kernel_uart.construct();
  _fcon.construct(_kernel_uart);

  Kconsole::console()->register_console(_fcon, 0);
  return true;
}

#line 87 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"


void
Kernel_uart::setup()
{
  unsigned           n = Config::default_console_uart_baudrate;
  Uart::TransferMode m = Uart::MODE_8N1;
  unsigned long long p = Config::default_console_uart;
  int                i = -1;

  if (Koptions::o()->opt(Koptions::F_uart_baud))
    n = Koptions::o()->uart.baud;

  if (Koptions::o()->opt(Koptions::F_uart_base))
    p = Koptions::o()->uart.base_address;

  if (Koptions::o()->opt(Koptions::F_uart_irq))
    i = Koptions::o()->uart.irqno;

  if (!startup(p, i))
    printf("Comport/base 0x%04llx is not accepted by the uart driver!\n", p);
  else if (!change_mode(m, n))
    panic("Something is wrong with the baud rate (%u)!\n", n);
}

#line 111 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"


Kernel_uart::Kernel_uart()
{
  setup();
  register_pm(Cpu_number::boot_cpu());
}

#line 118 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"

void
Kernel_uart::pm_on_suspend(Cpu_number cpu)
{
  (void)cpu;
  assert (cpu == Cpu_number::boot_cpu());

  uart()->state(Console::DISABLED);

  if(Config::serial_esc != Config::SERIAL_ESC_NOIRQ)
    uart()->disable_rcv_irq();
}

#line 130 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"

void
Kernel_uart::pm_on_resume(Cpu_number cpu)
{
  (void)cpu;
  assert (cpu == Cpu_number::boot_cpu());
  static_cast<Kernel_uart*>(Kernel_uart::uart())->setup();
  uart()->state(Console::ENABLED);

  if(Config::serial_esc != Config::SERIAL_ESC_NOIRQ)
    uart()->enable_rcv_irq();
}

#line 159 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"



void
Kernel_uart::enable_rcv_irq()
{
  static Kuart_irq uart_irq;
  if (Irq_mgr::mgr->alloc(&uart_irq, uart()->irq()))
    {
      uart_irq.unmask();
      uart()->enable_rcv_irq();
    }
}
