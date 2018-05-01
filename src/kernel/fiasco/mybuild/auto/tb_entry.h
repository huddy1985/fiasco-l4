// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef tb_entry_h
#define tb_entry_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"

#include "l4_error.h"
#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"

#include "l4_types.h"

//
// INTERFACE definition follows 
//

#line 23 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"

class Tb_entry;
#line 25 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
class Context;
#line 26 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
class Space;
#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
class Sched_context;
#line 28 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
class Syscall_frame;
#line 29 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
class Trap_state;
#line 30 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
class Tb_entry_formatter;
#line 31 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
class String_buffer;
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"

enum Tbuf_entry_fixed
{
  Tbuf_unused             = 0,
  Tbuf_pf,
  Tbuf_ipc,
  Tbuf_ipc_res,
  Tbuf_ipc_trace,
  Tbuf_ke,
  Tbuf_ke_reg,
  Tbuf_breakpoint,
  Tbuf_ke_bin,
  Tbuf_dynentries,

  Tbuf_max                = 0x80,
  Tbuf_hidden             = 0x80,
};
#line 32 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"

struct Tb_log_table_entry
{
  char const *name;
  unsigned char *patch;
  Tb_entry_formatter *fmt;
};
#line 39 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"

extern Tb_log_table_entry _jdb_log_table[];
#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
extern Tb_log_table_entry _jdb_log_table_end;
#line 42 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"



class Tb_entry
{
protected:
  Mword		_number;	///< event number
  Address	_ip;		///< instruction pointer
  Unsigned64	_tsc;		///< time stamp counter
  Context const *_ctx;		///< Context
  Unsigned32	_pmc1;		///< performance counter value 1
  Unsigned32	_pmc2;		///< performance counter value 2
  Unsigned32	_kclock;	///< lower 32 bits of kernel clock
  Unsigned8	_type;		///< type of entry
  Unsigned8     _cpu;           ///< CPU

  static Mword (*rdcnt1)();
  static Mword (*rdcnt2)();

public:
  class Group_order
  {
  public:
    Group_order() : _o(0) {} // not grouped
    Group_order(unsigned v) : _o(2 + v) {}
    static Group_order none() { return Group_order(); }
    static Group_order last() { return Group_order(255, true); }
    static Group_order first() { return Group_order(0); }
    static Group_order direct() { return Group_order(1, true); }

    bool not_grouped() const { return _o == 0; }
    bool is_direct() const { return _o == 1; }
    bool is_first() const { return _o == 2; }
    bool is_last() const { return _o == 255; }
    bool grouped() const { return _o >= 2; }
    unsigned char depth() const { return _o - 2; }

  private:
    Group_order(unsigned char v, bool) : _o(v) {}
    unsigned char _o;
  };

  Group_order has_partner() const { return Group_order::none(); }
  Group_order is_partner(Tb_entry const *) const { return Group_order::none(); }
  Mword partner() const { return 0; }


#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
private:

public:
  enum
  {
    Tb_entry_size = 64,
  };

public:  
#line 322 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  static void
  set_rdcnt(int num, Mword (*f)());
  
#line 336 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  clear();
  
#line 341 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  set_global(char type, Context const *ctx, Address ip);
  
#line 352 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  hide();
  
#line 357 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  unhide();
  
#line 362 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Address
  ip() const;
  
#line 367 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Context const *
  ctx() const;
  
#line 372 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Unsigned8
  type() const;
  
#line 377 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline int
  hidden() const;
  
#line 382 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Mword
  number() const;
  
#line 387 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  number(Mword number);
  
#line 392 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  rdpmc1();
  
#line 397 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  rdpmc2();
  
#line 402 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Unsigned32
  kclock() const;
  
#line 407 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Unsigned8
  cpu() const;
  
#line 412 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Unsigned64
  tsc() const;
  
#line 417 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Unsigned32
  pmc1() const;
  
#line 422 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Unsigned32
  pmc2() const;
  
#line 29 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
  inline void
  rdtsc();

protected:  
#line 303 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  static Mword dummy_read_pmc();
} __attribute__((__packed__, __aligned__(8)));
#line 89 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


class Tb_entry_union : public Tb_entry
{
private:
  char _padding[Tb_entry_size - sizeof(Tb_entry)];
};
#line 96 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"

static_assert(sizeof(Tb_entry_union) == Tb_entry::Tb_entry_size,
              "Tb_entry_union has the wrong size");
#line 99 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"

