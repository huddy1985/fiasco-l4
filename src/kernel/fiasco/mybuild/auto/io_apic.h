// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef io_apic_h
#define io_apic_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

#include <types.h>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
#include "initcalls.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
#include <spin_lock.h>
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
#include "irq_chip_ia32.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
#include <cxx/bitfield>
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
#include "irq_mgr.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
#include "pm.h"

//
// INTERFACE definition follows 
//

#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

class Acpi_madt;
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

class Io_apic_entry
{
  friend class Io_apic;
private:
  Unsigned64 _e;

public:
  enum Delivery { Fixed, Lowest_prio, SMI, NMI = 4, INIT, ExtINT = 7 };
  enum Dest_mode { Physical, Logical };
  enum Polarity { High_active, Low_active };
  enum Trigger { Edge, Level };

  Io_apic_entry() {}
  Io_apic_entry(Unsigned8 vector, Delivery d, Dest_mode dm, Polarity p,
                Trigger t, Unsigned32 dest)
    : _e(  vector_bfm_t::val(vector) | delivery_bfm_t::val(d) | mask_bfm_t::val(1)
         | dest_mode_bfm_t::val(dm)  | polarity_bfm_t::val(p)
         | trigger_bfm_t::val(t)     | dest_bfm_t::val(dest >> 24))
  {}

  CXX_BITFIELD_MEMBER( 0,  7, vector, _e);
  CXX_BITFIELD_MEMBER( 8, 10, delivery, _e);
  CXX_BITFIELD_MEMBER(11, 11, dest_mode, _e);
  CXX_BITFIELD_MEMBER(13, 13, polarity, _e);
  CXX_BITFIELD_MEMBER(15, 15, trigger, _e);
  CXX_BITFIELD_MEMBER(16, 16, mask, _e);
  // support for IRQ remapping
  CXX_BITFIELD_MEMBER(48, 48, format, _e);
  // support for IRQ remapping
  CXX_BITFIELD_MEMBER(49, 63, irt_index, _e);
  CXX_BITFIELD_MEMBER(56, 63, dest, _e);
};
#line 45 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


class Io_apic : public Irq_chip_icu, protected Irq_chip_ia32
{
  friend class Jdb_io_apic_module;
  friend class Irq_chip_ia32;
public:
  unsigned nr_irqs() const override { return Irq_chip_ia32::nr_irqs(); }
  bool reserve(Mword pin) override { return Irq_chip_ia32::reserve(pin); }
  Irq_base *irq(Mword pin) const override { return Irq_chip_ia32::irq(pin); }

private:
  struct Apic
  {
    Unsigned32 volatile adr;
    Unsigned32 dummy[3];
    Unsigned32 volatile data;

    unsigned num_entries();
    Mword read(int reg);
    void modify(int reg, Mword set_bits, Mword del_bits);
    void write(int reg, Mword value);
  } __attribute__((packed));

  Apic *_apic;
  mutable Spin_lock<> _l;
  unsigned _offset;
  Io_apic *_next;

  static unsigned _nr_irqs;
  static Io_apic *_first;
  static Acpi_madt const *_madt;
  static Io_apic_entry *_state_save_area;

public:  
#line 189 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  explicit Io_apic(Unsigned64 phys, unsigned gsi_base);
  
#line 235 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  inline Io_apic_entry
  read_entry(unsigned i) const;
  
#line 247 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  inline void
  write_entry(unsigned i, Io_apic_entry const &e);
  
#line 308 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  static FIASCO_INIT
  Acpi_madt const *
  lookup_madt();
  
#line 320 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  static inline Acpi_madt const *madt();
  
#line 322 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  static FIASCO_INIT
  bool
  init_scan_apics();
  
#line 362 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  static FIASCO_INIT
  void
  init(Cpu_number);
  
#line 378 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  static void
  save_state();
  
#line 387 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  static void
  restore_state(bool set_boot_cpu = false);
  
#line 405 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  static unsigned
  total_irqs();
  
#line 410 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  static unsigned
  legacy_override(unsigned i);
  
#line 432 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  void
  dump();
  
#line 449 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  inline bool
  valid() const;
  
#line 471 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  inline bool
  masked(unsigned irq);
  
#line 480 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  inline void
  sync();
  
#line 487 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  inline void
  set_dest(unsigned irq, Mword dst);
  
#line 496 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  inline unsigned
  gsi_offset() const;
  
#line 500 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  static Io_apic *
  find_apic(unsigned irqnum);
  
#line 511 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  void
  mask(Mword irq) override;
  
#line 518 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  void
  ack(Mword) override;
  
#line 524 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  void
  mask_and_ack(Mword irq) override;
  
#line 532 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  void
  unmask(Mword irq) override;
  
#line 538 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  void
  set_cpu(Mword irq, Cpu_number cpu) override;
  
#line 562 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  int
  set_mode(Mword pin, Mode mode) override;
  
#line 576 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  inline Irq_chip::Mode
  get_mode(Mword pin);
  
#line 591 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  bool
  is_edge_triggered(Mword pin) const override;
  
#line 599 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  bool
  alloc(Irq_base *irq, Mword pin) override;
  
#line 614 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  void
  unbind(Irq_base *irq) override;
  
#line 625 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  static inline bool
  active();
  
#line 632 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  inline char const *
  chip_type() const override;

protected:  
#line 256 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  static FIASCO_INIT
  void
  read_overrides();
  
#line 545 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  static inline Mword
  to_io_apic_trigger(Irq_chip::Mode mode);
  
#line 554 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  static inline Mword
  to_io_apic_polarity(Irq_chip::Mode mode);

private:  
#line 453 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  inline void
  _mask(unsigned irq);
  
#line 462 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  inline void
  _unmask(unsigned irq);
};
#line 79 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

