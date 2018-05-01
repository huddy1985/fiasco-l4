// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kernel_uart_i_h
#define kernel_uart_i_h
#line 39 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"

#include <cassert>
#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include <cstring>
#line 42 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include <cstdlib>
#line 43 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include <cstdio>
#line 44 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"

#include "filter_console.h"
#line 46 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include "irq_chip.h"
#line 47 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include "irq_mgr.h"
#line 48 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include "kdb_ke.h"
#line 49 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include "kernel_console.h"
#line 50 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include "uart.h"
#line 51 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include "config.h"
#line 52 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include "kip.h"
#line 53 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include "koptions.h"
#line 54 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include "panic.h"
#line 55 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"
#include "vkey.h"
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart-libuart.cpp"

#include "kmem.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart-libuart.cpp"
#include "io_regblock.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart-libuart.cpp"

#include "io_regblock_port.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart-libuart.cpp"
#include "types.h"
#line 142 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart.cpp"


class Kuart_irq : public Irq_base
{
public:
  Kuart_irq() { hit_func = &handler_wrapper<Kuart_irq>; }
  void switch_mode(bool) {}
  void handle(Upstream_irq const *ui)
  {
    Kernel_uart::uart()->irq_ack();
    mask_and_ack();
    ui->ack();
    unmask();
    if (!Vkey::check_())
      kdb_ke("IRQ ENTRY");
  }
};

#endif // kernel_uart_i_h
