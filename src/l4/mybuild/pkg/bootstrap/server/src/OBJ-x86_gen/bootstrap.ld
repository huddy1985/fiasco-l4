ENTRY(_start)
PHDRS {
  data PT_LOAD;
}
SECTIONS
{
  . = 0x2d0000;
  PROVIDE (ImageBase = 0x2d0000);
  .hash : { *(.hash) } : data
  . = (. < (0x400 + 0x2d0000)) ? (0x2d0000 + 0x400) : .;
  .text :
  {
    *(.init)
    KEEP(*(.multiboot2))
    *(.text .text.* .gnu.linkonce.t*)
    *(.rodata*)
  } : data
  .dynsym : { *(.dynsym) } : data
  .dynstr : { *(.dynstr) } : data
  .reloc : { *(.reloc) } : data
  .rel.dyn :
  {
    *(.rel.*) *(.rel.module_info)
  } : data
  .data :
  {
    . = ALIGN(8);
    *(.data)
    *(.data.*)
    *(.plt)
    *(.got.plt)
    *(.got)
    . = ALIGN(8); PROVIDE (__CTORS_BEGIN = .); KEEP (*(SORT(.ctors.*))) KEEP (*(.ctors)) PROVIDE (__CTORS_END = .); PROVIDE (__preinit_array_start = .); KEEP (*(SORT(.preinit_array.*))) KEEP (*(.preinit_array)) PROVIDE (__preinit_array_end = .); PROVIDE (__init_array_start = .); KEEP (*(SORT(.init_array.*))) KEEP (*(.init_array)) PROVIDE (__init_array_end = .);
    PROVIDE (__PLATFORMS_BEGIN = .); KEEP (*(.platformdata)) PROVIDE (__PLATFORMS_END = .);
  } : data
  .data.module_info :
  {
    . = ALIGN(16);
    _module_info_start = .;
    KEEP(*(.module_info .module_info.*))
    _module_info_end = .;
  } : data
  .dynamic : { *(.dynamic) } : data
  .rela.dyn :
  {
    *(.rela.init)
    *(.rela.text .rela.text.* .rela.gnu.linkonce.t.*)
    *(.rela.fini)
    *(.rela.rodata .rela.rodata.* .rela.gnu.linkonce.r.*)
    *(.rela.data .rela.data.* .rela.gnu.linkonce.d.*)
    *(.rela.tdata .rela.tdata.* .rela.gnu.linkonce.td.*)
    *(.rela.tbss .rela.tbss.* .rela.gnu.linkonce.tb.*)
    *(.rela.ctors)
    *(.rela.dtors)
    *(.rela.got)
    *(.rela.bss .rela.bss.* .rela.gnu.linkonce.b.*)
    *(.rela.ldata .rela.ldata.* .rela.gnu.linkonce.l.*)
    *(.rela.lbss .rela.lbss.* .rela.gnu.linkonce.lb.*)
    *(.rela.lrodata .rela.lrodata.* .rela.gnu.linkonce.lr.*)
    *(.rela.ifunc)
    *(.rela.module*)
    *(.rela.init_array)
  } : data
  .rela.plt :
  {
    *(.rela.plt)
    *(.rela.iplt)
  } : data
  _edata = .;
  PROVIDE (edata = .);
  . = ALIGN(4096);
  __bss_start = .;
  .bss :
  {
   *(.bss)
   *(.bss.*)
   *(COMMON)
   *(.dynbss)
   *(.bss_memmap)
  } : data
  _end = . ;
  PROVIDE (end = .);
  . = ALIGN(4096);
  /DISCARD/ : {
    *(.rela.reloc)
    *(.note.GNU-stack)
    *(.jcr)
    *(.interp)
    *(.comment)
    *(.note)
    *(.eh_frame)
    *(.stab)
    *(.stabstr)
    *(.fini)
  }
}
