// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "kip.h"
#include "kip_i.h"

#line 208 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"

Kip *Kip::global_kip;
#line 232 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"

#ifdef TARGET_NAME
#line 234 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"
#define TARGET_NAME_PHRASE " for " TARGET_NAME
#line 235 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"
#else
#line 236 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"
#define TARGET_NAME_PHRASE
#line 237 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"
#endif
#line 238 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"

asm(".section .initkip.version, \"a\", %progbits        \n"
    ".string \"" CONFIG_KERNEL_VERSION_STRING "\"       \n"
    ".previous                                          \n");
#line 242 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"

asm(".section .initkip.features.end, \"a\", %progbits   \n"
    ".string \"\"                                       \n"
    ".previous                                          \n");

#line 192 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"


Mem_desc *Kip::add_mem_region(Mem_desc const &md)
{
  for (auto &m: mem_descs_a())
    if (m.type() == Mem_desc::Undefined)
      {
        m = md;
        return &m;
      }

  // Add mem region failed -- must be a Fiasco startup problem.  Bail out.
  panic("Too few memory descriptors in KIP");

  return 0;
}

#line 224 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/abi/kip.cpp"


char const *Kip::version_string() const
{
  static_assert((sizeof(Kip) & 0xf) == 0, "Invalid KIP structure size");

  return reinterpret_cast <char const *> (this) + (offset_version_strings << 4);
}
