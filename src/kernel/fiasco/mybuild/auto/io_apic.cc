// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "io_apic.h"
#include "io_apic_i.h"

#line 97 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

enum { Print_info = 0 };
#line 99 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

Acpi_madt const *Io_apic::_madt;
#line 101 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
unsigned Io_apic::_nr_irqs;
#line 102 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
Io_apic *Io_apic::_first;
#line 103 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"
Io_apic_entry *Io_apic::_state_save_area;

#line 104 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


Irq_mgr::Irq
Io_apic_mgr::chip(Mword irq) const
{
  Io_apic *a = Io_apic::find_apic(irq);
  if (a)
    return Irq(a, irq - a->gsi_offset());

  return Irq(0, 0);
}

#line 115 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


unsigned
Io_apic_mgr::nr_irqs() const
{
  return Io_apic::total_irqs();
}

#line 122 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


unsigned
Io_apic_mgr::nr_msis() const
{ return 0; }

#line 127 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

unsigned
Io_apic_mgr::legacy_override(Mword i)
{ return Io_apic::legacy_override(i); }

#line 131 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

void
Io_apic_mgr::pm_on_suspend(Cpu_number cpu)
{
  (void)cpu;
  assert (cpu == Cpu_number::boot_cpu());
  Io_apic::save_state();
}

#line 139 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

void
Io_apic_mgr::pm_on_resume(Cpu_number cpu)
{
  (void)cpu;
  assert (cpu == Cpu_number::boot_cpu());
  Pic::disable_all_save();
  Io_apic::restore_state(true);
}

#line 187 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


Io_apic::Io_apic(Unsigned64 phys, unsigned gsi_base)
: Irq_chip_ia32(0), _l(Spin_lock<>::Unlocked),
  _offset(gsi_base), _next(0)
{
  if (Print_info)
    printf("IO-APIC: addr=%lx\n", (Mword)phys);

  Address offs;
  Address va = Mem_layout::alloc_io_vmem(Config::PAGE_SIZE);
  assert (va);

  Kmem::map_phys_page(phys, va, false, true, &offs);

  Kip::k()->add_mem_region(Mem_desc(phys, phys + Config::PAGE_SIZE -1, Mem_desc::Reserved));

  Io_apic::Apic *a = (Io_apic::Apic*)(va + offs);
  a->write(0, 0);

  _apic = a;
  _irqs = a->num_entries() + 1;
  _vec = (unsigned char *)Boot_alloced::alloc(_irqs);

  if ((_offset + nr_irqs()) > _nr_irqs)
    _nr_irqs = _offset + nr_irqs();

  Io_apic **c = &_first;
  while (*c && (*c)->_offset < _offset)
    c = &((*c)->_next);

  _next = *c;
  *c = this;

  Mword cpu_phys = ::Apic::apic.cpu(Cpu_number::boot_cpu())->apic_id();

  for (unsigned i = 0; i < _irqs; ++i)
    {
      int v = 0x20 + i;
      Io_apic_entry e(v, Io_apic_entry::Fixed, Io_apic_entry::Physical,
                      Io_apic_entry::High_active, Io_apic_entry::Edge,
                      cpu_phys);
      write_entry(i, e);
    }
}

#line 255 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

FIASCO_INIT
void
Io_apic::read_overrides()
{
  for (unsigned tmp = 0;; ++tmp)
    {
      auto irq = _madt->find<Acpi_madt::Irq_source>(tmp);

      if (!irq)
        break;

      if (Print_info)
        printf("IO-APIC: ovr[%2u] %02x -> %x %x\n",
               tmp, (unsigned)irq->src, irq->irq, (unsigned)irq->flags);

      if (irq->irq >= _nr_irqs)
        {
          WARN("IO-APIC: warning override %02x -> %x (flags=%x) points to invalid GSI\n",
               (unsigned)irq->src, irq->irq, (unsigned)irq->flags);
          continue;
        }

      Io_apic *ioapic = find_apic(irq->irq);
      assert (ioapic);
      unsigned pin = irq->irq - ioapic->gsi_offset();
      Irq_chip::Mode mode = ioapic->get_mode(pin);

      unsigned pol = irq->flags & 0x3;
      unsigned trg = (irq->flags >> 2) & 0x3;
      switch (pol)
        {
        default: break;
        case 0: break;
        case 1: mode.polarity() = Mode::Polarity_high; break;
        case 2: break;
        case 3: mode.polarity() = Mode::Polarity_low; break;
        }

      switch (trg)
        {
        default: break;
        case 0: break;
        case 1: mode.level_triggered() = Mode::Trigger_edge; break;
        case 2: break;
        case 3: mode.level_triggered() = Mode::Trigger_level; break;
        }

      ioapic->set_mode(pin, mode);
    }
}

#line 306 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


FIASCO_INIT
Acpi_madt const *
Io_apic::lookup_madt()
{
  if (_madt)
    return _madt;

  _madt = Acpi::find<Acpi_madt const *>("APIC");
  return _madt;
}

#line 321 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

