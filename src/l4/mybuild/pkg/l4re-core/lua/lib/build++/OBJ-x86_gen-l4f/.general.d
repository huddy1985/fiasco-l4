.general.d: /media/fedora_work/project/real-time/l4re/src/l4/pkg/l4re-core/lua/lib/build++/Makefile 
.general.d: /media/fedora_work/project/real-time/l4re/src/l4/mybuild/.config.all
/media/fedora_work/project/real-time/l4re/src/l4/mybuild/.config.all:

$(if $(wildcard /media/fedora_work/project/real-time/l4re/src/l4/mybuild/Makeconf.local), .general.d: FORCE)
$(if $(wildcard /media/fedora_work/project/real-time/l4re/src/l4/Makeconf.local), .general.d: FORCE)
$(if $(wildcard /media/fedora_work/project/real-time/l4re/src/l4/conf/Makeconf.local), .general.d: FORCE)
$(if $(wildcard /media/fedora_work/project/real-time/l4re/src/l4/pkg/l4re-core/lua/Makeconf.local), .general.d: FORCE)
$(if $(wildcard /media/fedora_work/project/real-time/l4re/src/l4/pkg/l4re-core/lua/lib/build++/Makeconf.local), .general.d: FORCE)
