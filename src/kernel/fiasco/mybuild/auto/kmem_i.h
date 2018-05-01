// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kmem_i_h
#define kmem_i_h

//
// IMPLEMENTATION of inline functions follows
//


#line 565 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kmem-ia32.cpp"


inline void
Kmem::setup_global_cpu_structures(bool superpages)
{
  auto *alloc = Kmem_alloc::allocator();
  assert((Mem_layout::Io_bitmap & ~Config::SUPERPAGE_MASK) == 0);

  enum { Tss_mem_size = 0x10 + Config::Max_num_cpus * (sizeof(Tss) + 256) };

  /* Per-CPU TSS required to use IO-bitmap for more CPUs */
  static_assert(Tss_mem_size < 0x10000, "Too many CPUs configured.");

  unsigned tss_mem_size = Tss_mem_size;

  if (tss_mem_size < Config::PAGE_SIZE)
    tss_mem_size = Config::PAGE_SIZE;

  tss_mem_pm = Mem_layout::pmem_to_phys(alloc->unaligned_alloc(tss_mem_size));

  printf("Kmem:: TSS mem at %lx (%uBytes)\n", tss_mem_pm, tss_mem_size);

  if (superpages
      && Config::SUPERPAGE_SIZE - (tss_mem_pm & ~Config::SUPERPAGE_MASK) < 0x10000)
    {
      // can map as 4MB page because the cpu_page will land within a
      // 16-bit range from io_bitmap
      auto e = kdir->walk(Virt_addr(Mem_layout::Io_bitmap - Config::SUPERPAGE_SIZE),
                          Pdir::Super_level, false, pdir_alloc(alloc));

      e.set_page(tss_mem_pm & Config::SUPERPAGE_MASK,
                 Pt_entry::Writable | Pt_entry::Referenced
                 | Pt_entry::Dirty | Pt_entry::global());

      tss_mem_vm = cxx::Simple_alloc(
          (tss_mem_pm & ~Config::SUPERPAGE_MASK)
          + (Mem_layout::Io_bitmap - Config::SUPERPAGE_SIZE),
          tss_mem_size);
    }
  else
    {
      unsigned i;
      for (i = 0; (i << Config::PAGE_SHIFT) < tss_mem_size; ++i)
        {
          auto e = kdir->walk(Virt_addr(Mem_layout::Io_bitmap - Config::PAGE_SIZE * (i+1)),
                              Pdir::Depth, false, pdir_alloc(alloc));

          e.set_page(tss_mem_pm + i * Config::PAGE_SIZE,
                     Pt_entry::Writable | Pt_entry::Referenced | Pt_entry::Dirty
                     | Pt_entry::global());
        }

      tss_mem_vm = cxx::Simple_alloc(
          Mem_layout::Io_bitmap - Config::PAGE_SIZE * i,
          tss_mem_size);
    }

  // the IO bitmap must be followed by one byte containing 0xff
  // if this byte is not present, then one gets page faults
  // (or general protection) when accessing the last port
  // at least on a Pentium 133.
  //
  // Therefore we write 0xff in the first byte of the cpu_page
  // and map this page behind every IO bitmap
  io_bitmap_delimiter = tss_mem_vm.alloc<Unsigned8>();
}

#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/kmem-ia32-32.cpp"

inline FIASCO_INIT_CPU
void
Kmem::init_cpu_arch(Cpu &cpu, cxx::Simple_alloc *cpu_mem)
{
  // allocate the task segment for the double fault handler
  cpu.init_tss_dbf((Address)cpu_mem->alloc<Tss>(1, 0x10),
                   Mem_layout::pmem_to_phys(Kmem::dir()));

  cpu.init_sysenter();
}

#endif // kmem_i_h
