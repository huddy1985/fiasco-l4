deps_config := \
	Kconfig

include/config/auto.conf: \
	$(deps_config)

ifneq "$(INCLUDE_SPARC)" ""
include/config/auto.conf: FORCE
endif
ifneq "$(INCLUDE_PPC32)" ""
include/config/auto.conf: FORCE
endif
ifneq "$(KERNELVERSION)" "SVN"
include/config/auto.conf: FORCE
endif

$(deps_config): ;
