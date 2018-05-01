// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "kmem.h"
#include "kmem_i.h"

#line 183 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


Unsigned8    *Kmem::io_bitmap_delimiter;
#line 186 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
Address Kmem::kphys_start, Kmem::kphys_end;
#line 187 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
Device_map Kmem::dev_map;
#line 458 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


//---------------------------------------------------------------------------

#line 464 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


//--------------------------------------------------------------------------

#line 481 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

// static class variables
Kpdir *Mem_layout::kdir;
#line 508 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


//--------------------------------------------------------------------------

#line 523 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

unsigned long Kmem::tss_mem_pm;
#line 525 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"
cxx::Simple_alloc Kmem::tss_mem_vm;
#line 552 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

//--------------------------------------------------------------------------

#line 562 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

//--------------------------------------------------------------------------


#line 100 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


void
Device_map::init()
{
  for (unsigned i = 0; i < Max; ++i)
    _map[i] = ~0UL;
}

#line 108 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


unsigned
Device_map::lookup_idx(Address phys)
{
  Address p = phys & (~0UL << Config::SUPERPAGE_SHIFT);
  for (unsigned i = 0; i < Max; ++i)
    if (p == _map[i])
      return i;

  return ~0U;
}

#line 134 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


Address
Device_map::map(Address phys, bool /*cache*/)
{
  unsigned idx = lookup_idx(phys);
  if (idx != ~0U)
    return (Virt_base + idx * Config::SUPERPAGE_SIZE)
           | (phys & ~(~0UL << Config::SUPERPAGE_SHIFT));

  Address p = phys & (~0UL << Config::SUPERPAGE_SHIFT);
  Kmem_alloc *const alloc = Kmem_alloc::allocator();
  for (unsigned i = 0; i < Max; ++i)
    if (_map[i] == ~0UL)
      {
	Kmem::kdir->map(p,
                        Virt_addr(Virt_base + (i * Config::SUPERPAGE_SIZE)),
                        Virt_size(Config::SUPERPAGE_SIZE),
                        Pt_entry::Dirty | Pt_entry::Writable
                        | Pt_entry::Referenced,
                        Pt_entry::super_level(), false, pdir_alloc(alloc));
	_map[i] = p;

	return (Virt_base + (i * Config::SUPERPAGE_SIZE))
	       | (phys & ~(~0UL << Config::SUPERPAGE_SHIFT));
      }

  return ~0UL;
}

#line 169 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


void
Device_map::unmap(void const *phys)
{
  unsigned idx = lookup_idx((Address)phys);
  if (idx == ~0U)
    return;

  Address v = Virt_base + (idx * Config::SUPERPAGE_SIZE);

  Kmem::kdir->unmap(Virt_addr(v), Virt_size(Config::SUPERPAGE_SIZE),
                    Pdir::Depth, false);
}

#line 218 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


// Only used for initialization and kernel debugger

Address
Kmem::map_phys_page_tmp(Address phys, Mword idx)
{
  unsigned long pte = cxx::mask_lsb(phys, Pdir::page_order_for_level(Pdir::Depth));
  Address virt;

  switch (idx)
    {
    case 0:  virt = Mem_layout::Kmem_tmp_page_1; break;
    case 1:  virt = Mem_layout::Kmem_tmp_page_2; break;
    default: return ~0UL;
    }

  static unsigned long tmp_phys_pte[2] = { ~0UL, ~0UL };

  if (pte != tmp_phys_pte[idx])
    {
      // map two consecutive pages as to be able to access
      map_phys_page(phys,          virt,          false, true);
      map_phys_page(phys + 0x1000, virt + 0x1000, false, true);
      tmp_phys_pte[idx] = pte;
    }

  return virt + phys - pte;
}

#line 282 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


//
// helper functions
//

// Establish a 4k-mapping

void
Kmem::map_phys_page(Address phys, Address virt,
                    bool cached, bool global, Address *offs)
{
  auto i = kdir->walk(Virt_addr(virt), Pdir::Depth, false,
                      pdir_alloc(Kmem_alloc::allocator()));
  Mword pte = phys & Config::PAGE_MASK;

  assert(i.level == Pdir::Depth);

  i.set_page(pte, Pt_entry::Writable | Pt_entry::Referenced | Pt_entry::Dirty
                  | (cached ? 0 : (Pt_entry::Write_through | Pt_entry::Noncacheable))
                  | (global ? Pt_entry::global() : 0));
  Mem_unit::tlb_flush(virt);

  if (offs)
    *offs = phys - pte;
}

#line 308 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"



Address
Kmem::mmio_remap(Address phys)
{
  Address offs;
  Address va = alloc_io_vmem(Config::PAGE_SIZE);

  if (!va)
    return ~0UL;

  Kmem::map_phys_page(phys, va, false, true, &offs);
  return va + offs;
}

#line 323 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

