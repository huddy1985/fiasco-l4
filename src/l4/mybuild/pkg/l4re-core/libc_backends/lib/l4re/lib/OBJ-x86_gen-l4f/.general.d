.general.d: /media/fedora_work/project/real-time/l4re/src/l4/pkg/l4re-core/libc_backends/lib/l4re/lib/Makefile 
.general.d: /media/fedora_work/project/real-time/l4re/src/l4/mybuild/.config.all
/media/fedora_work/project/real-time/l4re/src/l4/mybuild/.config.all:

$(if $(wildcard /media/fedora_work/project/real-time/l4re/src/l4/mybuild/Makeconf.local), .general.d: FORCE)
$(if $(wildcard /media/fedora_work/project/real-time/l4re/src/l4/Makeconf.local), .general.d: FORCE)
$(if $(wildcard /media/fedora_work/project/real-time/l4re/src/l4/conf/Makeconf.local), .general.d: FORCE)
$(if $(wildcard /media/fedora_work/project/real-time/l4re/src/l4/pkg/l4re-core/libc_backends/Makeconf.local), .general.d: FORCE)
$(if $(wildcard /media/fedora_work/project/real-time/l4re/src/l4/pkg/l4re-core/libc_backends/lib/l4re/lib/Makeconf.local), .general.d: FORCE)
