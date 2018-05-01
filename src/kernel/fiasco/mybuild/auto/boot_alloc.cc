// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "boot_alloc.h"
#include "boot_alloc_i.h"

#line 37 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/boot_alloc.cpp"

Boot_alloced::Block_list Boot_alloced::_free;

#line 39 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/boot_alloc.cpp"


void *
Boot_alloced::alloc(size_t size)
{
  if (Debug_boot_alloc)
    printf("Boot_alloc: size=0x%lx\n", (unsigned long)size);

  // this is best fit list-based allocation

  Block_list::Iterator best = _free.end();
  for (Block_list::Iterator curr = _free.begin(); curr != _free.end(); ++curr)
    {
      if (((best == _free.end()) || curr->size < best->size)
	  && curr->size >= size)
	best = curr;
    }

  if (best == _free.end())
    {
      // start from 1k
      unsigned long alloc_size = 1024;

      // look for a size suitable and buddy friendly
      while (alloc_size < size)
	alloc_size <<= 1;

      Block *b = (Block*)Kmem_alloc::allocator()->unaligned_alloc(alloc_size);
      if (Debug_boot_alloc)
        printf("Boot_alloc: allocated extra memory block @%p (size=%lx)\n",
               b, alloc_size);

      if (!b)
	return 0;

      b->size = alloc_size;
      _free.add(b);
      best = _free.begin();
    }


  void *b = *best;
  Block *rem = (Block *)(((Address)b + size + sizeof(Block) - 1) & ~(sizeof(Block) - 1));
  long rem_sz = (Address)b + (*best)->size - (Address)rem;
  if (Debug_boot_alloc)
    printf("Boot_alloc: @ %p\n", b);
  if (rem_sz > (long)sizeof(Block))
    {
      rem->size = rem_sz;
      _free.replace(best, rem);
      if (Debug_boot_alloc)
        printf("Boot_alloc: remaining free block @ %p (size=%lx)\n", rem, (unsigned long)rem_sz);
    }
  else
    _free.erase(best);

  memset(b, 0, size);
  return b;
}

#line 113 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/boot_alloc.cpp"

void
Boot_alloced::operator delete (void *b)
{
  WARN("Boot_alloc: trying to delete boot-time allocated object @ %p\n", b);
}

#line 119 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/boot_alloc.cpp"

void
Boot_alloced::operator delete[] (void *b)
{
  WARN("Boot_alloc: trying to delete boot-time allocated object @ %p\n", b);
}
