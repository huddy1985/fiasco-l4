// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "acpi.h"
#include "acpi_i.h"


#line 143 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"
static void
print_acpi_id(char const *id, int len);
#line 106 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"

Acpi_sdt Acpi::_sdt;
#line 108 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"
bool Acpi::_init_done;
#line 440 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"


// ------------------------------------------------------------------------


#line 141 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"


static void
print_acpi_id(char const *id, int len)
{
  char ID[len];
  for (int i = 0; i < len; ++i)
    ID[i] = isalnum(id[i]) ? id[i] : '.';
  printf("%.*s", len, ID);
}

#line 151 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"

void
Acpi_rsdp::print_info() const
{
  printf("ACPI: RSDP[%p]\tr%02x OEM:", this, (unsigned)rev);
  print_acpi_id(oem, 6);
  printf("\n");
}

#line 159 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"

void
Acpi_table_head::print_info() const
{
  printf("ACPI: ");
  print_acpi_id(signature, 4);
  printf("[%p]\tr%02x OEM:", this, (unsigned)rev);
  print_acpi_id(oem_id, 6);
  printf(" OEMTID:");
  print_acpi_id(oem_tid, 8);
  printf("\n");
}

#line 171 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"


void
Acpi_sdt::print_summary() const
{
  for (unsigned i = 0; i < _num_tables; ++i)
    if (_tables[i])
      _tables[i]->print_info();
}

#line 202 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"


void *
Acpi::_map_table_head(Unsigned64 phys)
{
  // is the acpi address bigger that our handled physical addresses
  if (Acpi_helper_get_msb<(sizeof(phys) > sizeof(Address))>::msb(phys))
    {
      printf("ACPI: cannot map phys address %llx, out of range (%ubit)\n",
             (unsigned long long)phys, (unsigned)sizeof(Address) * 8);
      return 0;
    }

  void *t = Kmem::dev_map.map((void*)phys);
  if (t == (void *)~0UL)
    {
      printf("ACPI: cannot map phys address %llx, map failed\n",
             (unsigned long long)phys);
      return 0;
    }

  return t;
}

#line 225 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"


bool
Acpi::check_signature(char const *sig, char const *reference)
{
  for (; *reference; ++sig, ++reference)
    if (*reference != *sig)
      return false;

  return true;
}

#line 255 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"




void
Acpi::init_virt()
{
  enum { Print_info = 0 };

  if (_init_done)
    return;
  _init_done = 1;

  if (Print_info)
    printf("ACPI-Init\n");

  Acpi_rsdp const *rsdp = Acpi_rsdp::locate();
  if (!rsdp)
    {
      WARN("ACPI: Could not find RSDP, skip init\n");
      return;
    }

  rsdp->print_info();

  if (rsdp->rev && rsdp->xsdt_phys)
    {
      Acpi_xsdt_p const *x = Kmem::dev_map.map((const Acpi_xsdt_p *)rsdp->xsdt_phys);
      if (x == (Acpi_xsdt_p const *)~0UL)
        WARN("ACPI: Could not map XSDT\n");
      else if (!x->checksum_ok())
        WARN("ACPI: Checksum mismatch in XSDT\n");
      else
        {
          _sdt.init(x);
          if (Print_info)
            {
              x->print_info();
              _sdt.print_summary();
            }
          return;
        }
    }

  if (rsdp->rsdt_phys)
    {
      Acpi_rsdt_p const *r = Kmem::dev_map.map((const Acpi_rsdt_p *)(unsigned long)rsdp->rsdt_phys);
      if (r == (Acpi_rsdt_p const *)~0UL)
        WARN("ACPI: Could not map RSDT\n");
      else if (!r->checksum_ok())
        WARN("ACPI: Checksum mismatch in RSDT\n");
      else
        {
          _sdt.init(r);
          if (Print_info)
            {
              r->print_info();
              _sdt.print_summary();
            }
          return;
        }
    }
}

#line 327 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"


Acpi_rsdt_p const *
Acpi_rsdp::rsdt() const
{
  return (Acpi_rsdt_p const*)(unsigned long)rsdt_phys;
}

#line 334 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"


Acpi_xsdt_p const *
Acpi_rsdp::xsdt() const
{
  if (rev == 0)
    return 0;
  return (Acpi_xsdt_p const*)xsdt_phys;
}

#line 343 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"


bool
Acpi_rsdp::checksum_ok() const
{
  // ACPI 1.0 checksum
  Unsigned8 sum = 0;
  for (unsigned i = 0; i < 20; i++)
    sum += *((Unsigned8 *)this + i);

  if (sum)
    return false;

  if (rev == 0)
    return true;

  // Extended Checksum
  for (unsigned i = 0; i < len && i < 4096; ++i)
    sum += *((Unsigned8 *)this + i);

  return !sum;
}

#line 365 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"


bool
Acpi_table_head::checksum_ok() const
{
  Unsigned8 sum = 0;
  for (unsigned i = 0; i < len && i < 4096; ++i)
    sum += *((Unsigned8 *)this + i);

  return !sum;
}

#line 376 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"


Acpi_table_head const *
Acpi_sdt::find(char const *sig) const
{
  for (unsigned i = 0; i < _num_tables; ++i)
    {
      Acpi_table_head const *t = _tables[i];
      if (!t)
	continue;

      if (Acpi::check_signature(t->signature, sig)
          && t->checksum_ok())
	return t;
    }

  return 0;
}

#line 413 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"


Acpi_madt::Apic_head const *
Acpi_madt::find(Unsigned8 type, int idx) const
{
  for (unsigned i = 0; i < len-sizeof(Acpi_madt);)
    {
      Apic_head const *a = (Apic_head const *)(data + i);
      //printf("a=%p, a->type=%u, a->len=%u\n", a, a->type, a->len);
      if (a->type == type)
	{
	  if (!idx)
	    return a;
	  --idx;
	}
      i += a->len;
    }

  return 0;
}

#line 444 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"


Acpi_rsdp const *
Acpi_rsdp::locate_in_region(Address start, Address end)
{
  for (Address p = start; p < end; p += 16)
    {
      Acpi_rsdp const* r = (Acpi_rsdp const *)p;
      if (Acpi::check_signature(r->signature, "RSD PTR ")
          && r->checksum_ok())
        return r;
    }

  return 0;
}

#line 459 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"


Acpi_rsdp const *
Acpi_rsdp::locate()
{
  enum
  {
    ACPI20_PC99_RSDP_START = 0x0e0000,
    ACPI20_PC99_RSDP_END   = 0x100000,

    BDA_EBDA_SEGMENT       = 0x00040E,
  };

  // If we are booted from UEFI, bootstrap reads the RSDP pointer from
  // UEFI and creates a memory descriptor with sub type 5 for it
  for (auto const &md: Kip::k()->mem_descs_a())
    if (   md.type() == Mem_desc::Info
        && md.ext_type() == Mem_desc::Info_acpi_rsdp)
      {
        Acpi_rsdp const *r = Acpi::map_table_head<Acpi_rsdp>(md.start());
        if (   Acpi::check_signature(r->signature, "RSD PTR ")
            && r->checksum_ok())
          return r;
        else
          panic("RSDP memory descriptor from bootstrap invalid");
      }

  if (Acpi_rsdp const *r = locate_in_region(ACPI20_PC99_RSDP_START,
                                            ACPI20_PC99_RSDP_END))
    return r;

  Address ebda = *(Unsigned16 *)BDA_EBDA_SEGMENT << 4;
  if (Acpi_rsdp const *r = locate_in_region(ebda, ebda + 1024))
    return r;

  return 0;
}
