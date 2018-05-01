// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef entry_frame_h
#define entry_frame_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/entry_frame.cpp"

#include "l4_types.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"

#include "types.h"

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/entry_frame.cpp"

class Syscall_pre_frame {};
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/entry_frame.cpp"
class Syscall_post_frame {};
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/entry_frame.cpp"

/**
 * Encapsulation of syscall data.
 *
 * This class must be defined in arch dependent parts
 * and has to represent the data necessary for a 
 * system call as laid out on the kernel stack. 
 */
class Syscall_frame
{
public:

  L4_obj_ref ref() const;
  void ref(L4_obj_ref const &ref);
  Utcb *utcb() const;
  L4_msg_tag tag() const;
  void tag(L4_msg_tag const &tag);

  L4_timeout_pair timeout() const;
  void timeout(L4_timeout_pair const &to);

  Mword from_spec() const;
  void from(Mword id);

#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"
private:

protected:
  Mword             _ecx;
  Mword             _edx;
  Mword             _esi;
  Mword             _edi;
  Mword             _ebx;
  Mword             _ebp;
  Mword             _eax;
};
#line 31 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/entry_frame.cpp"


class Return_frame
{
public:
  Mword ip() const;
  Mword ip_syscall_page_user() const;
  void  ip(Mword _pc);

  Mword sp() const;
  void  sp(Mword _sp);

#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"
private:

private:
  Mword             _eip;
  Unsigned16  _cs, __attribute__((unused)) __csu;
  Mword          _eflags;
  Mword             _esp;
  Unsigned16  _ss, __attribute__((unused)) __ssu;

public:
  enum { Pf_ax_offset = 0 };

public:  
#line 69 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"
  inline Mword 
  flags() const;
  
#line 74 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"
  inline void
  flags(Mword flags);
  
#line 79 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"
  inline Mword
  cs() const;
  
#line 84 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"
  inline void
  cs(Mword cs);
  
#line 89 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"
  inline Mword
  ss() const;
  
#line 94 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"
  inline void
  ss(Mword ss);
};
#line 43 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/entry_frame.cpp"

/**
 * Encapsulation of a syscall entry kernel stack.
 *
 * This class encapsulates the complete top of the 
 * kernel stack after a syscall (including the 
 * iret return frame).
 */
class Entry_frame
: public Syscall_post_frame,
  public Syscall_frame,
  public Syscall_pre_frame,
  public Return_frame
{
public:
  static Entry_frame *to_entry_frame(Syscall_frame *sf)
  { return nonull_static_cast<Entry_frame *>(sf); }

  Syscall_frame *syscall_frame() { return this; }
  Syscall_frame const *syscall_frame() const { return this; }
} __attribute__((packed));
#line 64 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/entry_frame.cpp"


/*
 * Fiasco Kernel-Entry Frame-Layout Code
 * Shared between UX and native IA32.
 */



//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 36 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"

//---------------------------------------------------------------------------
// basic Entry_frame methods for IA32
// 
#include "mem_layout.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 100 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"

//---------------------------------------------------------------------------
// IPC frame methods for IA32
// 

inline Mword Syscall_frame::from_spec() const
{ return _esi; }

#line 107 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"


inline void Syscall_frame::from(Mword f)
{ _esi = f; }

#line 111 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"


inline L4_obj_ref Syscall_frame::ref() const
{ return L4_obj_ref::from_raw(_edx); }

#line 115 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"


inline void Syscall_frame::ref(L4_obj_ref const &ref)
{ _edx = ref.raw(); }

#line 119 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"


inline L4_timeout_pair Syscall_frame::timeout() const
{ return L4_timeout_pair(_ecx); }

#line 123 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"


inline void Syscall_frame::timeout(L4_timeout_pair const &to)
{ _ecx = to.raw(); }

#line 127 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"

inline Utcb *Syscall_frame::utcb() const
{ return reinterpret_cast<Utcb*>(_edi); }

#line 130 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"

inline L4_msg_tag Syscall_frame::tag() const
{ return L4_msg_tag(_eax); }

#line 133 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"


inline void Syscall_frame::tag(L4_msg_tag const &tag)
{ _eax = tag.raw(); }

#line 67 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"


inline Mword 
Return_frame::flags() const
{ return _eflags; }

#line 72 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"


inline void
Return_frame::flags(Mword flags)
{ _eflags = flags; }

#line 77 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"


inline Mword
Return_frame::cs() const
{ return _cs; }

#line 82 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"


inline void
Return_frame::cs(Mword cs)
{ _cs = cs; }

#line 87 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"


inline Mword
Return_frame::ss() const
{ return _ss; }

#line 92 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"


inline void
Return_frame::ss(Mword ss)
{ _ss = ss; }

#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"


inline Address
Return_frame::ip() const
{ return _eip; }

#line 46 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"


inline Address
Return_frame::ip_syscall_page_user() const
{
  Address eip = ip();
  if ((eip & Mem_layout::Syscalls) == Mem_layout::Syscalls)
     eip = *(Mword*)sp();
  return eip;
}

#line 56 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"



inline Address
Return_frame::sp() const
{ return _esp; }

#line 62 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"


inline void
Return_frame::sp(Mword sp)
{ _esp = sp; }

#line 141 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/entry_frame-ia32-ux.cpp"


inline void
Return_frame::ip(Mword ip)
{
  // We have to consider a special case where we have to leave the kernel
  // with iret instead of sysexit: If the target thread entered the kernel
  // through sysenter, it would leave using sysexit. This is not possible
  // for two reasons: Firstly, the sysexit instruction needs special user-
  // land code to load the right value into the edx register (see user-
  // level sysenter bindings). And secondly, the sysexit instruction
  // decrements the user-level eip value by two to ensure that the fixup
  // code is executed. One solution without kernel support would be to add
  // the instructions "movl %ebp, %edx" just _before_ the code the target
  // eip is set to.
  if (cs() & 0x80)
    {
      // this cannot happen in Fiasco UX
      /* symbols from the assembler entry code */
      extern Mword leave_from_sysenter_by_iret;
      extern Mword leave_alien_from_sysenter_by_iret;
      extern Mword ret_from_fast_alien_ipc;
      Mword **ret_from_disp_syscall = reinterpret_cast<Mword**>(static_cast<Entry_frame*>(this))-1;
      cs(cs() & ~0x80);
      if (*ret_from_disp_syscall == &ret_from_fast_alien_ipc)
	*ret_from_disp_syscall = &leave_alien_from_sysenter_by_iret;
      else
	*ret_from_disp_syscall = &leave_from_sysenter_by_iret;
    }

  _eip = ip;
}

#endif // entry_frame_h