struct Tb_entry_empty : public Tb_entry
{
  void print(String_buffer *) const {}
};
#line 104 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"

class Tb_entry_formatter
{
public:
  typedef Tb_entry::Group_order Group_order;

  virtual void print(String_buffer *, Tb_entry const *e) const = 0;
  virtual Group_order has_partner(Tb_entry const *e) const = 0;
  virtual Group_order is_pair(Tb_entry const *e, Tb_entry const *n) const = 0;
  virtual Mword partner(Tb_entry const *e) const = 0;

  static Tb_entry_formatter const *get_fmt(Tb_entry const *e)
  {
    if (e->type() >= Tbuf_dynentries)
      return _jdb_log_table[e->type() - Tbuf_dynentries].fmt;

    return _fixed[e->type()];
  }

private:
  static Tb_entry_formatter const *_fixed[];

public:  
#line 311 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  static void
  set_fixed(unsigned type, Tb_entry_formatter const *f);
};
#line 126 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


template< typename T >
class Tb_entry_formatter_t : public Tb_entry_formatter
{
public:
  Tb_entry_formatter_t() {}

  typedef T const *Const_ptr;
  typedef T *Ptr;

  void print(String_buffer *buf, Tb_entry const *e) const
  { static_cast<Const_ptr>(e)->print(buf); }

  Group_order has_partner(Tb_entry const *e) const
  { return static_cast<Const_ptr>(e)->has_partner(); }

  Group_order is_pair(Tb_entry const *e, Tb_entry const *n) const
  {
    //assert (get_fmt(e) == &singleton);

    if (&singleton == get_fmt(n))
      return static_cast<Const_ptr>(e)->is_partner(static_cast<Const_ptr>(n));
    return Tb_entry::Group_order::none();
  }

  Mword partner(Tb_entry const *e) const
  { return static_cast<Const_ptr>(e)->partner(); }

  static Tb_entry_formatter_t const singleton;
};
#line 157 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"

template<typename T>
Tb_entry_formatter_t<T> const Tb_entry_formatter_t<T>::singleton;
#line 160 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


/** logged ipc. */
class Tb_entry_ipc : public Tb_entry
{
private:
  L4_msg_tag	_tag;           ///< message tag
  Mword	_dword[2];	///< first two message words
  L4_obj_ref	_dst;		///< destination id
  Mword       _dbg_id;
  Mword       _label;
  L4_timeout_pair _timeout;	///< timeout
public:
  Tb_entry_ipc() : _timeout(0) {}
  void print(String_buffer *buf) const;

public:  
#line 428 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  set(Context const *ctx, Mword ip, Syscall_frame *ipc_regs, Utcb *utcb,
  		  Mword dbg_id, Unsigned64 left);
  
#line 450 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Mword
  ipc_type() const;
  
#line 455 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Mword
  dbg_id() const;
  
#line 460 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline L4_obj_ref
  dst() const;
  
#line 465 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline L4_timeout_pair
  timeout() const;
  
#line 470 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline L4_msg_tag
  tag() const;
  
#line 475 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Mword
  label() const;
  
#line 480 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Mword
  dword(unsigned index) const;
};
#line 176 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"

/** logged ipc result. */
class Tb_entry_ipc_res : public Tb_entry
{
private:
  L4_msg_tag	_tag;		///< message tag
  Mword	_dword[2];	///< first two dwords
  L4_error	_result;	///< result
  Mword	_from;		///< receive descriptor
  Mword	_pair_event;	///< referred event
  Unsigned8	_have_snd;	///< ipc had send part
  Unsigned8	_is_np;		///< next period bit set
public:
  void print(String_buffer *buf) const;

public:  
#line 486 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  set(Context const *ctx, Mword ip, Syscall_frame *ipc_regs,
                        Utcb *utcb,
  		      Mword result, Mword pair_event, Unsigned8 have_snd,
  		      Unsigned8 is_np);
  
#line 507 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline int
  have_snd() const;
  
#line 512 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline int
  is_np() const;
  
#line 517 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Mword
  from() const;
  
#line 522 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline L4_error
  result() const;
  
#line 527 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline L4_msg_tag
  tag() const;
  
#line 532 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Mword
  dword(unsigned index) const;
  
#line 537 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Mword
  pair_event() const;
};
#line 191 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"

