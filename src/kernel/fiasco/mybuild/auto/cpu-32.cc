// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "cpu.h"
#include "cpu_i.h"

#line 129 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"

//----------------------------------------------------------------------------

#line 140 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"

extern "C" void entry_vec08_dbf();
#line 142 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
extern "C" Address dbf_stack_top;
#line 229 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"

extern "C" void entry_sys_fast_ipc_c (void);

#line 143 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"

FIASCO_INIT_CPU
void
Cpu::init_tss_dbf(Address tss_dbf_mem, Address kdir)
{
  tss_dbf = reinterpret_cast<Tss*>(tss_dbf_mem);

  gdt->set_entry_byte(Gdt::gdt_tss_dbf / 8, tss_dbf_mem, sizeof(Tss) - 1,
		      Gdt_entry::Access_kernel | Gdt_entry::Access_tss |
		      Gdt_entry::Accessed, 0);

  tss_dbf->_cs     = Gdt::gdt_code_kernel;
  tss_dbf->_ss     = Gdt::gdt_data_kernel;
  tss_dbf->_ds     = Gdt::gdt_data_kernel;
  tss_dbf->_es     = Gdt::gdt_data_kernel;
  tss_dbf->_fs     = Gdt::gdt_data_kernel;
  tss_dbf->_gs     = Gdt::gdt_data_kernel;
  tss_dbf->_eip    = (Address)entry_vec08_dbf;
  tss_dbf->_esp    = (Address)&dbf_stack_top;
  tss_dbf->_ldt    = 0;
  tss_dbf->_eflags = 0x00000082;
  tss_dbf->_cr3    = kdir;
  tss_dbf->_io_bit_map_offset = 0x8000;
}

#line 167 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"


FIASCO_INIT_CPU
void
Cpu::init_tss(Address tss_mem, size_t tss_size)
{
  tss = reinterpret_cast<Tss*>(tss_mem);

  gdt->set_entry_byte(Gdt::gdt_tss / 8, tss_mem, tss_size,
		      Gdt_entry::Access_kernel | Gdt_entry::Access_tss, 0);

  tss->set_ss0(Gdt::gdt_data_kernel);
  assert(Mem_layout::Io_bitmap - tss_mem
         < (1 << (sizeof(tss->_io_bit_map_offset) * 8)));
  tss->_io_bit_map_offset = Mem_layout::Io_bitmap - tss_mem;
}

#line 183 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"


FIASCO_INIT_CPU
void
Cpu::init_gdt(Address gdt_mem, Address user_max)
{
  gdt = reinterpret_cast<Gdt*>(gdt_mem);

  // make sure kernel cs/ds and user cs/ds are placed in the same
  // cache line, respectively; pre-set all "accessed" flags so that
  // the CPU doesn't need to do this later

  gdt->set_entry_4k(Gdt::gdt_code_kernel / 8, 0, 0xffffffff,
                    Gdt_entry::Access_kernel |
                    Gdt_entry::Access_code_read |
                    Gdt_entry::Accessed, Gdt_entry::Size_32);
  gdt->set_entry_4k(Gdt::gdt_data_kernel / 8, 0, 0xffffffff,
                    Gdt_entry::Access_kernel |
                    Gdt_entry::Access_data_write |
                    Gdt_entry::Accessed, Gdt_entry::Size_32);
  gdt->set_entry_4k(Gdt::gdt_code_user / 8, 0, user_max,
		    Gdt_entry::Access_user |
		    Gdt_entry::Access_code_read |
		    Gdt_entry::Accessed, Gdt_entry::Size_32);
  gdt->set_entry_4k(Gdt::gdt_data_user / 8, 0, user_max,
                    Gdt_entry::Access_user |
                    Gdt_entry::Access_data_write |
                    Gdt_entry::Accessed, Gdt_entry::Size_32);
}

#line 220 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"



void
Cpu::set_fast_entry(void (*func)(void))
{
  if (sysenter())
    set_sysenter(func);
}

#line 240 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"

FIASCO_INIT_AND_PM
void
Cpu::init_sysenter()
{
  if (sysenter())
    {
      _sysenter_eip = (Mword)entry_sys_fast_ipc_c;
      setup_sysenter();
    }
}
