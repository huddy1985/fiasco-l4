// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef boot_info_h
#define boot_info_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/boot_info.cpp"

#include "initcalls.h"
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"

#include "types.h"

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/boot_info.cpp"

class Boot_info
{
public:
  static void init() FIASCO_INIT;

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"
private:

private:
  static unsigned _checksum_ro;
  static unsigned _checksum_rw;

public:  
#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"
  /// \defgroup pre init setup
  /**
   * The Boot_info object must be set up with these functions
   * before Boot_info::init() is called!
   * This can be done either in __main, if booted on hardware
   * or in an initializer with a higher priority than BOOT_INFO_INIT_PRIO
   * (e.g UX_STARTUP1_INIT_PRIO) if the kernel runs on software (FIASCO-UX)
   */
  //@{
  
  
  static inline void set_checksum_ro(unsigned ro_cs);
  
#line 42 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"
  static inline void set_checksum_rw(unsigned rw_cs);
  
#line 53 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"
  static inline unsigned
  get_checksum_ro(void);
  
#line 60 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"
  static inline unsigned
  get_checksum_rw(void);
  
#line 67 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"
  static void
  reset_checksum_ro(void);
};
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"

//-----------------------------------------------------------------------------


//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 25 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"


/// \defgroup pre init setup
/**
 * The Boot_info object must be set up with these functions
 * before Boot_info::init() is called!
 * This can be done either in __main, if booted on hardware
 * or in an initializer with a higher priority than BOOT_INFO_INIT_PRIO
 * (e.g UX_STARTUP1_INIT_PRIO) if the kernel runs on software (FIASCO-UX)
 */
//@{


inline void Boot_info::set_checksum_ro(unsigned ro_cs)
{  _checksum_ro = ro_cs; }

#line 40 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"


inline void Boot_info::set_checksum_rw(unsigned rw_cs)
{  _checksum_rw = rw_cs; }

#line 51 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"


inline unsigned
Boot_info::get_checksum_ro(void)
{
  return _checksum_ro;
}

#line 58 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/boot_info-ia32.cpp"


inline unsigned
Boot_info::get_checksum_rw(void)
{
  return _checksum_rw;
}

#endif // boot_info_h
