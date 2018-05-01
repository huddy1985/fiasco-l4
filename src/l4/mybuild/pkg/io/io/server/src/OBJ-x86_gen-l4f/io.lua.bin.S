.section .rodata, "a"
 .global _binary_io_lua_start
 .global _binary_io_lua_end
 .p2align 3
 _binary_io_lua_start:
 .incbin "/media/fedora_work/project/real-time/l4re/src/l4/pkg/io/io/server/src/io.lua"
 _binary_io_lua_end:

