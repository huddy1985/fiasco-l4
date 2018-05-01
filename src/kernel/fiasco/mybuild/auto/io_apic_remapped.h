// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef io_apic_remapped_h
#define io_apic_remapped_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"

#include "io_apic.h"

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
namespace Intel { class Io_mmu; }
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"

class Io_apic_remapped : public Io_apic
{
public:
  Io_apic_remapped(Unsigned64 phys, unsigned gsi_base,
                   Intel::Io_mmu *iommu, Unsigned16 src_id)
  : Io_apic(phys, gsi_base), _iommu(iommu), _src_id(src_id)
  {}

private:
  Intel::Io_mmu *_iommu;
  Unsigned16 _src_id;

public:  
#line 259 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
  bool
  alloc(Irq_base *irq, Mword pin) override;
  
#line 286 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
  void
  unbind(Irq_base *irq) override;
  
#line 294 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
  int
  set_mode(Mword pin, Mode mode) override;
  
#line 318 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
  void
  set_cpu(Mword pin, Cpu_number cpu) override;
  
#line 336 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
  static FIASCO_INIT
  bool
  init_apics();
  
#line 443 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"
  inline char const *
  chip_type() const override;
};
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"

// -----------------------------------------------------------------


//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 441 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic_remapped.cpp"


inline char const *
Io_apic_remapped::chip_type() const 
{ return "rIO-APIC"; }

#endif // io_apic_remapped_h
