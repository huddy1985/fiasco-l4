// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef acpi_h
#define acpi_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"

#include <types.h>

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"

class Acpi_gas
{
public:
  enum Type { System_mem = 0, System_io = 1, Pci_cfg_mem = 2 };
  Unsigned8  id;
  Unsigned8  width;
  Unsigned8  offset;
  Unsigned8  access_size;
  Unsigned64 addr;
} __attribute__((packed));
#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"



class Acpi_table_head
{
public:
  char       signature[4];
  Unsigned32 len;
  Unsigned8  rev;
  Unsigned8  chk_sum;
  char       oem_id[6];
  char       oem_tid[8];
  Unsigned32 oem_rev;
  Unsigned32 creator_id;
  Unsigned32 creator_rev;

  bool checksum_ok() const;

public:  
#line 160 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"
  void
  print_info() const;
} __attribute__((packed));
#line 33 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"


class Acpi_sdt
{
private:
  unsigned _num_tables;
  Acpi_table_head const **_tables;

public:  
#line 173 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"
  void
  print_summary() const;
  
#line 187 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"
  template< typename SDT > void
  init(SDT *sdt);
  
#line 378 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"
  Acpi_table_head const *
  find(char const *sig) const;

private:  
#line 244 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"
  template< typename T > Acpi_table_head const *
  map_entry(unsigned idx, T phys);
};
#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"

class Acpi
{
public:
  static Acpi_sdt const *sdt() { return &_sdt; }

private:
  static Acpi_sdt _sdt;
  static bool _init_done;

public:  
#line 227 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"
  static bool
  check_signature(char const *sig, char const *reference);
  
#line 238 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"
  template<typename TAB> static TAB *
  map_table_head(Unsigned64 phys);
  
#line 259 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"
  static void
  init_virt();
  
#line 321 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"
  template< typename T > static T
  find(const char *s);

private:  
#line 204 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"
  static void *
  _map_table_head(Unsigned64 phys);
};
#line 51 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"

class Acpi_madt : public Acpi_table_head
{
public:
  enum Type
  { LAPIC, IOAPIC, Irq_src_ovr, NMI, LAPIC_NMI, LAPIC_adr_ovr, IOSAPIC,
    LSAPIC, Irq_src };

  struct Apic_head
  {
    Unsigned8 type;
    Unsigned8 len;
  } __attribute__((packed));

  struct Io_apic : public Apic_head
  {
    enum { ID = IOAPIC };
    Unsigned8 id;
    Unsigned8 res;
    Unsigned32 adr;
    Unsigned32 irq_base;
  } __attribute__((packed));

  struct Irq_source : public Apic_head
  {
    enum { ID = Irq_src_ovr };
    Unsigned8  bus;
    Unsigned8  src;
    Unsigned32 irq;
    Unsigned16 flags;
  } __attribute__((packed));

public:
  Unsigned32 local_apic;
  Unsigned32 apic_flags;

private:
  char data[0];

public:  
#line 415 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"
  Acpi_madt::Apic_head const *
  find(Unsigned8 type, int idx) const;
  
#line 435 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"
  template<typename T> inline T const *
  find(int idx) const;
} __attribute__((packed));
#line 90 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"

template< bool >
struct Acpi_helper_get_msb
{ template<typename P> static Address msb(P) { return 0; } };
#line 94 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"

template<>
struct Acpi_helper_get_msb<true>
{ template<typename P> static Address msb(P p) { return p >> (sizeof(Address) * 8); } };

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 101 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"

#include "boot_alloc.h"
#line 103 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"
#include "kmem.h"
#line 104 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"
#include "warn.h"
#line 105 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"
#include <cctype>

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 433 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"

 
template<typename T> inline T const *
Acpi_madt::find(int idx) const
{
  return static_cast<T const *>(find(T::ID, idx));
}

//
// IMPLEMENTATION of function templates
//


#line 185 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"


template< typename SDT > void
Acpi_sdt::init(SDT *sdt)
{
  unsigned entries = sdt->entries();
  _tables = (Acpi_table_head const **)Boot_alloced::alloc(sizeof(*_tables) * entries);
  if (_tables)
    {
      _num_tables = entries;
      for (unsigned i = 0; i < entries; ++i)
        if (sdt->ptrs[i])
          _tables[i] = this->map_entry(i, sdt->ptrs[i]);
        else
          _tables[i] = 0;
    }
}

#line 236 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"


template<typename TAB> TAB *
Acpi::map_table_head(Unsigned64 phys)
{ return reinterpret_cast<TAB *>(_map_table_head(phys)); }

#line 241 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"



template< typename T > Acpi_table_head const *
Acpi_sdt::map_entry(unsigned idx, T phys)
{
  if (idx >= _num_tables)
    {
      printf("ACPI: table index out of range (%u >= %u)\n", idx, _num_tables);
      return 0;
    }

  return Acpi::map_table_head<Acpi_table_head>((Unsigned64)phys);
}

#line 318 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"



template< typename T > T
Acpi::find(const char *s)
{
  init_virt();
  return static_cast<T>(sdt()->find(s));
}

#endif // acpi_h
