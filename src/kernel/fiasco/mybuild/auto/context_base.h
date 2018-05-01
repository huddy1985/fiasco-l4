// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef context_base_h
#define context_base_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context_base.cpp"

#include "types.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context_base.cpp"
#include "config_tcbsize.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context_base.cpp"
#include "fiasco_defs.h"

//
// INTERFACE definition follows 
//

#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context_base.cpp"

class Context;
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context_base.cpp"

class Context_base
{
public:
  enum
  {
    Size = THREAD_BLOCK_SIZE
  };

  // This virtual dtor enforces that Context / Thread / Context_base
  // all start at offset 0
  virtual ~Context_base() = 0;

protected:
  Mword _state;

public:  
#line 63 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context_base.cpp"
  inline void
  set_current_cpu(Cpu_number);
  
#line 68 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context_base.cpp"
  inline Cpu_number
  get_current_cpu() const;
};

#line 44 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context_base.cpp"
inline Context *context_of(const void *ptr);

#line 51 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context_base.cpp"
inline Context *current();

#line 59 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context_base.cpp"
inline Cpu_number current_cpu();

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 37 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context_base.cpp"

#include "config.h"
#line 39 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context_base.cpp"
#include "processor.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 61 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context_base.cpp"


inline void
Context_base::set_current_cpu(Cpu_number)
{}

#line 66 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context_base.cpp"


inline Cpu_number
Context_base::get_current_cpu() const
{ return Cpu_number::boot_cpu(); }

#line 40 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context_base.cpp"

inline Context_base::~Context_base() {}

#line 42 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context_base.cpp"


inline Context *context_of(const void *ptr)
{
  return reinterpret_cast<Context *>
    (reinterpret_cast<unsigned long>(ptr) & ~(Context_base::Size - 1));
}

#line 49 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context_base.cpp"


inline Context *current()
{ return context_of((void *)Proc::stack_pointer()); }

#line 57 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/context_base.cpp"


inline Cpu_number current_cpu()
{ return Cpu_number::boot_cpu(); }

#endif // context_base_h
