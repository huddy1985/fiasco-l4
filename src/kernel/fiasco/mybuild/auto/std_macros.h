// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef std_macros_h
#define std_macros_h

//
// INTERFACE definition follows 
//

#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/std_macros.cpp"

#define BUILTIN_EXPECT(exp,c)	__builtin_expect((exp),(c))
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#define EXPECT_TRUE(exp)	__builtin_expect((exp),true)
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#define EXPECT_FALSE(exp)	__builtin_expect((exp),false)
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/std_macros.cpp"

// Use this for functions which do not examine any values except their
// arguments and have no effects except the return value. Note that a
// function that has pointer arguments and examines the data pointed to
// must _not_ be declared `const'.  Likewise, a function that calls a
// non-`const' function usually must not be `const'.  It does not make
// sense for a `const' function to return `void'.
#define FIASCO_CONST		__attribute__ ((__const__))
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/std_macros.cpp"

#ifdef __i386__
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#define FIASCO_FASTCALL		__attribute__ ((__regparm__(3)))
#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#else
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#define FIASCO_FASTCALL
#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#endif
#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/std_macros.cpp"

#define MARK_AS_DEPRECATED	__attribute__ ((__deprecated__))
#line 22 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#define ALWAYS_INLINE		__attribute__ ((__always_inline__))
#line 23 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#define FIASCO_NOINLINE        __attribute__ ((__noinline__))
#line 24 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#define FIASCO_WARN_RESULT     __attribute__ ((warn_unused_result))
#line 25 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/std_macros.cpp"

#define FIASCO_NORETURN         __attribute__ ((__noreturn__))
#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#define FIASCO_FLATTEN          __attribute__((__flatten__))
#line 28 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/std_macros.cpp"

#define FIASCO_STRINGIFY_(x) #x
#line 30 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/std_macros.cpp"
#define FIASCO_STRINGIFY(x) FIASCO_STRINGIFY_(x)

#endif // std_macros_h
