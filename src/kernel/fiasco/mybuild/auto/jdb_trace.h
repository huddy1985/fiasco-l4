// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_trace_h
#define jdb_trace_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"

#include "l4_types.h"

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"

class Syscall_frame;
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
typedef struct
{
  Address lo, hi;
} Addr_range;
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"

class Jdb_ipc_trace
{
public:
  static int         _other_thread;
  static Mword       _gthread;
  static int         _other_task;
  static Mword       _task;
  static int         _snd_only;
  static int         _log;
  static int         _log_to_buf;
  static int         _log_result;
  static int         _trace;
  static int         _slow_ipc;
  static int         _cpath;
  static int         _cshortcut;
  friend class Jdb_set_trace;

public:  
#line 72 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static inline int log();
  
#line 73 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static inline int log_buf();
  
#line 74 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static inline int log_result();
  
#line 77 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static inline int
  check_restriction (Mword id,
  				  Mword task,
  				  Syscall_frame *ipc_regs,
  				  Mword dst_task);
  
#line 94 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static void 
  clear_restriction();
  
#line 105 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static void
  show();
};
#line 28 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"

class Jdb_pf_trace
{
private:
  static int         _other_thread;
  static Mword       _gthread;
  static Addr_range  _addr;
  static int         _log;
  static int         _log_to_buf;
  friend class Jdb_set_trace;

public:  
#line 140 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static inline int log();
  
#line 141 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static inline int log_buf();
  
#line 144 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static inline int
  check_restriction (Mword id, Address pfa);
  
#line 155 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static void
  show();
  
#line 193 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
  static void 
  clear_restriction();
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 42 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"

#include <cstdio>
#line 46 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
#include "entry_frame.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 69 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"



inline int Jdb_ipc_trace::log()        { return _log; }

#line 73 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
inline int Jdb_ipc_trace::log_buf()    { return _log_to_buf; }

#line 74 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
inline int Jdb_ipc_trace::log_result() { return _log_result; }

#line 75 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"


inline int
Jdb_ipc_trace::check_restriction (Mword id,
				  Mword task,
				  Syscall_frame *ipc_regs,
				  Mword dst_task)
{
  return (   ((_gthread == 0)
	      || ((_other_thread) ^ (_gthread == id))
	      )
	   && ((!_snd_only || ipc_regs->ref().valid()))
	   && ((_task == 0)
	      || ((_other_task)   
		  ^ ((_task == task) || (_task == dst_task))))
	  );
}

#line 139 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"

inline int Jdb_pf_trace::log()     { return _log; }

#line 141 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
inline int Jdb_pf_trace::log_buf() { return _log_to_buf; }

#line 142 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"


inline int
Jdb_pf_trace::check_restriction (Mword id, Address pfa)
{
  return (   (((_gthread == 0)
	      || ((_other_thread) ^ (_gthread == id))))
	  && (!(_addr.lo | _addr.hi)
	      || (_addr.lo <= _addr.hi && pfa >= _addr.lo && pfa <= _addr.hi)
	      || (_addr.lo >  _addr.hi && pfa <  _addr.hi && pfa >  _addr.lo)));
}

#endif // jdb_trace_h
