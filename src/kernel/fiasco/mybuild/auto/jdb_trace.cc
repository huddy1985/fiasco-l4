// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_trace.h"
#include "jdb_trace_i.h"

#line 50 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"

int         Jdb_ipc_trace::_other_thread;
#line 52 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
Mword       Jdb_ipc_trace::_gthread;
#line 53 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
int         Jdb_ipc_trace::_other_task;
#line 54 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
Mword       Jdb_ipc_trace::_task;
#line 55 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
int         Jdb_ipc_trace::_snd_only;
#line 56 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
int         Jdb_ipc_trace::_log;
#line 57 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
int         Jdb_ipc_trace::_log_to_buf;
#line 58 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
int         Jdb_ipc_trace::_log_result;
#line 59 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
int         Jdb_ipc_trace::_trace;
#line 60 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
int         Jdb_ipc_trace::_slow_ipc;
#line 61 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
int         Jdb_ipc_trace::_cpath;
#line 62 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
int         Jdb_ipc_trace::_cshortcut;
#line 63 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"

int         Jdb_pf_trace::_other_thread;
#line 65 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
Mword       Jdb_pf_trace::_gthread;
#line 66 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
Addr_range  Jdb_pf_trace::_addr;
#line 67 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
int         Jdb_pf_trace::_log;
#line 68 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"
int         Jdb_pf_trace::_log_to_buf;

#line 92 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"


void 
Jdb_ipc_trace::clear_restriction()
{
  _other_thread = 0;
  _gthread      = 0;
  _other_task   = 0;
  _task         = 0;
  _snd_only    = 0;
}

#line 103 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"


void
Jdb_ipc_trace::show()
{
  if (_trace)
    putstr("IPC tracing to tracebuffer enabled");
  else if (_log)
    {
      printf("IPC logging%s%s enabled%s",
	  _log_result ? " incl. results" : "",
	  _log_to_buf ? " to tracebuffer" : "",
          _log_to_buf ? "" : " (exit with 'i', proceed with other key)");
      if (_gthread != 0)
	{
	  printf("\n    restricted to thread%s %lx%s",
		 _other_thread ? "s !=" : "",
		 _gthread,
		 _snd_only ? ", snd-only" : "");
	}
      if (_task != 0)
	{
	  printf("\n    restricted to task%s %lx",
	      _other_task ? "s !=" : "", _task);
	}
    }
  else
    {
      printf("IPC logging disabled -- using the IPC %s path",
	  _slow_ipc
	    ? "slow" 
	    : "C fast");
    }

  putchar('\n');
}

#line 153 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"


void
Jdb_pf_trace::show()
{
  if (_log)
    {
      int res_enabled = 0;
      BEGIN_LOG_EVENT("Page fault results", "pfr", Tb_entry_pf)
      res_enabled = 1;
      END_LOG_EVENT;
      printf("PF logging%s%s enabled",
	     res_enabled ? " incl. results" : "",
	     _log_to_buf ? " to tracebuffer" : "");
      if (_gthread != 0)
	{
    	  printf(", restricted to thread%s %lx",
		 _other_thread ? "s !=" : "",
		 _gthread);
	}
      if (_addr.lo || _addr.hi)
	{
     	  if (_gthread != 0)
	    putstr(" and ");
	  else
    	    putstr(", restricted to ");
	  if (_addr.lo <= _addr.hi)
	    printf(L4_PTR_FMT " <= pfa <= " L4_PTR_FMT
		   , _addr.lo, _addr.hi);
	  else
    	    printf("pfa < " L4_PTR_FMT " || pfa > " L4_PTR_FMT,
		   _addr.hi, _addr.lo);
	}
    }
  else
    putstr("PF logging disabled");
  putchar('\n');
}

#line 191 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_trace.cpp"


void 
Jdb_pf_trace::clear_restriction()
{
  _other_thread = 0;
  _gthread      = 0;
  _addr.lo      = 0;
  _addr.hi      = 0;
}
