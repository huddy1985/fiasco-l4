// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef irq_chip_ia32_h
#define irq_chip_ia32_h
#line 26 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"

#include "globals.h"
#line 28 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
#include "idt_init.h"
#line 29 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
#include "irq_chip.h"
#line 30 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
#include "boot_alloc.h"
#line 31 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
#include "spin_lock.h"
#line 32 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
#include "lock_guard.h"

//
// INTERFACE definition follows 
//

#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"

class Irq_base;
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"

/** this structure must exactly map to the code stubs from 32/entry.S */
struct Irq_entry_stub
{
  char _res[2];
  Irq_base *irq;
  char _res2[5];
} __attribute__((packed));
#line 33 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"

/**
 * Allocator for IA32 interrupt vectors in the IDT.
 *
 * Some vectors are fixed purpose, others can be dynamically
 * managed by this allocator to support MSIs and multiple IO-APICs.
 */
class Int_vector_allocator
{
public:
  enum
  {
    /// Start at vector 0x20, note: <0x10 is vorbidden here
    Base = 0x20,

    /// The Last vector + 1 that is managed
    End  = APIC_IRQ_BASE - 0x08
  };

  bool empty() const { return !_first; }

private:
  /// array for free list
  unsigned char _vectors[End - Base];

  /// the first free vector
  unsigned _first;

  Spin_lock<> _lock;

public:  
#line 101 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
  /**
   * Add free vectors to the allocator.
   * \note This code is not thread / MP safe and assumed to be executed at boot
   * time.
   */
  
  void
  add_free(unsigned start, unsigned end);
  
#line 123 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
  inline void
  free(unsigned v);
  
#line 134 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
  inline unsigned
  alloc();
};
#line 63 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"

/**
 * Generic IA32 IRQ chip class.
 *
 * Uses an array of Idt_entry_code objects to manage
 * the IRQ entry points and the Irq_base objects assigned to the
 * pins of a specific controller.
 */
class Irq_chip_ia32
{
public:
  /// Number of pins at this chip.
  unsigned nr_irqs() const { return _irqs; }

protected:
  unsigned _irqs;
  unsigned char *_vec;
  Spin_lock<> _entry_lock;

  static Int_vector_allocator _vectors;

  unsigned char vector(Mword pin) const
  { return _vec[pin]; }

public:  
#line 149 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
  /**
   * \note This code is not thread / MP safe.
   */
  
  explicit inline Irq_chip_ia32(unsigned irqs);
  
#line 169 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
  Irq_base *
  irq(Mword irqn) const;
  
#line 275 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
  bool
  reserve(Mword irqn);

protected:  
#line 236 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
  /**
   * \pre `irq->irqLock()` must be held
   */
   
  template<typename CHIP> inline unsigned
  valloc(Irq_base *irq, Mword pin, unsigned vector);
  
#line 253 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
  /**
   * \pre `irq->irqLock()` must be held
   */
  
  bool
  vfree(Irq_base *irq, void *handler);

private:  
#line 182 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
  /**
   * Generic binding of an Irq_base object to a specific pin and a 
   * an INT vector.
   *
   * \param irq The Irq_base object to bind
   * \param pin The pin number at this IRQ chip
   * \param vector The INT vector to use, or 0 for dynamic allocation
   * \return the INT vector used an success, or 0 on failure.
   *
   * This function does the following:
   * 1. Some sanity checks
   * 2. Check if PIN is unassigned
   * 3. Check if no vector is given:
   *    a) Use vector that was formerly assigned to this PIN
   *    b) Try to allocate a new vector for the PIN
   * 4. Prepare the entry code to point to \a irq
   * 5. Point IDT entry to the PIN's entry code
   * 6. Return the assigned vector number
   */
  
  unsigned
  _valloc(Mword pin, unsigned vector);
  
#line 221 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"
  unsigned
  _vsetup(Irq_base *irq, Mword pin, unsigned vector);
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 121 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"


inline void
Int_vector_allocator::free(unsigned v)
{
  assert (Base <= v && v < End);

  auto g = lock_guard(_lock);
  _vectors[v - Base] = _first;
  _first = v;
}

#line 132 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"


inline unsigned
Int_vector_allocator::alloc()
{
  if (!_first)
    return 0;

  auto g = lock_guard(_lock);
  unsigned r = _first;
  if (!r)
    return 0;

  _first = _vectors[r - Base];
  return r;
}

#line 148 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"

/**
 * \note This code is not thread / MP safe.
 */

inline Irq_chip_ia32::Irq_chip_ia32(unsigned irqs)
: _irqs(irqs),
  _vec(irqs ? (unsigned char *)Boot_alloced::alloc(irqs) : 0),
  _entry_lock(Spin_lock<>::Unlocked)
{
  for (unsigned i = 0; i < irqs; ++i)
    _vec[i] = 0;

  // add vectors from 0x40 up to Int_vector_allocator::End
  // as free if we are the first IA32 chip ctor running
  if (_vectors.empty())
    _vectors.add_free(0x34, Int_vector_allocator::End);
}

#line 235 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"

/**
 * \pre `irq->irqLock()` must be held
 */
 
template<typename CHIP> inline unsigned
Irq_chip_ia32::valloc(Irq_base *irq, Mword pin, unsigned vector)
{
  auto g = lock_guard(_entry_lock);
  unsigned v = _valloc(pin, vector);
  if (!v)
    return 0;

  static_cast<CHIP*>(this)->bind(irq, pin);
  _vsetup(irq, pin, v);
  return v;
}

#endif // irq_chip_ia32_h
