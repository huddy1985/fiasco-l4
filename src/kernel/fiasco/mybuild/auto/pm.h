// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef pm_h
#define pm_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/pm.cpp"

#include <cxx/dlist>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/pm.cpp"
#include "per_cpu_data.h"

//
// INTERFACE definition follows 
//

#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/pm.cpp"

class Pm_object : public cxx::D_list_item
{
private:
  typedef cxx::Sd_list<Pm_object, cxx::D_list_item_policy, cxx::Sd_list_head_policy<Pm_object>, true> List;
public:
  virtual void pm_on_suspend(Cpu_number) = 0;
  virtual void pm_on_resume(Cpu_number) = 0;
  virtual ~Pm_object() = 0;

  void register_pm(Cpu_number cpu)
  {
    _list.cpu(cpu).push_back(this);
  }

  static void run_on_suspend_hooks(Cpu_number cpu)
  {
    List &l = _list.cpu(cpu);
    for (List::R_iterator c = l.rbegin(); c != l.rend(); ++c)
      (*c)->pm_on_suspend(cpu);
  }

  static void run_on_resume_hooks(Cpu_number cpu)
  {
    List &l = _list.cpu(cpu);
    for (List::Iterator c = l.begin(); c != l.end(); ++c)
      (*c)->pm_on_resume(cpu);
  }

private:
  static Per_cpu<List> _list;
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 42 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/pm.cpp"


inline Pm_object::~Pm_object() {}

#endif // pm_h