FIASCO_INIT
bool
Io_apic::init_scan_apics()
{
  auto madt = lookup_madt();

  if (madt == 0)
    {
      WARN("Could not find APIC in RSDT nor XSDT, skipping init\n");
      return false;
    }

  int n_apics;
  for (n_apics = 0;
       auto ioapic = madt->find<Acpi_madt::Io_apic>(n_apics);
       ++n_apics)
    {
      Io_apic *apic = new Boot_object<Io_apic>(ioapic->adr, ioapic->irq_base);
      (void)apic;

      if (Print_info)
        {
          printf("IO-APIC[%2d]: pins %u\n", n_apics, apic->nr_irqs());
          apic->dump();
        }
    }

  if (!n_apics)
    {
      WARN("IO-APIC: Could not find IO-APIC in MADT, skip init\n");
      return false;
    }

  if (Print_info)
    printf("IO-APIC: dual 8259: %s\n", madt->apic_flags & 1 ? "yes" : "no");

  return true;
}

#line 360 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


FIASCO_INIT
void
Io_apic::init(Cpu_number)
{
  if (!Irq_mgr::mgr)
    Irq_mgr::mgr = new Boot_object<Io_apic_mgr>();

  _state_save_area = new Boot_object<Io_apic_entry>[_nr_irqs];
  read_overrides();

  // in the case we use the IO-APIC not the PIC we can dynamically use
  // INT vectors from 0x20 to 0x2f too
  _vectors.add_free(0x20, 0x30);
};

#line 376 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


void
Io_apic::save_state()
{
  for (Io_apic *a = _first; a; a = a->_next)
    for (unsigned i = 0; i < a->_irqs; ++i)
      _state_save_area[a->_offset + i] = a->read_entry(i);
}

#line 385 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


void
Io_apic::restore_state(bool set_boot_cpu)
{
  Mword cpu_phys = 0;
  if (set_boot_cpu)
    cpu_phys = ::Apic::apic.cpu(Cpu_number::boot_cpu())->apic_id();

  for (Io_apic *a = _first; a; a = a->_next)
    for (unsigned i = 0; i < a->_irqs; ++i)
      {
        Io_apic_entry e = _state_save_area[a->_offset + i];
        if (set_boot_cpu && e.format() == 0)
          e.dest() = cpu_phys;
        a->write_entry(i, e);
      }
}

#line 403 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


unsigned
Io_apic::total_irqs()
{ return _nr_irqs; }

#line 408 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


unsigned
Io_apic::legacy_override(unsigned i)
{
  if (!_madt)
    return i;

  unsigned tmp = 0;
  for (;;++tmp)
    {
      Acpi_madt::Irq_source const *irq
	= static_cast<Acpi_madt::Irq_source const *>(_madt->find(Acpi_madt::Irq_src_ovr, tmp));

      if (!irq)
	break;

      if (irq->src == i)
	return irq->irq;
    }
  return i;
}

#line 430 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


void
Io_apic::dump()
{
  for (unsigned i = 0; i < _irqs; ++i)
    {
      Io_apic_entry e = read_entry(i);
      printf("  PIN[%2u%c]: vector=%2x, del=%u, dm=%s, dest=%u (%s, %s)\n",
	     i, e.mask() ? 'm' : '.',
	     (unsigned)e.vector(), (unsigned)e.delivery(), e.dest_mode() ? "logical" : "physical",
	     (unsigned)e.dest(),
	     e.polarity() ? "low" : "high",
	     e.trigger() ? "level" : "edge");
    }

}

#line 498 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


Io_apic *
Io_apic::find_apic(unsigned irqnum)
{
  for (Io_apic *a = _first; a; a = a->_next)
    {
      if (a->_offset <= irqnum && a->_offset + a->_irqs > irqnum)
	return a;
    }
  return 0;
};

#line 510 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

void
Io_apic::mask(Mword irq) 
{
  _mask(irq);
  sync();
}

#line 517 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

void
Io_apic::ack(Mword) 
{
  ::Apic::irq_ack();
}

#line 523 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

void
Io_apic::mask_and_ack(Mword irq) 
{
  _mask(irq);
  sync();
  ::Apic::irq_ack();
}

#line 531 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

void
Io_apic::unmask(Mword irq) 
{
  _unmask(irq);
}

#line 537 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

void
Io_apic::set_cpu(Mword irq, Cpu_number cpu) 
{
  set_dest(irq, ::Apic::apic.cpu(cpu)->apic_id());
}

#line 561 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"

int
Io_apic::set_mode(Mword pin, Mode mode) 
{
  if (!mode.set_mode())
    return 0;

  Io_apic_entry e = read_entry(pin);
  e.polarity() = to_io_apic_polarity(mode);
  e.trigger() = to_io_apic_trigger(mode);
  write_entry(pin, e);
  return 0;
}

#line 589 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


bool
Io_apic::is_edge_triggered(Mword pin) const 
{
  Io_apic_entry e = read_entry(pin);
  return e.trigger() == Io_apic_entry::Edge;
}

#line 597 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


bool
Io_apic::alloc(Irq_base *irq, Mword pin) 
{
  unsigned v = valloc<Io_apic>(irq, pin, 0);

  if (!v)
    return false;

  Io_apic_entry e = read_entry(pin);
  e.vector() = v;
  write_entry(pin, e);
  return true;
}

#line 612 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/io_apic.cpp"


void
Io_apic::unbind(Irq_base *irq) 
{
  extern char entry_int_apic_ignore[];
  Mword n = irq->pin();
  mask(n);
  vfree(irq, &entry_int_apic_ignore);
  Irq_chip_icu::unbind(irq);
}
