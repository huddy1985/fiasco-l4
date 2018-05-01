// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "koptions.h"
#include "koptions_i.h"

#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/koptions.cpp"

namespace Koptions_ns
{
  Koptions::Options o __attribute__((section(".koptions"))) =
    {
      Koptions::Magic,
      1,              // version
      0,              // flags
      0,              // kmemsize
      { 0, 0, 0, 0, 0, 0 }, // uart
      "",             // jdb_cmd
      0,              // tbuf_entries
      0,              // out_buf
    };
}
#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/koptions.cpp"

namespace Koptions {
  Options *o() { return &Koptions_ns::o; }
};
