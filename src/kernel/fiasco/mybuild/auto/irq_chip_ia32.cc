// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "irq_chip_ia32.h"
#include "irq_chip_ia32_i.h"

#line 96 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"

// The global INT vector allocator for IRQs uses these data
Int_vector_allocator Irq_chip_ia32::_vectors;

#line 99 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"


/**
 * Add free vectors to the allocator.
 * \note This code is not thread / MP safe and assumed to be executed at boot
 * time.
 */

void
Int_vector_allocator::add_free(unsigned start, unsigned end)
{
  assert (Base > 0x10);
  assert (End > Base);
  assert (start >= Base);
  assert (end <= End);

  for (unsigned v = start - Base; v < end - Base - 1; ++v)
    _vectors[v] = v + Base + 1;

  _vectors[end - Base - 1] = _first;
  _first = start;
}

#line 166 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"



Irq_base *
Irq_chip_ia32::irq(Mword irqn) const
{
  if (irqn >= _irqs)
    return 0;

  if (!_vec[irqn])
    return 0;

  extern Irq_entry_stub idt_irq_vector_stubs[];
  return idt_irq_vector_stubs[_vec[irqn] - 0x20].irq;
}

#line 181 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"

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
Irq_chip_ia32::_valloc(Mword pin, unsigned vector)
{
  if (pin >= _irqs)
    return 0;

  if (vector >= Int_vector_allocator::End)
    return 0;

  if (_vec[pin])
    return 0;

  if (!vector)
    vector = _vectors.alloc();

  return vector;
}

#line 219 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"


unsigned
Irq_chip_ia32::_vsetup(Irq_base *irq, Mword pin, unsigned vector)
{
  _vec[pin] = vector;
  extern Irq_entry_stub idt_irq_vector_stubs[];
  auto p = idt_irq_vector_stubs + vector - 0x20;
  p->irq = irq;

  // force code to memory before setting IDT entry
  Mem::barrier();

  Idt::set_entry(vector, (Address)p, false);
  return vector;
}

#line 252 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"

/**
 * \pre `irq->irqLock()` must be held
 */

bool
Irq_chip_ia32::vfree(Irq_base *irq, void *handler)
{
  extern Irq_entry_stub idt_irq_vector_stubs[];
  unsigned v = _vec[irq->pin()];
  assert (v);
  assert (idt_irq_vector_stubs[v - 0x20].irq == irq);

  Idt::set_entry(v, (Address)handler, false);
  idt_irq_vector_stubs[v - 0x20].irq = 0;
  _vec[irq->pin()] = 0;

  _vectors.free(v);
  return true;
}

#line 272 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/irq_chip_ia32.cpp"



bool
Irq_chip_ia32::reserve(Mword irqn)
{
  if (irqn >= _irqs)
    return false;

  if (_vec[irqn])
    return false;

  _vec[irqn] = 0xff;
  return true;
}
