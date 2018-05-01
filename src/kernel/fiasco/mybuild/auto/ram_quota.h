// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef ram_quota_h
#define ram_quota_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ram_quota.cpp"

#include <cstddef>

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ram_quota.cpp"

class Ram_quota
{
public:
  static Ram_quota *root;
  virtual ~Ram_quota() = 0;

private:
  Ram_quota *_parent;
  unsigned long _current;
  unsigned long _max;

public:  
#line 28 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ram_quota.cpp"
  inline void *
  operator new (size_t, void *b) throw();
  
#line 33 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ram_quota.cpp"
  Ram_quota();
  
#line 40 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ram_quota.cpp"
  Ram_quota(Ram_quota *p, unsigned long max);
  
#line 45 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ram_quota.cpp"
  unsigned long
  current() const;
  
#line 50 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ram_quota.cpp"
  bool
  alloc(signed long bytes);
  
#line 64 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ram_quota.cpp"
  inline void
  free(signed long bytes);
  
#line 70 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ram_quota.cpp"
  inline Ram_quota*
  parent() const;
  
#line 75 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ram_quota.cpp"
  inline unsigned long
  limit() const;
  
#line 80 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ram_quota.cpp"
  inline bool
  unlimited() const;
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 26 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ram_quota.cpp"


inline void *
Ram_quota::operator new (size_t, void *b) throw()
{ return b; }

#line 62 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ram_quota.cpp"


inline void
Ram_quota::free(signed long bytes)
{ alloc(-bytes); }

#line 67 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ram_quota.cpp"



inline Ram_quota*
Ram_quota::parent() const
{ return _parent; }

#line 73 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ram_quota.cpp"


inline unsigned long
Ram_quota::limit() const
{ return _max; }

#line 78 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ram_quota.cpp"


inline bool
Ram_quota::unlimited() const
{ return _max == ~0UL; }

#line 24 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ram_quota.cpp"

inline Ram_quota::~Ram_quota() {}

#endif // ram_quota_h
