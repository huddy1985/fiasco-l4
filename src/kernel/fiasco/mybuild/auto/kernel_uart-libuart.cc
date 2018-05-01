// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "kernel_uart.h"
#include "kernel_uart_i.h"

#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart-libuart.cpp"

//------------------------------------------------------------------------

#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart-libuart.cpp"

namespace {

union Regs
{
  Static_object<L4::Io_register_block_port> io;
  Static_object<L4::Io_register_block_mmio> mem;
  Static_object<L4::Io_register_block_mmio_fixed_width<Unsigned64> > mem64;
  Static_object<L4::Io_register_block_mmio_fixed_width<Unsigned32> > mem32;
  Static_object<L4::Io_register_block_mmio_fixed_width<Unsigned16> > mem16;
};

static bool
setup_uart_io_port(Regs *regs, Address base, int irq)
{
  regs->io.construct(base);
  return Kernel_uart::uart()->startup(regs->io.get(), irq,
                                      Koptions::o()->uart.base_baud);
}

}

#line 57 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart-libuart.cpp"


bool
Kernel_uart::init_for_mode(Init_mode init_mode)
{
  if (Koptions::o()->uart.access_type == Koptions::Uart_type_ioport)
    return init_mode == Init_before_mmu;
  else
    return init_mode == Init_after_mmu;
}

#line 67 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/kernel_uart-libuart.cpp"


bool Kernel_uart::startup(unsigned, int irq)
{
  static Regs regs;

  if (Koptions::o()->opt(Koptions::F_uart_base))
    {
      Address base = Koptions::o()->uart.base_address;
      switch (Koptions::o()->uart.access_type)
        {
        case Koptions::Uart_type_ioport:
          return setup_uart_io_port(&regs, base, irq);

        case Koptions::Uart_type_mmio:
            {
              L4::Io_register_block *r = 0;

              switch (Koptions::o()->uart.reg_shift)
                {
                case 0: // no shift use natural access width
                  r = regs.mem.construct(Kmem::mmio_remap(base),
                                         Koptions::o()->uart.reg_shift);
                  break;
                case 1: // 1 bit shift, assume fixed 16bit access width
                  r = regs.mem16.construct(Kmem::mmio_remap(base),
                                           Koptions::o()->uart.reg_shift);
                  break;
                case 2: // 2 bit shift, assume fixed 32bit access width
                  r = regs.mem32.construct(Kmem::mmio_remap(base),
                                           Koptions::o()->uart.reg_shift);
                  break;
                case 3: // 3 bit shift, assume fixed 64bit access width
                  r = regs.mem32.construct(Kmem::mmio_remap(base),
                                           Koptions::o()->uart.reg_shift);
                  break;
                default:
                  panic("UART: illegal reg shift value: %d",
                        Koptions::o()->uart.reg_shift);
                  break;
                }
              return uart()->startup(r, irq, Koptions::o()->uart.base_baud);
            }
        default:
          return false;
        }
    }

  return false;
}
