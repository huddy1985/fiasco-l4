// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef mapping_h
#define mapping_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/mapping-ia32-32.cpp"

#include "types.h"
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"

#include "types.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"
#include "mapdb_types.h"

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/mapping-ia32-32.cpp"

class Treemap;
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"

class Space;
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/mapping-ia32-32.cpp"

class Mapping_entry
{
public:
  enum { Alignment = 1 };

  union 
    {
      struct 
	{
	  unsigned long _space:32;	///< Address-space number
	  unsigned long address:20;	///< Virtual address in address space
        } __attribute__((packed)) data;
      Treemap *_submap;
    } __attribute__((packed));
  Unsigned8 _depth;

  void set_space(Space *s) { data._space = (unsigned long)s; }
  Space *space() const { return (Space *)data._space; }
} __attribute__((packed));
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"
/** Represents one mapping in a mapping tree.
    Instances of Mapping ("mappings") work as an iterator over a
    mapping tree.  Mapping trees are never visible on the user level.
    Mappings are looked up directly in the mapping database (class
    Mapdb) using Mapdb::lookup().  When carrying out such a
    lookup, the mapping database locks the corresponding mapping tree
    before returning the mapping.  This mapping can the be used to
    iterate over the tree and to look up other mappings in the tree.
    The mapping tree is unlocked (and all mappings pointing into it
    become invalid) when Mapdb::free is called with any one of its
    mappings.
 */
class Mapping
{
  friend class Jdb_mapdb;
public:
  typedef Mdb_types::Order Order;
  typedef Mdb_types::Pcnt Pcnt;
  typedef Mdb_types::Pfn Pfn;
  struct Page_t;
  typedef cxx::int_type_order<Address, Page_t, Order> Page;

  enum Mapping_depth
  {
    Depth_root = 0, Depth_max = 252, 
    Depth_submap = 253, Depth_empty = 254, Depth_end = 255 
  };

  enum { Alignment = Mapping_entry::Alignment };

  // CREATORS
  Mapping(const Mapping&);	// this constructor is undefined.

  // DATA
  Mapping_entry _data;
  static_assert (__alignof__(Mapping_entry) == Alignment, "WRONG ALIGNMENT");

public:  
#line 51 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"
  inline Mapping();
  
#line 68 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"
  /** Address space.
      @return the address space into which the frame is mapped. 
   */
  
  inline Space *
  space() const;
  
#line 78 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"
  /** Set address space.
      @param space the address space into which the frame is mapped. 
   */
  
  inline void
  set_space(Space *space);
  
#line 88 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"
  /** Virtual address.
      @return the virtual address at which the frame is mapped.
   */
  
  inline Mapping::Page
  page() const;
  
#line 99 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"
  inline Mapping::Pfn
  pfn(Mapping::Order order) const;
  
#line 105 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"
  /** Set virtual address.
      @param address the virtual address at which the frame is mapped.
   */
  
  inline void
  set_page(Page address);
  
#line 115 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"
  /** Depth of mapping in mapping tree. */
  
  inline unsigned 
  depth() const;
  
#line 123 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"
  /** Set depth of mapping in mapping tree. */
  
  inline void 
  set_depth(unsigned depth);
  
#line 131 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"
  /** free entry?.
      @return true if this is unused.
   */
  
  inline bool
  unused() const;
  
#line 142 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"
  inline bool
  is_end_tag() const;
  
#line 149 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"
  inline Treemap *
  submap() const;
  
#line 158 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"
  inline void
  set_submap(Treemap *treemap);
  
#line 166 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"
  inline void
  set_unused();
  
#line 172 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"
  /** Parent.
      @return parent mapping of this mapping.
   */
  Mapping *
  parent();

private:  
#line 55 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"
  inline Mapping_entry *
  data();
  
#line 62 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"
  inline const Mapping_entry *
  data() const;
} __attribute__((packed, aligned(__alignof__(Mapping_entry))));

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 49 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"


inline Mapping::Mapping()
{}

#line 53 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"


inline Mapping_entry *
Mapping::data()
{
  return &_data;
}

#line 60 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"


inline const Mapping_entry *
Mapping::data() const
{
  return &_data;
}

#line 67 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"

/** Address space.
    @return the address space into which the frame is mapped. 
 */

inline Space *
Mapping::space() const
{
  return data()->space();
}

#line 77 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"

/** Set address space.
    @param space the address space into which the frame is mapped. 
 */

inline void
Mapping::set_space(Space *space)
{
  data()->set_space(space);
}

#line 87 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"

/** Virtual address.
    @return the virtual address at which the frame is mapped.
 */

inline Mapping::Page
Mapping::page() const
{
  return Page(data()->data.address);
}

#line 97 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"


inline Mapping::Pfn
Mapping::pfn(Mapping::Order order) const
{
  return Pfn(data()->data.address) << order;
}

#line 104 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"

/** Set virtual address.
    @param address the virtual address at which the frame is mapped.
 */

inline void
Mapping::set_page(Page address)
{
  data()->data.address = cxx::int_value<Page>(address);
}

#line 114 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"

/** Depth of mapping in mapping tree. */

inline unsigned 
Mapping::depth() const
{
  return data()->_depth;
}

#line 122 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"

/** Set depth of mapping in mapping tree. */

inline void 
Mapping::set_depth(unsigned depth)
{
  data()->_depth = depth;
}

#line 130 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"

/** free entry?.
    @return true if this is unused.
 */

inline bool
Mapping::unused() const
{
  return depth() >= Depth_empty;
}

#line 140 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"


inline bool
Mapping::is_end_tag() const
{
  return depth() == Depth_end;
}

#line 147 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"


inline Treemap *
Mapping::submap() const
{
  return (data()->_depth == Depth_submap) 
    ? data()->_submap
    : 0;
}

#line 156 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"


inline void
Mapping::set_submap(Treemap *treemap)
{
  data()->_submap = treemap;
  data()->_depth = Depth_submap;
}

#line 164 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mapping.cpp"


inline void
Mapping::set_unused()
{
  data()->_depth = Depth_empty;
}

#endif // mapping_h
