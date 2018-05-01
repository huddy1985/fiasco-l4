// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_entry_frame_h
#define jdb_entry_frame_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"

#include "cpu.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"
#include "tb_entry.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"
#include "trap_state.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"
#include "tb_entry.h"

//
// INTERFACE definition follows 
//

#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"

class Jdb_entry_frame : public Trap_state
{
public:  
#line 36 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"
  inline bool
  debug_ipi() const;
  
#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"
  inline Address_type
  from_user() const;
  
#line 46 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"
  inline Address
  ksp() const;
  
#line 51 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"
  inline Address
  sp() const;
  
#line 56 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"
  inline Mword
  param() const;
  
#line 65 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"
  inline Mword
  get_reg(unsigned reg) const;
  
#line 126 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"
  inline Mword
  ss() const;
};
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"

class Jdb_output_frame : public Jdb_entry_frame
{
public:  
#line 142 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"
  inline Unsigned8*
  str() const;
  
#line 147 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"
  inline int
  len() const;
};
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"

class Jdb_status_page_frame : public Jdb_entry_frame
{
public:  
#line 151 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"
  //---------------------------------------------------------------------------
  
  inline void
  set(Address status_page);
};
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"

class Jdb_log_frame : public Jdb_entry_frame
{
public:  
#line 157 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"
  //---------------------------------------------------------------------------
  
  inline Unsigned8*
  str() const;
  
#line 164 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"
  inline void
  set_tb_entry(Tb_entry* tb_entry);
};
#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"

class Jdb_log_3val_frame : public Jdb_log_frame
{
public:  
#line 168 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"
  //---------------------------------------------------------------------------
  
  inline Mword
  val1() const;
  
#line 175 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"
  inline Mword
  val2() const;
  
#line 180 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"
  inline Mword
  val3() const;
};
#line 22 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"

class Jdb_debug_frame : public Jdb_entry_frame
{
public:  
#line 184 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"
  //---------------------------------------------------------------------------
  
  inline Mword
  addr() const;
  
#line 191 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"
  inline Mword
  size() const;
};
#line 25 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"

class Jdb_symbols_frame : public Jdb_debug_frame
{};
#line 28 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"

class Jdb_lines_frame : public Jdb_debug_frame
{};
#line 31 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"

//---------------------------------------------------------------------------


//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 34 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"


inline bool
Jdb_entry_frame::debug_ipi() const
{ return _trapno == 0xee; }

#line 39 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"


inline Address_type
Jdb_entry_frame::from_user() const
{ return cs() & 3 ? ADDR_USER : ADDR_KERNEL; }

#line 44 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"


inline Address
Jdb_entry_frame::ksp() const
{ return (Address)&_sp; }

#line 49 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"


inline Address
Jdb_entry_frame::sp() const
{ return from_user() ? _sp : ksp(); }

#line 54 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"


inline Mword
Jdb_entry_frame::param() const
{ return _ax; }

#line 63 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"


inline Mword
Jdb_entry_frame::get_reg(unsigned reg) const
{
  Mword val = 0;

  switch (reg)
    {
    case 1:  val = _ax; break;
    case 2:  val = _bx; break;
    case 3:  val = _cx; break;
    case 4:  val = _dx; break;
    case 5:  val = _bp; break;
    case 6:  val = _si; break;
    case 7:  val = _di; break;
    case 8:  val = _ip; break;
    case 9:  val = _sp; break;
    case 10: val = _flags; break;
    }

  return val;
}

#line 124 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"


inline Mword
Jdb_entry_frame::ss() const
{ return from_user() ? _ss : Cpu::get_ss(); }

#line 140 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"


inline Unsigned8*
Jdb_output_frame::str() const
{ return (Unsigned8*)_ax; }

#line 145 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"


inline int
Jdb_output_frame::len() const
{ return (unsigned)_bx; }

#line 150 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"

//---------------------------------------------------------------------------

inline void
Jdb_status_page_frame::set(Address status_page)
{ _ax = (Mword)status_page; }

#line 156 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"

//---------------------------------------------------------------------------

inline Unsigned8*
Jdb_log_frame::str() const
{ return (Unsigned8*)_dx; }

#line 162 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"


inline void
Jdb_log_frame::set_tb_entry(Tb_entry* tb_entry)
{ _ax = (Mword)tb_entry; }

#line 167 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"

//---------------------------------------------------------------------------

inline Mword
Jdb_log_3val_frame::val1() const
{ return _cx; }

#line 173 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"


inline Mword
Jdb_log_3val_frame::val2() const
{ return _si; }

#line 178 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"


inline Mword
Jdb_log_3val_frame::val3() const
{ return _di; }

#line 183 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"

//---------------------------------------------------------------------------

inline Mword
Jdb_debug_frame::addr() const
{ return _ax; }

#line 189 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_entry_frame-ia32.cpp"


inline Mword
Jdb_debug_frame::size() const
{ return _dx; }

#endif // jdb_entry_frame_h
