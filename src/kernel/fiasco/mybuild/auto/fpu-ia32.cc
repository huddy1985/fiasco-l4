// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "fpu.h"
#include "fpu_i.h"


#line 25 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/fpu-ia32.cpp"


void
Fpu::init_xsave(Cpu_number cpu)
{
  Unsigned32 eax, ebx, ecx, edx;

  Cpu::cpus.cpu(cpu).cpuid(0xd, 0, &eax, &ebx, &ecx, &edx);

  // allow safe features: x87, SSE, AVX and AVX512
  Fpu::fpu.cpu(cpu)._xcr0 = (((Unsigned64)edx << 32) | eax) & 0xe7;

  // enable xsave features
  Cpu::cpus.cpu(cpu).set_cr4(Cpu::cpus.cpu(cpu).get_cr4() | CR4_OSXSAVE);
  Cpu::xsetbv(Fpu::fpu.cpu(cpu).get_xcr0(), 0);
}

#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/fpu-ia32.cpp"


void
Fpu::init_disable()
{
  // disable Coprocessor Emulation to allow exception #7/NM on TS
  // enable Numeric Error (exception #16/MF, native FPU mode)
  // enable Monitor Coprocessor
  Cpu::set_cr0((Cpu::get_cr0() & ~CR0_EM) | CR0_NE | CR0_MP);
}
