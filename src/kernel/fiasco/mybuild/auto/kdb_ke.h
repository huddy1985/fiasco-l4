// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef kdb_ke_h
#define kdb_ke_h

//
// INTERFACE definition follows 
//

#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kdb_ke-ia32.cpp"

#define kdb_ke(msg)			\
  asm ("int3           		\n\t"	\
       "jmp 1f			\n\t"	\
       ".ascii " #msg  "	\n\t"	\
       "1:			\n\t")
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/kdb_ke-ia32.cpp"

#define kdb_ke_sequence(msg)		\
  asm ("int3			\n\t"	\
       "jmp 1f			\n\t"	\
       ".ascii \"*##\"		\n\t"	\
       "1:			\n\t"	\
       : : "a"(msg))

#endif // kdb_ke_h