/** logged ipc for user level tracing with Vampir. */
class Tb_entry_ipc_trace : public Tb_entry
{
private:
  Unsigned64	_snd_tsc;	///< entry tsc
  L4_msg_tag	_result;	///< result
  L4_obj_ref	_snd_dst;	///< send destination
  Mword	_rcv_dst;	///< rcv partner
  Unsigned8	_snd_desc;
  Unsigned8	_rcv_desc;
public:
  void print(String_buffer *buf) const;

public:  
#line 543 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  set(Context const *ctx, Mword ip, Unsigned64 snd_tsc,
  			L4_obj_ref const &snd_dst, Mword rcv_dst,
  			L4_msg_tag result, Unsigned8 snd_desc,
  			Unsigned8 rcv_desc);
};
#line 205 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


/** logged pagefault. */
class Tb_entry_pf : public Tb_entry
{
private:
  Address	_pfa;		///< pagefault address
  Mword	_error;		///< pagefault error code
  Space	*_space;
public:
  void print(String_buffer *buf) const;

public:  
#line 559 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  set(Context const *ctx, Address ip, Address pfa,
  		 Mword error, Space *spc);
  
#line 570 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Mword
  error() const;
  
#line 575 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Address
  pfa() const;
  
#line 580 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Space*
  space() const;
};
#line 217 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"

/** logged kernel event. */
template<unsigned BASE_SIZE>
union Tb_entry_msg
{
  char msg[Tb_entry::Tb_entry_size - BASE_SIZE];
  struct Ptr
  {
    char tag[2];
    char const *ptr;
  } mptr;

  void set_const(char const *msg)
  {
    mptr.tag[0] = 0;
    mptr.tag[1] = 1;
    mptr.ptr = msg;
  }

  void set_buf(unsigned i, char c)
  {
    if (i < sizeof(msg) - 1)
      msg[i] = c >= ' ' ? c : '.';
  }

  void term_buf(unsigned i)
  {
    msg[i < sizeof(msg) - 1 ? i : sizeof(msg) - 1] = '\0';
  }

  char const *str() const
  {
    return mptr.tag[0] == 0 && mptr.tag[1] == 1 ? mptr.ptr : msg;
  }
};
#line 252 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"

class Tb_entry_ke : public Tb_entry
{
public:
  Tb_entry_msg<sizeof(Tb_entry)> msg;
  void set(Context const *ctx, Address ip)
  { set_global(Tbuf_ke, ctx, ip); }
};
#line 260 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"

class Tb_entry_ke_reg : public Tb_entry
{
public:
  Mword v[3];
  Tb_entry_msg<sizeof(Tb_entry) + sizeof(v)> msg;
  void set(Context const *ctx, Address ip)
  { set_global(Tbuf_ke_reg, ctx, ip); }
};
#line 269 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"

/** logged breakpoint. */
class Tb_entry_bp : public Tb_entry
{
private:
  Address	_address;	///< breakpoint address
  int		_len;		///< breakpoint length
  Mword	_value;		///< value at address
  int		_mode;		///< breakpoint mode
public:
  void print(String_buffer *buf) const;

public:  
#line 586 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  set(Context const *ctx, Address ip,
  		 int mode, int len, Mword value, Address address);
  
#line 600 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline int
  mode() const;
  
#line 605 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline int
  len() const;
  
#line 610 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Mword
  value() const;
  
#line 615 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline Address
  addr() const;
};
#line 281 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"

/** logged binary kernel event. */
class Tb_entry_ke_bin : public Tb_entry
{
public:
  char _msg[Tb_entry_size - sizeof(Tb_entry)];
  enum { SIZE = 30 };

public:  
#line 621 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  set(Context const *ctx, Address ip);
  
#line 626 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
  inline void
  set_buf(unsigned i, char c);
};
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"

/** logged trap. */
class Tb_entry_trap : public Tb_entry
{
private:
  Unsigned8	_trapno;
  Unsigned16	_error;
  Mword	_ebp, _cr2, _eax, _eflags, _esp;
  Unsigned16	_cs,  _ds;
public:
  void print(String_buffer *buf) const;

public:  
#line 34 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
  inline void
  set(Mword eip, Trap_state *ts);
  
#line 49 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
  inline void
  set(Mword eip, Mword trapno);
  
#line 58 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
  inline Unsigned8
  trapno() const;
  
#line 63 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
  inline Unsigned16
  error() const;
  
#line 68 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
  inline Mword
  eax() const;
  
#line 73 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
  inline Mword
  cr2() const;
  
#line 78 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
  inline Mword
  ebp() const;
  
#line 83 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
  inline Unsigned16
  cs() const;
  
#line 88 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
  inline Unsigned16
  ds() const;
  
#line 93 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
  inline Mword
  sp() const;
  
#line 98 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"
  inline Mword
  flags() const;
} __attribute__((packed));

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 296 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"

