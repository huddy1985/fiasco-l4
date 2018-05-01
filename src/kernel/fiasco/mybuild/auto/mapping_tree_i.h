// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef mapping_tree_i_h
#define mapping_tree_i_h
#line 276 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping_tree.cpp"

template<int SIZE_ID_MAX>
struct Mapping_tree_allocators;
#line 260 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping_tree.cpp"

template<int SIZE_ID>
struct Mapping_tree_allocator
{
  Kmem_slab a;
  enum
  {
    Elem_size = (Size_factor << SIZE_ID) * sizeof (Mapping)
                + ((sizeof(Mapping_tree) + Mapping::Alignment - 1)
                   & ~((unsigned long)Mapping::Alignment - 1))
  };

  Mapping_tree_allocator(Kmem_slab **array)
  : a(Elem_size, Mapping::Alignment, "Mapping_tree")
  { array[SIZE_ID] = &a; }
};
#line 279 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping_tree.cpp"

template<>
struct Mapping_tree_allocators<0>
{
  Mapping_tree_allocator<0> a;
  Mapping_tree_allocators(Kmem_slab **array) : a(array) {}
};
#line 286 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping_tree.cpp"

template<int SIZE_ID_MAX>
struct Mapping_tree_allocators
{

  Mapping_tree_allocator<SIZE_ID_MAX> a;
  Mapping_tree_allocators<SIZE_ID_MAX - 1> n;

  Mapping_tree_allocators(Kmem_slab **array) : a(array), n(array) {}
};

#endif // mapping_tree_i_h
