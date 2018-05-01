// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_input_task_h
#define jdb_input_task_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input_task.cpp"

#include "jdb_module.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input_task.cpp"
#include "types.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input_task.cpp"
#include "l4_types.h"

//
// INTERFACE definition follows 
//

#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input_task.cpp"


class Task;
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input_task.cpp"
class Space;
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input_task.cpp"
class Kobject;
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input_task.cpp"

class Jdb_input_task_addr
{
public:
  static char     first_char;
  static char     first_char_have_task;
private:
  static Kobject *_task;
  static Space   *_space;
  static Address  _addr;
public:
  typedef struct
    {
      char str[32];
      Jdb_module::Gotkey *gotkey;
    } Symbol;
  static Symbol   symbol;

public:  
#line 59 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input_task.cpp"
  static Task *
  task();
  
#line 64 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input_task.cpp"
  static Space *
  space();
  
#line 69 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input_task.cpp"
  static Address
  addr();
  
#line 74 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input_task.cpp"
  static Jdb_module::Action_code
  action(void *&args, char const *&fmt, int &next_char);

private:  
#line 51 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input_task.cpp"
  static void
  gotkey_complete_symbol(char *&str, int maxlen, int c);
};

#endif // jdb_input_task_h
