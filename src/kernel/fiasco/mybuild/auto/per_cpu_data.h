// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef per_cpu_data_h
#define per_cpu_data_h
#line 43 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/per_cpu_data.cpp"

#include "static_init.h"
#line 45 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/per_cpu_data.cpp"
#include "config.h"
#line 46 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/per_cpu_data.cpp"
#include "context_base.h"
#line 47 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/per_cpu_data.cpp"
#include <cxx/type_traits>

//
// INTERFACE definition follows 
//

#line 66 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/per_cpu_data.cpp"

template< typename T > class Per_cpu_ptr;
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/per_cpu_data.cpp"

template< typename T, unsigned EXTRA = 0 >
class Per_cpu_array
: public cxx::array<T, Cpu_number, Config::Max_num_cpus + EXTRA>
{};
#line 39 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/per_cpu_data.cpp"

#define DEFINE_PER_CPU_CTOR_DATA(id)
#line 48 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/per_cpu_data.cpp"

#define DEFINE_PER_CPU_P(p) \
  DEFINE_PER_CPU_CTOR_DATA(__COUNTER__) \
  __attribute__((section(".per_cpu.data"),init_priority(0xfffe - p)))
#line 52 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/per_cpu_data.cpp"

#define DEFINE_PER_CPU      DEFINE_PER_CPU_P(9)
#line 54 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/per_cpu_data.cpp"
#define DEFINE_PER_CPU_LATE DEFINE_PER_CPU_P(19)
#line 55 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/per_cpu_data.cpp"

class Per_cpu_data
{
public:
  static void init_ctors();
  static void run_ctors(Cpu_number cpu);
  static void run_late_ctors(Cpu_number cpu);
  static bool valid(Cpu_number cpu);

  enum With_cpu_num { Cpu_num };
};
#line 68 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/per_cpu_data.cpp"

template< typename T >
class Per_cpu : private Per_cpu_data
{
  friend class Per_cpu_ptr<T>;
public:
  typedef T Type;

  T const &cpu(Cpu_number) const;
  T &cpu(Cpu_number);

  T const &current() const { return cpu(current_cpu()); }
  T &current() { return cpu(current_cpu()); }

  Per_cpu();
  explicit Per_cpu(With_cpu_num);

  template<typename TEST>
  Cpu_number find_cpu(TEST const &test) const
  {
    for (Cpu_number i = Cpu_number::first(); i < Config::max_num_cpus(); ++i)
      if (valid(i) && test(cpu(i)))
        return i;

    return Cpu_number::nil();
  }

private:
  T _d;
};
#line 98 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/per_cpu_data.cpp"

template< typename T >
class Per_cpu_ptr : private Per_cpu_data
{
public:
  typedef typename cxx::conditional<
    cxx::is_const<T>::value,
    Per_cpu<typename cxx::remove_cv<T>::type> const,
    Per_cpu<typename cxx::remove_cv<T>::type> >::type Per_cpu_type;

  Per_cpu_ptr() {}
  Per_cpu_ptr(Per_cpu_type *o) : _p(&o->_d) {}
  Per_cpu_ptr &operator = (Per_cpu_type *o)
  {
    _p = &o->_d;
    return *this;
  }

  T &cpu(Cpu_number cpu);
  T &current() { return cpu(current_cpu()); }

private:
  T *_p;
};
#line 122 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/per_cpu_data.cpp"


//---------------------------------------------------------------------------


//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 126 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/per_cpu_data.cpp"

#include <construction.h>

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 128 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/per_cpu_data.cpp"


inline bool
Per_cpu_data::valid(Cpu_number cpu)
{
#if defined NDEBUG
  (void)cpu;
  return 1;
#else
  return cpu == Cpu_number::boot_cpu();
#endif
}

#line 169 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/per_cpu_data.cpp"


inline void
Per_cpu_data::run_ctors(Cpu_number)
{
  extern ctor_function_t __PER_CPU_INIT_ARRAY_START__[];
  extern ctor_function_t __PER_CPU_INIT_ARRAY_END__[];
  run_ctor_functions(__PER_CPU_INIT_ARRAY_START__, __PER_CPU_INIT_ARRAY_END__);

  extern ctor_function_t __PER_CPU_CTORS_LIST__[];
  extern ctor_function_t __PER_CPU_CTORS_END__[];
  run_ctor_functions(__PER_CPU_CTORS_LIST__, __PER_CPU_CTORS_END__);
}

#line 182 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/per_cpu_data.cpp"


inline void
Per_cpu_data::run_late_ctors(Cpu_number)
{
  extern ctor_function_t __PER_CPU_LATE_INIT_ARRAY_START__[];
  extern ctor_function_t __PER_CPU_LATE_INIT_ARRAY_END__[];
  run_ctor_functions(__PER_CPU_LATE_INIT_ARRAY_START__,
                     __PER_CPU_LATE_INIT_ARRAY_END__);

  extern ctor_function_t __PER_CPU_LATE_CTORS_LIST__[];
  extern ctor_function_t __PER_CPU_LATE_CTORS_END__[];
  run_ctor_functions(__PER_CPU_LATE_CTORS_LIST__, __PER_CPU_LATE_CTORS_END__);
}

#line 140 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/per_cpu_data.cpp"



template< typename T > inline T const &Per_cpu<T>::cpu(Cpu_number) const { return _d; }

#line 144 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/per_cpu_data.cpp"



template< typename T > inline T &Per_cpu<T>::cpu(Cpu_number) { return _d; }

#line 158 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/per_cpu_data.cpp"



template< typename T > inline T &Per_cpu_ptr<T>::cpu(Cpu_number) { return *_p; }

//
// IMPLEMENTATION of function templates
//


#line 148 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/per_cpu_data.cpp"



template< typename T > Per_cpu<T>::Per_cpu()
{}

#line 153 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/per_cpu_data.cpp"



template< typename T > Per_cpu<T>::Per_cpu(With_cpu_num) : _d(Cpu_number::boot_cpu())
{}

#endif // per_cpu_data_h
