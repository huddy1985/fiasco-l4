// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_attach_irq_i_h
#define jdb_attach_irq_i_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"

#include <cstdio>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"

#include "irq_chip.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
#include "irq.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
#include "semaphore.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
#include "irq_mgr.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
#include "jdb_module.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
#include "kernel_console.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
#include "static_init.h"
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
#include "thread.h"
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
#include "types.h"
#line 93 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"

#include "jdb_kobject.h"
#line 95 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
#include "irq.h"
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"


//===================
// Std JDB modules
//===================

/**
 * 'IRQ' module.
 *
 * This module handles the 'R' command that
 * provides IRQ attachment and listing functions.
 */
class Jdb_attach_irq : public Jdb_module
{
public:
  Jdb_attach_irq() FIASCO_INIT;
private:
  static char     subcmd;

public:  
#line 43 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
  Jdb_module::Action_code
  action( int cmd, void *&args, char const *&, int & );
  
#line 73 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
  int
  num_cmds() const;
  
#line 80 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
  Jdb_module::Cmd const *
  cmds() const;
};
#line 96 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"

class Jdb_kobject_irq : public Jdb_kobject_handler
{

public:  
#line 103 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
  inline Jdb_kobject_irq();
  
#line 111 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
  bool
  handle_key(Kobject_common *o, int key);
  
#line 121 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
  Kobject_common *
  follow_link(Kobject_common *o);
  
#line 130 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
  bool
  show_kobject(Kobject_common *, int);
  
#line 135 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
  void
  show_kobject_short(String_buffer *buf, Kobject_common *o);
};

//
// IMPLEMENTATION of inline functions follows
//


#line 100 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"



inline Jdb_kobject_irq::Jdb_kobject_irq()
  : Jdb_kobject_handler((Irq*)0)
{
  Jdb_kobject::module()->register_handler(this);
}

#endif // jdb_attach_irq_i_h
