// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef mappable_h
#define mappable_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mappable.cpp"

#include "mapping_tree.h"

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mappable.cpp"

class Mappable : public Base_mappable
{
public:
  bool no_mappings() const;
  virtual ~Mappable() = 0;
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mappable.cpp"

inline Mappable::~Mappable() {}

#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mappable.cpp"


inline bool
Mappable::no_mappings() const
{
  return !tree.get() || tree.get()->is_empty();
}

#endif // mappable_h
