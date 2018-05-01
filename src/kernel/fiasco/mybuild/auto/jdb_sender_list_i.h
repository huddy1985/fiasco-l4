// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_sender_list_i_h
#define jdb_sender_list_i_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"

#include <cstdio>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"
#include <cstring>
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"

#include "thread_object.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"
#include "jdb.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"
#include "jdb_kobject.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"
#include "jdb_module.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"
#include "ipc_gate.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"


class Jdb_sender_list : public Jdb_module, public Jdb_kobject_handler
{
public:
  Jdb_sender_list() FIASCO_INIT;

  virtual bool show_kobject(Kobject_common *, int) { return true; }
private:
  static Kobject *object;

public:  
#line 98 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&, char const *&, int &);
  
#line 115 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"
  bool
  handle_key(Kobject_common *o, int keycode);
  
#line 133 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"
  int num_cmds() const;
  
#line 137 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"
  Jdb_module::Cmd const * cmds() const;

private:  
#line 29 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"
  void
  show_sender_list(Prio_list *t, int overlayprint,
                                    int printnone,
                                    const char *tag = 0, unsigned long dbgid = 0);
  
#line 80 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_sender_list.cpp"
  bool
  show_obj(Kobject *o, int printnone);
};

#endif // jdb_sender_list_i_h