#include "entry_frame.h"
#line 298 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
#include "globals.h"
#line 299 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
#include "kip.h"
#line 300 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"
#include "trap_state.h"
#line 25 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"

#include "cpu.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 334 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline void
Tb_entry::clear()
{ _type = Tbuf_unused; }

#line 339 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline void
Tb_entry::set_global(char type, Context const *ctx, Address ip)
{
  _type   = type;
  _ctx    = ctx;
  _ip     = ip;
  _kclock = (Unsigned32)Kip::k()->clock;
  _cpu    = cxx::int_value<Cpu_number>(current_cpu());
}

#line 350 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline void
Tb_entry::hide()
{ _type |= Tbuf_hidden; }

#line 355 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline void
Tb_entry::unhide()
{ _type &= ~Tbuf_hidden; }

#line 360 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Address
Tb_entry::ip() const
{ return _ip; }

#line 365 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Context const *
Tb_entry::ctx() const
{ return _ctx; }

#line 370 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Unsigned8
Tb_entry::type() const
{ return _type & (Tbuf_max-1); }

#line 375 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline int
Tb_entry::hidden() const
{ return _type & Tbuf_hidden; }

#line 380 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Mword
Tb_entry::number() const
{ return _number; }

#line 385 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline void
Tb_entry::number(Mword number)
{ _number = number; }

#line 390 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline void
Tb_entry::rdpmc1()
{ _pmc1 = rdcnt1(); }

#line 395 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline void
Tb_entry::rdpmc2()
{ _pmc2 = rdcnt2(); }

#line 400 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Unsigned32
Tb_entry::kclock() const
{ return _kclock; }

#line 405 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Unsigned8
Tb_entry::cpu() const
{ return _cpu; }

#line 410 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Unsigned64
Tb_entry::tsc() const
{ return _tsc; }

#line 415 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Unsigned32
Tb_entry::pmc1() const
{ return _pmc1; }

#line 420 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Unsigned32
Tb_entry::pmc2() const
{ return _pmc2; }

#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"


inline void
Tb_entry::rdtsc()
{ _tsc = Cpu::rdtsc(); }

#line 425 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"



inline void
Tb_entry_ipc::set(Context const *ctx, Mword ip, Syscall_frame *ipc_regs, Utcb *utcb,
		  Mword dbg_id, Unsigned64 left)
{
  (void)left;
  set_global(Tbuf_ipc, ctx, ip);
  _dst       = ipc_regs->ref();
  _label     = ipc_regs->from_spec();


  _dbg_id = dbg_id;

  _timeout   = ipc_regs->timeout();
  _tag       = ipc_regs->tag();
  // hint for gcc
  Mword tmp0 = utcb->values[0];
  Mword tmp1 = utcb->values[1];
  _dword[0]  = tmp0;
  _dword[1]  = tmp1;
}

#line 448 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Mword
Tb_entry_ipc::ipc_type() const
{ return _dst.op(); }

#line 453 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Mword
Tb_entry_ipc::dbg_id() const
{ return _dbg_id; }

#line 458 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline L4_obj_ref
Tb_entry_ipc::dst() const
{ return _dst; }

#line 463 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline L4_timeout_pair
Tb_entry_ipc::timeout() const
{ return _timeout; }

#line 468 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline L4_msg_tag
Tb_entry_ipc::tag() const
{ return _tag; }

#line 473 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Mword
Tb_entry_ipc::label() const
{ return _label; }

#line 478 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Mword
Tb_entry_ipc::dword(unsigned index) const
{ return _dword[index]; }

#line 483 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"



inline void
Tb_entry_ipc_res::set(Context const *ctx, Mword ip, Syscall_frame *ipc_regs,
                      Utcb *utcb,
		      Mword result, Mword pair_event, Unsigned8 have_snd,
		      Unsigned8 is_np)
{
  set_global(Tbuf_ipc_res, ctx, ip);
  // hint for gcc
  Mword tmp0 = utcb->values[0];
  Mword tmp1 = utcb->values[1];
  _dword[0]   = tmp0;
  _dword[1]   = tmp1;
  _tag        = ipc_regs->tag();
  _pair_event = pair_event;
  _result     = L4_error::from_raw(result);
  _from       = ipc_regs->from_spec();
  _have_snd   = have_snd;
  _is_np      = is_np;
}

