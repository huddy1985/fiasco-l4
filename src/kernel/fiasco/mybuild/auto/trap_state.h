// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef trap_state_h
#define trap_state_h
#line 3 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"

#include "l4_types.h"

//
// INTERFACE definition follows 
//

#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"

class Trap_state
{
  friend class Jdb_tcb;
  friend class Jdb_stack_view;

public:
  typedef FIASCO_FASTCALL int (*Handler)(Trap_state*, unsigned cpu);
  static Handler base_handler asm ("BASE_TRAP_HANDLER");

  // Saved segment registers
  Mword  _es;
  Mword  _ds;
  Mword  _gs;                                     // => utcb->values[ 0]
  Mword  _fs;                                     // => utcb->values[ 1]

  // PUSHA register state frame
  Mword  _di;                                     // => utcb->values[ 2]
  Mword  _si;                                     // => utcb->values[ 3]
  Mword  _bp;                                     // => utcb->values[ 4]
  Mword  _cr2; // we save cr2 over esp for PFs    // => utcb->values[ 5]
  Mword  _bx;                                     // => utcb->values[ 6]
  Mword  _dx;                                     // => utcb->values[ 7]
  Mword  _cx;                                     // => utcb->values[ 8]
  Mword  _ax;                                     // => utcb->values[ 9]

  // Processor trap number, 0-31
  Mword  _trapno;                                 // => utcb->values[10]

  // Error code pushed by the processor, 0 if none
  Mword  _err;                                    // => utcb->values[11]

  // Processor state frame
  Mword  _ip;                                     // => utcb->values[12]
  Mword  _cs;                                     // => utcb->values[13]
  Mword  _flags;                                  // => utcb->values[14]
  Mword  _sp;                                     // => utcb->values[15]
  Mword  _ss;

public:  
#line 82 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline void
  sanitize_user_state();
  
#line 117 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline void
  copy_and_sanitize(Trap_state const *src);
  
#line 125 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline void
  set_pagefault(Mword pfa, Mword error);
  
#line 134 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline Mword
  trapno() const;
  
#line 139 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline Mword
  error() const;
  
#line 144 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline Mword
  ip() const;
  
#line 149 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline Mword
  cs() const;
  
#line 154 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline Mword
  flags() const;
  
#line 159 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline Mword
  sp() const;
  
#line 164 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline Mword
  ss() const;
  
#line 169 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline Mword
  value() const;
  
#line 174 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline Mword
  value2() const;
  
#line 179 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline Mword
  dx() const;
  
#line 184 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline Mword
  value3() const;
  
#line 189 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline Mword
  value4() const;
  
#line 194 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline void
  ip(Mword ip);
  
#line 199 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline void
  cs(Mword cs);
  
#line 204 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline void
  flags(Mword flags);
  
#line 209 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline void
  sp(Mword sp);
  
#line 214 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline void
  ss(Mword ss);
  
#line 219 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline void
  value(Mword value);
  
#line 224 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline void
  value3(Mword value);
  
#line 229 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline void
  consume_instruction(unsigned count);
  
#line 234 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline bool
  is_debug_exception() const;
  
#line 239 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  void
  dump();
  
#line 281 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
  inline bool
  exclude_logging();
};
#line 44 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"

struct Trex
{
  Trap_state s;

  void set_ipc_upcall()
  {
    s._err = 0;
    s._trapno = 0xfe;
  }

  void dump() { s.dump(); }
};
#line 57 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"

namespace Ts
{
  enum
  {
    /// full number of words in a Trap_state
    Words = sizeof(Trap_state) / sizeof(Mword),
    /// words for the IRET frame at the end of the trap state
    Iret_words = 5,
    /// words for error code and trap number
    Code_words = 2,
    /// offset of the IRET frame
    Iret_offset = Words - Iret_words,
    /// number of words used for normal registers
    Reg_words = Words - Iret_words - Code_words,
  };
}
#line 74 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"

//---------------------------------------------------------------------------


#line 272 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
extern "C" FIASCO_FASTCALL
void
trap_dump_panic(Trap_state *ts);

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 77 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"

#include "regdefs.h"
#line 79 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
#include "gdt.h"
#line 111 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
#include "atomic.h"
#line 112 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"
#include "mem.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 80 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline void
Trap_state::sanitize_user_state()
{
  _cs = Gdt::gdt_code_user | Gdt::Selector_user;
  _ss = Gdt::gdt_data_user | Gdt::Selector_user;
  _flags = (_flags & ~(EFLAGS_IOPL | EFLAGS_NT)) | EFLAGS_IF;
}

#line 115 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline void
Trap_state::copy_and_sanitize(Trap_state const *src)
{
  Mem::memcpy_mwords(this, src, sizeof(*this) / sizeof(Mword));
  sanitize_user_state();
}

#line 123 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline void
Trap_state::set_pagefault(Mword pfa, Mword error)
{
  _cr2 = pfa;
  _trapno = 0xe;
  _err = error;
}

#line 132 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline Mword
Trap_state::trapno() const
{ return _trapno; }

#line 137 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline Mword
Trap_state::error() const
{ return _err; }

#line 142 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline Mword
Trap_state::ip() const
{ return _ip; }

#line 147 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline Mword
Trap_state::cs() const
{ return _cs; }

#line 152 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline Mword
Trap_state::flags() const
{ return _flags; }

#line 157 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline Mword
Trap_state::sp() const
{ return _sp; }

#line 162 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline Mword
Trap_state::ss() const
{ return _ss; }

#line 167 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline Mword
Trap_state::value() const
{ return _ax; }

#line 172 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline Mword
Trap_state::value2() const
{ return _cx; }

#line 177 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline Mword
Trap_state::dx() const
{ return _dx; }

#line 182 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline Mword
Trap_state::value3() const
{ return _dx; }

#line 187 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline Mword
Trap_state::value4() const
{ return _bx; }

#line 192 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline void
Trap_state::ip(Mword ip)
{ _ip = ip; }

#line 197 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline void
Trap_state::cs(Mword cs)
{ _cs = cs; }

#line 202 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline void
Trap_state::flags(Mword flags)
{ _flags = flags; }

#line 207 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline void
Trap_state::sp(Mword sp)
{ _sp = sp; }

#line 212 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline void
Trap_state::ss(Mword ss)
{ _ss = ss; }

#line 217 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline void
Trap_state::value(Mword value)
{ _ax = value; }

#line 222 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline void
Trap_state::value3(Mword value)
{ _dx = value; }

#line 227 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"

 
inline void
Trap_state::consume_instruction(unsigned count)
{ cas ((Address*)(&_ip), _ip, _ip + count); }

#line 232 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline bool
Trap_state::is_debug_exception() const
{ return _trapno == 1 || _trapno == 3; }

#line 279 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/trap_state.cpp"


inline bool
Trap_state::exclude_logging()
{ return _trapno == 1 || _trapno == 3; }

#endif // trap_state_h
