// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_object_i_h
#define jdb_object_i_h
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/jdb_object.cpp"

#include "globals.h"
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/jdb_object.cpp"
#include "jdb.h"
#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/jdb_object.cpp"
#include "kobject_helper.h"
#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/jdb_object.cpp"
#include "kobject_rpc.h"
#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/jdb_object.cpp"
#include "minmax.h"
#line 22 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/jdb_object.cpp"

class Jdb_object : public Kobject_h<Jdb_object, Kobject>
{
public:
  enum
  {
    Jdb_enter      = 0,
    Jdb_outchar    = 1,
    Jdb_outnstring = 2,
    Jdb_outhex32   = 3,
    Jdb_outhex20   = 4,
    Jdb_outhex16   = 5,
    Jdb_outhex12   = 6,
    Jdb_outhex8    = 7,
    Jdb_outdec     = 8,

    // 0x200 prefix for tbuf opcodes
    Tbuf_log       = 1,
    Tbuf_clear     = 2,
    Tbuf_dump      = 3,
    Tbuf_log_3val  = 4,
    Tbuf_log_bin   = 5,
  };

  Jdb_object()
  {
    initial_kobjects.register_obj(this, Initial_kobjects::Jdb);
  }

public:  
#line 252 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/jdb_object.cpp"
  L4_msg_tag
  kinvoke(L4_obj_ref, L4_fpage::Rights rights, Syscall_frame *f,
                      Utcb const *r_msg, Utcb *s_msg);

private:  
#line 59 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/jdb_object.cpp"
  inline L4_msg_tag
  sys_kobject_debug(L4_msg_tag tag, unsigned op,
                                L4_fpage::Rights rights,
                                Syscall_frame *f,
                                Utcb const *r_msg, Utcb *);
  
#line 79 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/jdb_object.cpp"
  inline L4_msg_tag
  sys_tbuf(L4_msg_tag tag, unsigned op,
                       L4_fpage::Rights,
                       Syscall_frame *,
                       Utcb const *r_msg, Utcb *);
  
#line 179 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/jdb_object.cpp"
  inline L4_msg_tag
  sys_jdb(L4_msg_tag tag, unsigned op,
                      L4_fpage::Rights,
                      Syscall_frame *,
                      Utcb const *r_msg, Utcb *);
};

#endif // jdb_object_i_h
