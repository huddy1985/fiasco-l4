// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_report_i_h
#define jdb_report_i_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_report.cpp"

#include <cstdio>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_report.cpp"

#include "kobject.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_report.cpp"
#include "string_buffer.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_report.cpp"

#include "jdb.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_report.cpp"
#include "jdb_module.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_report.cpp"
#include "jdb_kobject.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_report.cpp"
#include "jdb_screen.h"
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_report.cpp"


class Jdb_report : public Jdb_module
{
  static char subcmd;

public:
  Jdb_report() : Jdb_module("INFO") {}

public:  
#line 51 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_report.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&, char const *&, int &);
  
#line 118 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_report.cpp"
  int
  num_cmds() const;
  
#line 123 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_report.cpp"
  Jdb_module::Cmd const *
  cmds() const;

private:  
#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_report.cpp"
  void
  show_objects();
  
#line 42 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_report.cpp"
  void
  delim(const char *text = 0);
};

#endif // jdb_report_i_h
