// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef pic_h
#define pic_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/pic.cpp"

#include <types.h>
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/pic-i8259.cpp"

#include "initcalls.h"

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/pic.cpp"

/**
 * Encapsulation of the platforms interrupt controller
 */
class Pic
{

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/pic-i8259.cpp"
private:

  friend class Jdb_kern_info_pic_state;
  friend class Io_m;
private:
  enum
  {
    MASTER_PIC_BASE = 0x20,
    SLAVES_PIC_BASE = 0xa0,
    OFF_ICW	    = 0x00,
    OFF_OCW	    = 0x01,

    MASTER_ICW	    = MASTER_PIC_BASE + OFF_ICW,
    MASTER_OCW	    = MASTER_PIC_BASE + OFF_OCW,
    SLAVES_ICW	    = SLAVES_PIC_BASE + OFF_ICW,
    SLAVES_OCW	    = SLAVES_PIC_BASE + OFF_OCW,
  };

public:  
#line 30 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/pic-i8259.cpp"
  static inline Unsigned16
  disable_all_save();
  
#line 43 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/pic-i8259.cpp"
  static inline void
  restore_all(Unsigned16 s);
};

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 26 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/pic-i8259.cpp"

#include "io.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 28 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/pic-i8259.cpp"


inline Unsigned16
Pic::disable_all_save()
{
  Unsigned16 s;
  s  = Io::in8(MASTER_OCW);
  s |= Io::in8(SLAVES_OCW) << 8;
  Io::out8(0xff, MASTER_OCW);
  Io::out8(0xff, SLAVES_OCW);

  return s;
}

#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/pic-i8259.cpp"


inline void
Pic::restore_all(Unsigned16 s)
{
  Io::out8(s & 0x0ff, MASTER_OCW);
  Io::out8((s >> 8) & 0x0ff, SLAVES_OCW);
}

#endif // pic_h
