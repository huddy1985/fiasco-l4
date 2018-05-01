// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef vkey_h
#define vkey_h

//
// INTERFACE definition follows 
//

#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"

class Irq_base;
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"

class Vkey
{
public:
  enum Echo_type { Echo_off = 0, Echo_on = 1, Echo_crnl = 2 };

public:  
#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"
  static void
  irq(Irq_base *i);
  
#line 60 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"
  static void
  set_echo(Echo_type echo);
  
#line 110 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"
  static void
  add_char(int v);
  
#line 118 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"
  static int
  check_();
  
#line 173 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"
  static int
  get();
  
#line 183 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"
  static void
  clear();

private:  
#line 28 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"
  static inline bool
  is_debugger_entry_key(int key);
  
#line 67 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"
  static bool
  add(int c);
  
#line 92 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"
  static bool
  add(const char *seq);
  
#line 102 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"
  static void
  trigger();
};
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/vkey.cpp"


// ---------------------------------------------------------------------------


#endif // vkey_h
