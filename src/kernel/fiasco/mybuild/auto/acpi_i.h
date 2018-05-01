// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef acpi_i_h
#define acpi_i_h
#line 109 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"

template< typename T >
class Acpi_sdt_p : public Acpi_table_head
{
public:
  T ptrs[0];


public:  
#line 182 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"
  unsigned
  entries() const;
  
#line 397 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"
  Acpi_table_head const *
  find(char const *sig) const;
} __attribute__((packed));
#line 117 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"

typedef Acpi_sdt_p<Unsigned32> Acpi_rsdt_p;
#line 119 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"
typedef Acpi_sdt_p<Unsigned64> Acpi_xsdt_p;
#line 120 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"

class Acpi_rsdp
{
public:
  char       signature[8];
  Unsigned8  chk_sum;
  char       oem[6];
  Unsigned8  rev;
  Unsigned32 rsdt_phys;
  Unsigned32 len;
  Unsigned64 xsdt_phys;
  Unsigned8  ext_chk_sum;
  char       reserved[3];

  Acpi_rsdt_p const *rsdt() const;
  Acpi_xsdt_p const *xsdt() const;

  bool checksum_ok() const;

  static Acpi_rsdp const *locate();

public:  
#line 152 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"
  void
  print_info() const;

private:  
#line 446 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"
  static Acpi_rsdp const *
  locate_in_region(Address start, Address end);
} __attribute__((packed));

//
// IMPLEMENTATION of function templates
//


#line 180 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"


template< typename T > unsigned
Acpi_sdt_p<T>::entries() const
{ return (len - sizeof(Acpi_table_head)) / sizeof(ptrs[0]); }

#line 394 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/acpi.cpp"



template< typename T > Acpi_table_head const *
Acpi_sdt_p<T>::find(char const *sig) const
{
  for (unsigned i = 0; i < ((len-sizeof(Acpi_table_head))/sizeof(ptrs[0])); ++i)
    {
      Acpi_table_head const *t = Kmem::dev_map.map((Acpi_table_head const*)ptrs[i]);
      if (t == (Acpi_table_head const *)~0UL)
	continue;

      if (Acpi::check_signature(t->signature, sig)
          && t->checksum_ok())
	return t;
    }

  return 0;
}

#endif // acpi_i_h
