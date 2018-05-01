# Definitions for 'make' from L4 BID
# vim:se ft=make:
# --- Automatically created, do not modify ---
L4_SYSTEM = x86_gen
L4_CC = gcc
L4_CXX = g++
L4_LD = ld -m elf_i386
L4_LDFLAGS_LD_STATIC = -static -gc-sections --defsym __L4_KIP_ADDR__=0xaffff000 --defsym __L4_STACK_ADDR__=0xb0000000 -L/media/fedora_work/project/real-time/l4re/src/l4/mybuild/lib/x86_gen/l4f -L/media/fedora_work/project/real-time/l4re/src/l4/mybuild/lib/x86_gen -L/media/fedora_work/project/real-time/l4re/src/l4/mybuild/lib --warn-common
L4_LDFLAGS_GCC_STATIC = -Wl,-gc-sections -Wl,--defsym -Wl,__L4_KIP_ADDR__=0xaffff000 -Wl,--defsym -Wl,__L4_STACK_ADDR__=0xb0000000 -Wl,--warn-common -static -L/media/fedora_work/project/real-time/l4re/src/l4/mybuild/lib/x86_gen/l4f -L/media/fedora_work/project/real-time/l4re/src/l4/mybuild/lib/x86_gen -L/media/fedora_work/project/real-time/l4re/src/l4/mybuild/lib
L4_LDFLAGS_DYNAMIC_LINKER_LD = 
L4_LDFLAGS_DYNAMIC_LINKER_GCC = 
L4_LIBDIRS_R = 
L4_LIBDIRS = -L/media/fedora_work/project/real-time/l4re/src/l4/mybuild/lib/x86_gen/l4f -L/media/fedora_work/project/real-time/l4re/src/l4/mybuild/lib/x86_gen -L/media/fedora_work/project/real-time/l4re/src/l4/mybuild/lib
L4_GCCSYSLIBDIRS = -L/usr/lib/gcc/x86_64-linux-gnu/5/32/ -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../../x86_64-linux-gnu/lib/x86_64-linux-gnu/5/32/ -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../../x86_64-linux-gnu/lib/i386-linux-gnu/ -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../../x86_64-linux-gnu/lib/../lib32/ -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/5/32/ -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../i386-linux-gnu/ -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../../lib32/ -L/lib/x86_64-linux-gnu/5/32/ -L/lib/i386-linux-gnu/ -L/lib/../lib32/ -L/usr/lib/x86_64-linux-gnu/5/32/ -L/usr/lib/i386-linux-gnu/ -L/usr/lib/../lib32/ -L/usr/lib/gcc/x86_64-linux-gnu/5/ -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../../x86_64-linux-gnu/lib/x86_64-linux-gnu/5/ -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../../x86_64-linux-gnu/lib/i386-linux-gnu/ -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../../x86_64-linux-gnu/lib/ -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/5/ -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../i386-linux-gnu/ -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../ -L/lib/x86_64-linux-gnu/5/ -L/lib/i386-linux-gnu/ -L/lib/ -L/usr/lib/x86_64-linux-gnu/5/ -L/usr/lib/i386-linux-gnu/ -L/usr/lib/
L4_CPPFLAGS =               -DSYSTEM_x86_gen_l4f -DARCH_x86 -DCPUTYPE_gen -DL4API_l4f  -D_GNU_SOURCE    -I/media/fedora_work/project/real-time/l4re/src/l4/mybuild/include/contrib/libstdc++-v3 -I/media/fedora_work/project/real-time/l4re/src/l4/mybuild/include/x86/l4f -I/media/fedora_work/project/real-time/l4re/src/l4/mybuild/include/x86 -I/media/fedora_work/project/real-time/l4re/src/l4/mybuild/include  -nostdinc -I/media/fedora_work/project/real-time/l4re/src/l4/mybuild/include/contrib/libstdc++-v3 -I/media/fedora_work/project/real-time/l4re/src/l4/mybuild/include/uclibc  -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include-fixed
L4_CFLAGS = -fno-omit-frame-pointer        -g -O2 -fno-strict-aliasing -Wextra -Wall -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations        -fno-common -std=gnu99 -m32    -fstack-protector
L4_CXXFLAGS = -std=gnu++11 -fno-omit-frame-pointer        -g -O2 -fno-strict-aliasing -Wextra -Wall -Wmissing-declarations  -fno-common   -m32 -DL4_GCC_HAS_ATOMICS  -fstack-protector -fuse-cxa-atexit
L4_GCCLIB = /media/fedora_work/project/real-time/l4re/src/l4/mybuild/lib/x86_gen/l4f/libgcc.a
L4_GCCLIB_EH = /usr/lib/gcc/x86_64-linux-gnu/5/32/libgcc_eh.a
L4_LDS_stat_bin = 
L4_BID_STACK_ADDR = 0xb0000000
L4_BID_KIP_ADDR = 0xaffff000
L4_BID_KIP_OFFS_SYS_INVOKE = 0x800
L4_BID_KIP_OFFS_SYS_DEBUGGER = 0x900
L4_BID_PKG_CONFIG = /media/fedora_work/project/real-time/l4re/src/l4/tool/bin/l4-bender
L4_BID_PKG_CONFIG_CALL = $(shell PKG_CONFIG_LIBDIR=$(1)/pc PKG_CONFIG_PATH= $(L4_BID_PKG_CONFIG) --define-variable=incdir=$(1)/include/contrib $(if $(VERBOSE),--silence-errors) $(2) $(3) || echo __PKGCONFIG_FAILED__)
L4_BID_PKG_CONFIG_FAILED = $(findstring __PKGCONFIG_FAILED__,$(1))
L4_BID_BENDER_LINK = 
L4_BID_BENDER_DEFINES = -Dl4obj=$(1) -Dl4dir=$(2) -Dgcclibdir="$(3:-L%=%)" -Dl4system=$(4) $(if $(5),-Dl4api=$(5))
LIBCINCDIR_all_static = -nostdinc -I/media/fedora_work/project/real-time/l4re/src/l4/mybuild/include/contrib/libstdc++-v3 -I/media/fedora_work/project/real-time/l4re/src/l4/mybuild/include/uclibc  -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include-fixed
LIBCINCDIR_all_shared = -nostdinc -I/media/fedora_work/project/real-time/l4re/src/l4/mybuild/include/contrib/libstdc++-v3 -I/media/fedora_work/project/real-time/l4re/src/l4/mybuild/include/uclibc  -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include-fixed
REQUIRES_LIBS_all_static = stdlibs
REQUIRES_LIBS_all_shared = stdlibs-sh
LDSCRIPT_all_static = 
LDSCRIPT_all_shared = 
LDFLAGS_all_static = -static -gc-sections
LDFLAGS_all_shared = -gc-sections
L4_CPPFLAGS_MINIMAL =               -DSYSTEM_x86_gen_l4f -DARCH_x86 -DCPUTYPE_gen -DL4API_l4f  -D_GNU_SOURCE      -I/media/fedora_work/project/real-time/l4re/src/l4/mybuild/include/x86/l4f -I/media/fedora_work/project/real-time/l4re/src/l4/mybuild/include/x86 -I/media/fedora_work/project/real-time/l4re/src/l4/mybuild/include  -nostdinc -I/media/fedora_work/project/real-time/l4re/src/l4/mybuild/include/contrib/libstdc++-v3 -I/media/fedora_work/project/real-time/l4re/src/l4/mybuild/include/uclibc  -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include-fixed
L4_CFLAGS_MINIMAL = -fno-omit-frame-pointer        -g -O2 -fno-strict-aliasing -Wextra -Wall -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations        -fno-common -std=gnu99 -m32   -fno-stack-protector
L4_CXXFLAGS_MINIMAL = -std=gnu++11 -fno-omit-frame-pointer        -g -O2 -fno-strict-aliasing -Wextra -Wall -Wmissing-declarations  -fno-common   -m32 -DL4_GCC_HAS_ATOMICS -fno-stack-protector -fuse-cxa-atexit
L4_LDFLAGS_LD_SHARED = -gc-sections --defsym __L4_KIP_ADDR__=0xaffff000 --defsym __L4_STACK_ADDR__=0xb0000000 -L/media/fedora_work/project/real-time/l4re/src/l4/mybuild/lib/x86_gen/l4f -L/media/fedora_work/project/real-time/l4re/src/l4/mybuild/lib/x86_gen -L/media/fedora_work/project/real-time/l4re/src/l4/mybuild/lib --warn-common
L4_LDFLAGS_GCC_SHARED = -Wl,-gc-sections -Wl,--defsym -Wl,__L4_KIP_ADDR__=0xaffff000 -Wl,--defsym -Wl,__L4_STACK_ADDR__=0xb0000000 -Wl,--warn-common -L/media/fedora_work/project/real-time/l4re/src/l4/mybuild/lib/x86_gen/l4f -L/media/fedora_work/project/real-time/l4re/src/l4/mybuild/lib/x86_gen -L/media/fedora_work/project/real-time/l4re/src/l4/mybuild/lib
L4_LDS_so = 
L4_LDS_dyn_bin = 
L4_CRT0_SO = 
L4_CRTN_SO = 