#line 505 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline int
Tb_entry_ipc_res::have_snd() const
{ return _have_snd; }

#line 510 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline int
Tb_entry_ipc_res::is_np() const
{ return _is_np; }

#line 515 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Mword
Tb_entry_ipc_res::from() const
{ return _from; }

#line 520 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline L4_error
Tb_entry_ipc_res::result() const
{ return _result; }

#line 525 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline L4_msg_tag
Tb_entry_ipc_res::tag() const
{ return _tag; }

#line 530 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Mword
Tb_entry_ipc_res::dword(unsigned index) const
{ return _dword[index]; }

#line 535 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Mword
Tb_entry_ipc_res::pair_event() const
{ return _pair_event; }

#line 540 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"



inline void
Tb_entry_ipc_trace::set(Context const *ctx, Mword ip, Unsigned64 snd_tsc,
			L4_obj_ref const &snd_dst, Mword rcv_dst,
			L4_msg_tag result, Unsigned8 snd_desc,
			Unsigned8 rcv_desc)
{
  set_global(Tbuf_ipc_trace, ctx, ip);
  _snd_tsc  = snd_tsc;
  _snd_dst  = snd_dst;
  _rcv_dst  = rcv_dst;
  _result   = result;
  _snd_desc = snd_desc;
  _rcv_desc = rcv_desc;
}

#line 557 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline void
Tb_entry_pf::set(Context const *ctx, Address ip, Address pfa,
		 Mword error, Space *spc)
{
  set_global(Tbuf_pf, ctx, ip);
  _pfa   = pfa;
  _error = error;
  _space = spc;
}

#line 568 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Mword
Tb_entry_pf::error() const
{ return _error; }

#line 573 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Address
Tb_entry_pf::pfa() const
{ return _pfa; }

#line 578 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Space*
Tb_entry_pf::space() const
{ return _space; }

#line 583 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"



inline void
Tb_entry_bp::set(Context const *ctx, Address ip,
		 int mode, int len, Mword value, Address address)
{
  set_global(Tbuf_breakpoint, ctx, ip);
  _mode    = mode;
  _len     = len;
  _value   = value;
  _address = address;
}

#line 596 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"




inline int
Tb_entry_bp::mode() const
{ return _mode; }

#line 603 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline int
Tb_entry_bp::len() const
{ return _len; }

#line 608 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Mword
Tb_entry_bp::value() const
{ return _value; }

#line 613 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline Address
Tb_entry_bp::addr() const
{ return _address; }

#line 618 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"



inline void
Tb_entry_ke_bin::set(Context const *ctx, Address ip)
{ set_global(Tbuf_ke_bin, ctx, ip); }

#line 624 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/tb_entry.cpp"


inline void
Tb_entry_ke_bin::set_buf(unsigned i, char c)
{
  if (i < sizeof(_msg)-1)
    _msg[i] = c;
}

#line 32 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"


inline void
Tb_entry_trap::set(Mword eip, Trap_state *ts)
{
  _ip     = eip;
  _trapno = ts->_trapno;
  _error  = ts->_err;
  _cr2    = ts->_cr2;
  _eax    = ts->_ax;
  _cs     = (Unsigned16)ts->cs();
  _ds     = (Unsigned16)ts->_ds;
  _esp    = ts->sp();
  _eflags = ts->flags();
}

#line 47 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"


inline void
Tb_entry_trap::set(Mword eip, Mword trapno)
{
  _ip     = eip;
  _trapno = trapno;
  _cs     = 0;
}

#line 56 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"


inline Unsigned8
Tb_entry_trap::trapno() const
{ return _trapno; }

#line 61 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"


inline Unsigned16
Tb_entry_trap::error() const
{ return _error; }

#line 66 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"


inline Mword
Tb_entry_trap::eax() const
{ return _eax; }

#line 71 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"


inline Mword
Tb_entry_trap::cr2() const
{ return _cr2; }

#line 76 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"


inline Mword
Tb_entry_trap::ebp() const
{ return _ebp; }

#line 81 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"


inline Unsigned16
Tb_entry_trap::cs() const
{ return _cs; }

#line 86 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"


inline Unsigned16
Tb_entry_trap::ds() const
{ return _ds; }

#line 91 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"


inline Mword
Tb_entry_trap::sp() const
{ return _esp; }

#line 96 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/tb_entry-ia32-32.cpp"


inline Mword
Tb_entry_trap::flags() const
{ return _eflags; }

#endif // tb_entry_h
