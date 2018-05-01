// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "map_util.h"
#include "map_util_i.h"

#line 204 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/map_util.cpp"


//-------------------------------------------------------------------------

#line 214 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/map_util.cpp"


//-------------------------------------------------------------------------


#line 262 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/map_util.cpp"


/** Flexpage mapping.
    divert to mem_map (for memory fpages) or io_map (for IO fpages)
    @param from source address space
    @param fp_from flexpage descriptor for virtual-address space range
	in source address space
    @param to destination address space
    @param fp_to flexpage descriptor for virtual-address space range
	in destination address space
    @param offs sender-specified offset into destination flexpage
    @param grant if set, grant the fpage, otherwise map
    @pre page_aligned(offs)
    @return IPC error
    L4_fpage from_fp, to_fp;
    Mword control;code that describes the status of the operation
*/
// Don't inline -- it eats too much stack.
// inline NEEDS ["config.h", io_map]
L4_error
fpage_map(Space *from, L4_fpage fp_from, Space *to,
          L4_fpage fp_to, L4_msg_item control, Kobject::Reap_list *r)
{
  Space::Caps caps = from->caps() & to->caps();

  if (Map_traits<Mem_space>::match(fp_from, fp_to) && (caps & Space::Caps::mem()))
    return mem_map(from, fp_from, to, fp_to, control);

#ifdef CONFIG_PF_PC
  if (Map_traits<Io_space>::match(fp_from, fp_to) && (caps & Space::Caps::io()))
    return io_map(from, fp_from, to, fp_to, control);
#endif

  if (Map_traits<Obj_space>::match(fp_from, fp_to) && (caps & Space::Caps::obj()))
    return obj_map(from, fp_from, to, fp_to, control, r->list());

  return L4_error::None;
}

#line 300 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/map_util.cpp"

/** Flexpage unmapping.
    divert to mem_fpage_unmap (for memory fpages) or
    io_fpage_unmap (for IO fpages)
    @param space address space that should be flushed
    @param fp    flexpage descriptor of address-space range that should
                 be flushed
    @param me_too If false, only flush recursive mappings.  If true,
                 additionally flush the region in the given address space.
    @param flush_mode determines which access privileges to remove.
    @return combined (bit-ORed) access status of unmapped physical pages
*/
// Don't inline -- it eats too much stack.
// inline NEEDS ["config.h", io_fpage_unmap]
L4_fpage::Rights
fpage_unmap(Space *space, L4_fpage fp, L4_map_mask mask, Kobject ***rl)
{
  L4_fpage::Rights ret(0);
  Space::Caps caps = space->caps();

  if ((caps & Space::Caps::io()) && (fp.is_iopage() || fp.is_all_spaces()))
    ret |= io_fpage_unmap(space, fp, mask);

  if ((caps & Space::Caps::obj()) && (fp.is_objpage() || fp.is_all_spaces()))
    ret |= obj_fpage_unmap(space, fp, mask, rl);

  if ((caps & Space::Caps::mem()) && (fp.is_mempage() || fp.is_all_spaces()))
    ret |= mem_fpage_unmap(space, fp, mask);

  return ret;
}
