// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_kobject_i_h
#define jdb_kobject_i_h
#line 141 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"

class Jdb_kobject_id_hdl : public Jdb_kobject_handler
{
public:
  virtual bool show_kobject(Kobject_common *, int) { return false; }
  virtual ~Jdb_kobject_id_hdl() {}

public:  
#line 150 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject.cpp"
  bool
  invoke(Kobject_common *o, Syscall_frame *f, Utcb *utcb);
};

#endif // jdb_kobject_i_h
