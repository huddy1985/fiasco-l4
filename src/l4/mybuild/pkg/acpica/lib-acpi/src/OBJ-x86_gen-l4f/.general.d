.general.d: /media/fedora_work/project/real-time/l4re/src/l4/pkg/acpica/lib-acpi/src/Makefile 
.general.d: /media/fedora_work/project/real-time/l4re/src/l4/mybuild/.config.all
/media/fedora_work/project/real-time/l4re/src/l4/mybuild/.config.all:

$(if $(wildcard /media/fedora_work/project/real-time/l4re/src/l4/mybuild/Makeconf.local), .general.d: FORCE)
$(if $(wildcard /media/fedora_work/project/real-time/l4re/src/l4/Makeconf.local), .general.d: FORCE)
$(if $(wildcard /media/fedora_work/project/real-time/l4re/src/l4/conf/Makeconf.local), .general.d: FORCE)
$(if $(wildcard /media/fedora_work/project/real-time/l4re/src/l4/pkg/acpica/Makeconf.local), .general.d: FORCE)
$(if $(wildcard /media/fedora_work/project/real-time/l4re/src/l4/pkg/acpica/lib-acpi/src/Makeconf.local), .general.d: FORCE)