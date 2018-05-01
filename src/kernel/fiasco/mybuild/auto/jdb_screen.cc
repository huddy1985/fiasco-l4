// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_screen.h"
#include "jdb_screen_i.h"

#line 29 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"

unsigned int Jdb_screen::_height         = 25; // default for native
#line 31 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"
unsigned int Jdb_screen::_width          = 80; // default
#line 32 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"
bool         Jdb_screen::_direct_enabled = true;
#line 33 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"

const char *Jdb_screen::Mword_adapter    = "~~~~~~~~~~~~~~~~";
#line 35 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"
const char *Jdb_screen::Mword_not_mapped = "----------------";
#line 36 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"
const char *Jdb_screen::Mword_blank      = "                ";
#line 37 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"
const char *Jdb_screen::Line             = "------------------------------------"
                                           "-----------------------------------";

#line 39 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"


void
Jdb_screen::set_height(unsigned int h)
{ _height = h; }

#line 44 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_screen.cpp"


void
Jdb_screen::set_width(unsigned int w)
{ _width = w; }
