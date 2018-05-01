// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_bp.h"
#include "jdb_bp_i.h"

#line 24 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"

Mword Jdb_bp::dr7;

#line 53 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"


int
Jdb_bp::global_breakpoints()
{
  return 1;
}

#line 60 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"


int
Jdb_bp::set_debug_address_register(int num, Mword addr, Mword len,
				   Breakpoint::Mode mode, Space *)
{
  clr_dr7(num, dr7);
  set_dr7(num, len, mode, dr7);
  switch (num)
    {
    case 0: write_debug_register(0, addr); break;
    case 1: write_debug_register(1, addr); break;
    case 2: write_debug_register(2, addr); break;
    case 3: write_debug_register(3, addr); break;
    default:;
    }
  return 1;
}

#line 78 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"


void
Jdb_bp::clr_debug_address_register(int num)
{
  clr_dr7(num, dr7);
}

#line 85 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"


void
Jdb_bp::at_jdb_enter()
{
  dr7 = read_debug_register(7);
  // disable breakpoints while we are in kernel debugger
  write_debug_register(7, dr7 & Val_enter);
}

#line 94 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"


void
Jdb_bp::at_jdb_leave()
{
  write_debug_register(6, Val_leave);
  write_debug_register(7, dr7);
}

#line 102 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"

/** @return 1 if single step occured */

int
Jdb_bp::test_sstep()
{
  Mword dr6 = read_debug_register(6);
  if (!(dr6 & Val_test_sstep))
    return 0;

  // single step has highest priority, don't consider other conditions
  write_debug_register(6, Val_leave);
  return 1;
}

#line 116 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"

/** @return 1 if breakpoint occured */

int
Jdb_bp::test_break(String_buffer *buf)
{
  Mword dr6 = read_debug_register(6);
  if (!(dr6 & Val_test))
    return 0;

  int ret = test_break(buf, dr6);
  write_debug_register(6, dr6 & ~Val_test);
  return ret;
}

#line 130 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"

/** @return 1 if other debug exception occured */

int
Jdb_bp::test_other(String_buffer *buf)
{
  Mword dr6 = read_debug_register(6);
  if (!(dr6 & Val_test_other))
    return 0;

  buf->printf("unknown trap 1 (dr6=" L4_PTR_FMT ")", dr6);
  write_debug_register(6, Val_leave);
  return 1;
}

#line 144 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"

/** @return 1 if only breakpoints were logged and jdb should not be entered */

int
Jdb_bp::test_log_only()
{
  Mword dr6 = read_debug_register(6);

  if (dr6 & Val_test)
    {
      dr7 = read_debug_register(7);
      // disable breakpoints -- we might trigger a r/w breakpoint again
      write_debug_register(7, dr7 & Val_enter);
      test_log(dr6);
      write_debug_register(6, dr6);
      write_debug_register(7, dr7);
      if (!(dr6 & Val_test_other))
	// don't enter jdb, breakpoints only logged
	return 1;
    }
  // enter jdb
  return 0;
}

#line 167 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_bp-ia32-amd64.cpp"


void
Jdb_bp::init_arch()
{
  Jdb::bp_test_log_only = test_log_only;
  Jdb::bp_test_break    = test_break;
  Jdb::bp_test_sstep    = test_sstep;
  Jdb::bp_test_other    = test_other;
}