class Io_apic_mgr : public Irq_mgr, public Pm_object
{
public:
  Io_apic_mgr() { register_pm(Cpu_number::boot_cpu()); }

public:  
#line 106 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  Irq_mgr::Irq
  chip(Mword irq) const;
  
#line 117 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  unsigned
  nr_irqs() const;
  
#line 124 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  unsigned
  nr_msis() const;
  
#line 128 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  unsigned
  legacy_override(Mword i);
  
#line 132 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  void
  pm_on_suspend(Cpu_number cpu);
  
#line 140 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
  void
  pm_on_resume(Cpu_number cpu);
};
#line 148 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 91 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
#include "assert.h"
#line 94 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
#include "lock_guard.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 232 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"



inline Io_apic_entry
Io_apic::read_entry(unsigned i) const
{
  auto g = lock_guard(_l);
  Io_apic_entry e;
  //assert(i <= num_entries());
  e._e = (Unsigned64)_apic->read(0x10+2*i) | (((Unsigned64)_apic->read(0x11+2*i)) << 32);
  return e;
}

#line 244 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"



inline void
Io_apic::write_entry(unsigned i, Io_apic_entry const &e)
{
  auto g = lock_guard(_l);
  //assert(i <= num_entries());
  _apic->write(0x10+2*i, e._e);
  _apic->write(0x11+2*i, e._e >> 32);
}

#line 318 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline Acpi_madt const *Io_apic::madt() { return _madt; }

#line 447 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline bool
Io_apic::valid() const { return _apic; }

#line 469 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline bool
Io_apic::masked(unsigned irq)
{
  auto g = lock_guard(_l);
  //assert(irq <= _apic->num_entries());
  return _apic->read(0x10 + irq * 2) & (1UL << 16);
}

#line 478 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline void
Io_apic::sync()
{
  (void)_apic->data;
}

#line 485 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline void
Io_apic::set_dest(unsigned irq, Mword dst)
{
  auto g = lock_guard(_l);
  //assert(irq <= _apic->num_entries());
  _apic->modify(0x11 + irq * 2, dst & (~0UL << 24), ~0UL << 24);
}

#line 494 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline unsigned
Io_apic::gsi_offset() const { return _offset; }

#line 574 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline Irq_chip::Mode
Io_apic::get_mode(Mword pin)
{
  Io_apic_entry e = read_entry(pin);
  Mode m(Mode::Set_irq_mode);
  m.polarity() = e.polarity() == Io_apic_entry::High_active
               ? Mode::Polarity_high
               : Mode::Polarity_low;
  m.level_triggered() = e.trigger() == Io_apic_entry::Level
                      ? Mode::Trigger_level
                      : Mode::Trigger_edge;
  return m;
}

#line 623 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline bool
Io_apic::active()
{ return _first; }

#line 630 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline char const *
Io_apic::chip_type() const 
{ return "IO-APIC"; }

#line 543 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline Mword
Io_apic::to_io_apic_trigger(Irq_chip::Mode mode)
{
  return mode.level_triggered()
         ? Io_apic_entry::Level
         : Io_apic_entry::Edge;
}

#line 552 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline Mword
Io_apic::to_io_apic_polarity(Irq_chip::Mode mode)
{
  return mode.polarity() == Irq_chip::Mode::Polarity_high
         ? Io_apic_entry::High_active
         : Io_apic_entry::Low_active;
}

#line 148 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"



inline Mword
Io_apic::Apic::read(int reg)
{
  adr = reg;
  asm volatile ("": : :"memory");
  return data;
}

#line 158 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline void
Io_apic::Apic::modify(int reg, Mword set_bits, Mword del_bits)
{
  Mword tmp;
  adr = reg;
  asm volatile ("": : :"memory");
  tmp = data;
  tmp &= ~del_bits;
  tmp |= set_bits;
  data = tmp;
}

#line 171 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline void
Io_apic::Apic::write(int reg, Mword value)
{
  adr = reg;
  asm volatile ("": : :"memory");
  data = value;
}

#line 180 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


inline unsigned
Io_apic::Apic::num_entries()
{
  return (read(1) >> 16) & 0xff;
}

#endif // io_apic_h
