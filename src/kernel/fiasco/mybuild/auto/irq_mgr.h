// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef irq_mgr_h
#define irq_mgr_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_mgr.cpp"

#include "types.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_mgr.cpp"
#include "irq_chip.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_mgr.cpp"
#include "l4_types.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_mgr.cpp"
#include <cxx/type_traits>

//
// INTERFACE definition follows 
//

#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_mgr.cpp"

/**
 * Interface used to manage hardware IRQs on a platform.
 *
 * The main purpose of this interface is to allow an
 * abstract mapping of global IRQ numbers to a chip
 * and pin number pair. The interface provides also
 * some global information about IRQs.
 */
class Irq_mgr
{
public:
  struct Msi_info
  {
    Unsigned64 addr;
    Unsigned32 data;
  };

  /**
   * Chip and pin for an IRQ pin.
   */
  struct Irq
  {
    // allow uninitialized instances
    enum Init { Bss };
    Irq(Init) {}

    /// Invalid IRQ.
    Irq() : chip(0) {}

    /// Create a chip-pin pair.
    Irq(Irq_chip_icu *chip, Mword pin) : chip(chip), pin(pin) {}

    /// The chip.
    Irq_chip_icu *chip;

    /// The pin number local to \a chip.
    Mword pin;
  };

  /// Map legacy (IA32) IRQ numbers to valid IRQ numbers.
  virtual unsigned legacy_override(Mword irqnum) { return irqnum; }

  /// Get the chip-pin pair for the given global IRQ number.
  virtual Irq chip(Mword irqnum) const = 0;

  /// Get the highest available global IRQ number plus 1.
  virtual unsigned nr_irqs() const = 0;

  /// Get the number of available entry points for MSIs.
  virtual unsigned nr_msis() const = 0;

  /** Get the message to use for a given MSI.
   * \pre The IRQ pin needs to be already allocated before using this function.
   */
  virtual int msg(Mword irqnum, Unsigned64, Msi_info *) const
  { (void)irqnum; return -L4_err::EPerm; }

  virtual void set_cpu(Mword irqnum, Cpu_number cpu) const;

  /// The pointer to the single global instance of the actual IRQ manager.
  static Irq_mgr *mgr;

  /// Prevent generation of a real virtual delete function
  virtual ~Irq_mgr() = 0;

public:  
#line 99 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_mgr.cpp"
  inline bool
  alloc(Irq_base *irq, Mword global_irq);
  
#line 115 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_mgr.cpp"
  inline bool
  reserve(Mword irqnum);
  
#line 126 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_mgr.cpp"
  inline Irq_base *
  irq(Mword irqnum) const;
};
#line 73 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_mgr.cpp"

template< typename CHIP >
class Irq_mgr_single_chip : public Irq_mgr
{
public:
  Irq_mgr_single_chip() {}

  template< typename... A >
  explicit Irq_mgr_single_chip(A&&... args) : c(cxx::forward<A>(args)...) {}

  Irq chip(Mword irqnum) const { return Irq(&c, irqnum); }
  unsigned nr_irqs() const { return c.nr_irqs(); }
  unsigned nr_msis() const { return 0; }
  mutable CHIP c;
};
#line 88 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_mgr.cpp"

//--------------------------------------------------------------------------


//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 97 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_mgr.cpp"


inline bool
Irq_mgr::alloc(Irq_base *irq, Mword global_irq)
{
  Irq i = chip(global_irq);
  if (!i.chip)
    return false;

  if (i.chip->alloc(irq, i.pin))
    {
      i.chip->set_cpu(i.pin, Cpu_number::boot_cpu());
      return true;
    }
  return false;
}

#line 113 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_mgr.cpp"


inline bool
Irq_mgr::reserve(Mword irqnum)
{
  Irq i = chip(irqnum);
  if (!i.chip)
    return false;

  return i.chip->reserve(i.pin);
}

#line 124 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_mgr.cpp"


inline Irq_base *
Irq_mgr::irq(Mword irqnum) const
{
  Irq i = chip(irqnum);
  if (!i.chip)
    return 0;

  return i.chip->irq(i.pin);
}

#line 95 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/irq_mgr.cpp"

inline Irq_mgr::~Irq_mgr() {}

#endif // irq_mgr_h
