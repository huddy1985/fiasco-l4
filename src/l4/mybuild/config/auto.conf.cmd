deps_config := \
	./mk/arch/Kconfig.sparc.inc \
	./mk/arch/Kconfig.ppc32.inc \
	./mk/arch/Kconfig.mips.inc \
	./mk/arch/Kconfig.ia32.inc \
	./mk/arch/Kconfig.arm64.inc \
	./mk/arch/Kconfig.arm.inc \
	/media/fedora_work/project/real-time/l4re/src/l4/mybuild/Kconfig.generated

.kconfig.auto: \
	$(deps_config)

ifneq "$(KERNELVERSION)" "SVN"
.kconfig.auto: FORCE
endif

$(deps_config): ;
