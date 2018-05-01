// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_screen.h"
#include "jdb_screen_i.h"

#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_screen-ia32.cpp"

const char* const Jdb_screen::Reg_names[]	= { "EAX", "EBX", "ECX", "EDX",
						    "EBP", "ESI", "EDI", "EIP",
						    "ESP", "EFL" };
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_screen-ia32.cpp"
const char Jdb_screen::Reg_prefix		= 'E';
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_screen-ia32.cpp"

const char* Jdb_screen::Root_page_table		= "pdir: ";

#line 25 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_screen-ia32.cpp"



int
Jdb_screen::num_regs()
{
   return sizeof(Jdb_screen::Reg_names) / sizeof(Jdb_screen::Reg_names[0]);
}