FIASCO_INIT
void
Kmem::init_mmu()
{
  dev_map.init();
  Kmem_alloc *const alloc = Kmem_alloc::allocator();

  kdir = (Kpdir*)alloc->alloc(Config::PAGE_SHIFT);
  memset (kdir, 0, Config::PAGE_SIZE);

  unsigned long cpu_features = Cpu::get_features();
  bool superpages = cpu_features & FEAT_PSE;

  printf("Superpages: %s\n", superpages?"yes":"no");

  Pt_entry::have_superpages(superpages);
  if (superpages)
    Cpu::set_cr4(Cpu::get_cr4() | CR4_PSE);

  if (cpu_features & FEAT_PGE)
    {
      Pt_entry::enable_global();
      Cpu::set_cr4 (Cpu::get_cr4() | CR4_PGE);
    }

  // set up the kernel mapping for physical memory.  mark all pages as
  // referenced and modified (so when touching the respective pages
  // later, we save the CPU overhead of marking the pd/pt entries like
  // this)

  // we also set up a one-to-one virt-to-phys mapping for two reasons:
  // (1) so that we switch to the new page table early and re-use the
  //     segment descriptors set up by boot_cpu.cc.  (we'll set up our
  //     own descriptors later.) we only need the first 4MB for that.
  // (2) a one-to-one phys-to-virt mapping in the kernel's page directory
  //     sometimes comes in handy (mostly useful for debugging)

  // first 4MB page
  kdir->map(0, Virt_addr(0UL), Virt_size(4 << 20),
      Pt_entry::Dirty | Pt_entry::Writable | Pt_entry::Referenced,
      Pt_entry::super_level(), false, pdir_alloc(alloc));


  kdir->map(Mem_layout::Kernel_image_phys,
            Virt_addr(Mem_layout::Kernel_image),
            Virt_size(Config::SUPERPAGE_SIZE),
            Pt_entry::Dirty | Pt_entry::Writable | Pt_entry::Referenced
            | Pt_entry::global(), Pt_entry::super_level(), false,
            pdir_alloc(alloc));

   if (!Mem_layout::Adap_in_kernel_image)
     kdir->map(Mem_layout::Adap_image_phys,
               Virt_addr(Mem_layout::Adap_image),
               Virt_size(Config::SUPERPAGE_SIZE),
               Pt_entry::Dirty | Pt_entry::Writable | Pt_entry::Referenced
               | Pt_entry::global(), Pt_entry::super_level(),
               false, pdir_alloc(alloc));

  // map the last 64MB of physical memory as kernel memory
  kdir->map(Mem_layout::pmem_to_phys(Mem_layout::Physmem),
            Virt_addr(Mem_layout::Physmem), Virt_size(Mem_layout::pmem_size),
            Pt_entry::Writable | Pt_entry::Referenced | Pt_entry::global(),
            Pt_entry::super_level(), false, pdir_alloc(alloc));

  // The service page directory entry points to an universal usable
  // page table which is currently used for the Local APIC and the
  // jdb adapter page.
  assert((Mem_layout::Service_page & ~Config::SUPERPAGE_MASK) == 0);

  kdir->walk(Virt_addr(Mem_layout::Service_page), Pdir::Depth,
             false, pdir_alloc(alloc));

  // kernel mode should acknowledge write-protected page table entries
  Cpu::set_cr0(Cpu::get_cr0() | CR0_WP);

  // now switch to our new page table
  Cpu::set_pdbr(Mem_layout::pmem_to_phys(kdir));

  setup_global_cpu_structures(superpages);


  // did we really get the first byte ??
  assert((reinterpret_cast<Address>(io_bitmap_delimiter)
          & ~Config::PAGE_MASK) == 0);
  *io_bitmap_delimiter = 0xff;
}

#line 410 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


void
Kmem::setup_cpu_structures(Cpu &cpu, cxx::Simple_alloc *cpu_alloc,
                           cxx::Simple_alloc *tss_alloc)
{
  // now initialize the global descriptor table
  cpu.init_gdt((Address)cpu_alloc->alloc_bytes(Gdt::gdt_max, 0x10), user_max());

  // Allocate the task segment as the last thing from cpu_page_vm
  // because with IO protection enabled the task segment includes the
  // rest of the page and the following IO bitmap (2 pages).
  //
  // Allocate additional 256 bytes for emergency stack right beneath
  // the tss. It is needed if we get an NMI or debug exception at
  // entry_sys_fast_ipc/entry_sys_fast_ipc_c/entry_sys_fast_ipc_log.
  Address tss_mem = (Address)tss_alloc->alloc_bytes(sizeof(Tss) + 256, 0x10);
  assert(tss_mem + sizeof(Tss) + 256 < Mem_layout::Io_bitmap);
  tss_mem += 256;
  assert(tss_mem >= Mem_layout::Io_bitmap - 0x100000);

  // this is actually tss_size + 1, including the io_bitmap_delimiter byte
  size_t tss_size;
  tss_size = Mem_layout::Io_bitmap + (Mem_layout::Io_port_max / 8) - tss_mem;

  assert(tss_size < 0x100000); // must fit into 20 Bits

  cpu.init_tss(tss_mem, tss_size);

  // force GDT... to memory before loading the registers
  asm volatile ( "" : : : "memory" );

  // set up the x86 CPU's memory model
  cpu.set_gdt();
  cpu.set_ldt(0);

  cpu.set_ds(Gdt::data_segment());
  cpu.set_es(Gdt::data_segment());
  cpu.set_ss(Gdt::gdt_data_kernel | Gdt::Selector_kernel);
  cpu.set_fs(Gdt::gdt_data_user   | Gdt::Selector_user);
  cpu.set_gs(Gdt::gdt_data_user   | Gdt::Selector_user);
  cpu.set_cs();

  // and finally initialize the TSS
  cpu.set_tss();

  init_cpu_arch(cpu, cpu_alloc);
}

#line 545 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


Address
Kmem::get_realmode_startup_pdbr()
{
  return Mem_layout::pmem_to_phys(Kmem::dir());
}

#line 631 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"

FIASCO_INIT_CPU
void
Kmem::init_cpu(Cpu &cpu)
{
  cxx::Simple_alloc cpu_mem_vm(Kmem_alloc::allocator()->unaligned_alloc(1024), 1024);
  if (Config::Warn_level >= 2)
    printf("Allocate cpu_mem @ %p\n", cpu_mem_vm.block());

  // now switch to our new page table
  Cpu::set_pdbr(Mem_layout::pmem_to_phys(kdir));

  setup_cpu_structures(cpu, &cpu_mem_vm, &tss_mem_vm);
}
