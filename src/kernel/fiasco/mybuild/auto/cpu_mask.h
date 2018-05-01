// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef cpu_mask_h
#define cpu_mask_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_mask.cpp"

#include "bitmap.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_mask.cpp"
#include "config.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_mask.cpp"
#include "types.h"

//
// INTERFACE definition follows 
//

#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_mask.cpp"

template<unsigned MAX_NUM_CPUS>
class Cpu_mask_t
{
public:
  enum { Max_num_cpus = MAX_NUM_CPUS };
  enum class Init { Bss };
  Cpu_mask_t(Init) {}
  Cpu_mask_t() { _b.clear_all(); }

  Cpu_mask_t(Cpu_mask_t const &) = default;
  Cpu_mask_t &operator = (Cpu_mask_t const &) = default;

  template<unsigned NCPUS>
  Cpu_mask_t &operator = (Cpu_mask_t<NCPUS> const &o)
  {
    _b = o._b;
    return *this;
  }

  bool empty() const { return _b.is_empty(); }
  bool get(Cpu_number cpu) const
  { return _b[cxx::int_value<Cpu_number>(cpu)]; }

  void clear(Cpu_number cpu)
  { return _b.clear_bit(cxx::int_value<Cpu_number>(cpu)); }

  void set(Cpu_number cpu)
  { _b.set_bit(cxx::int_value<Cpu_number>(cpu)); };

  void atomic_set(Cpu_number cpu)
  { _b.atomic_set_bit(cxx::int_value<Cpu_number>(cpu)); }

  void atomic_clear(Cpu_number cpu)
  { _b.atomic_clear_bit(cxx::int_value<Cpu_number>(cpu)); }

  bool atomic_get_and_clear(Cpu_number cpu)
  { return _b.atomic_get_and_clear(cxx::int_value<Cpu_number>(cpu)); }

private:
  template<unsigned B> friend class Cpu_mask_t;
  Bitmap<Max_num_cpus> _b;
};
#line 49 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu_mask.cpp"

typedef Cpu_mask_t<Config::Max_num_cpus> Cpu_mask;

#endif // cpu_mask_h
