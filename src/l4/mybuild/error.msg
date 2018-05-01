make[1]: Entering directory '/media/fedora_work/project/real-time/l4re/src/l4'
qemu-system-i386 -kernel /media/fedora_work/project/real-time/l4re/src/l4/mybuild/bin/x86_gen/bootstrap -serial stdio -append "bootstrap -modaddr 0x01100000 console=ttyAMA0 console=ttyS0" -initrd "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/mybuild/fiasco -serial_esc,/media/fedora_work/project/real-time/l4re/src/l4/mybuild/bin/x86_gen/l4f/sigma0 ,/media/fedora_work/project/real-time/l4re/src/l4/mybuild/bin/x86_gen/l4f/moe rom/l4linux.cfg,/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/mybuild/l4linux.cfg ,/media/fedora_work/project/real-time/l4re/src/l4/mybuild/bin/x86_gen/l4f/l4re ,/media/fedora_work/project/real-time/l4re/src/l4/mybuild/bin/x86_gen/l4f/ned ,/tmp/IskpwnoQke/vmlinuz ,/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/mybuild/drops-rd.rd " 

L4 Bootstrapper
  Build: #1 Tue May  1 16:27:04 CST 2018, x86-32, 5.4.0 20160609
  RAM: 0000000000000000 - 000000000009fbff: 639kB
  RAM: 0000000000100000 - 0000000007fdffff: 129920kB
  Total RAM: 127MB
  Scanning /media/fedora_work/project/real-time/l4re/src/kernel/fiasco/mybuild/fiasco -serial_esc
  Scanning /media/fedora_work/project/real-time/l4re/src/l4/mybuild/bin/x86_gen/l4f/sigma0 
  Scanning /media/fedora_work/project/real-time/l4re/src/l4/mybuild/bin/x86_gen/l4f/moe rom/l4linux.cfg
  need 980 bytes to copy MBI
  reserved 980 bytes at 0x2000
  Moving up to 8 modules behind 1100000
  moving module 07 { 14de400-24de3ff } -> { 22fc000-32fbfff } [16777216]
  moving module 06 { f15400-14de20f } -> { 1d33000-22fbe0f } [6065680]
  moving module 05 { b52400-f14abb } -> { 1970000-1d326bb } [3942076]
  moving module 04 { 953400-b51583 } -> { 1771000-196f183 } [2089348]
  moving module 03 { 952400-9524b3 } -> { 1770000-17700b3 } [180]
  moving module 02 { 43c400-952213 } -> { 125a000-176fe13 } [5332500]
  moving module 01 { 37b400-43b53f } -> { 1199000-125913f } [786752]
  moving module 00 { 2e2400-37a9a3 } -> { 1100000-11985a3 } [624036]
  Loading /project/real-time/l4re/src/kernel/fiasco/mybuild/fiasco
  Loading ect/real-time/l4re/src/l4/mybuild/bin/x86_gen/l4f/sigma0
  Loading roject/real-time/l4re/src/l4/mybuild/bin/x86_gen/l4f/moe
  find kernel info page...
  found kernel info page (via ELF) at 400000
Regions of list 'regions'
    [        0,       fff] {     1000} Arch   BIOS
    [     1000,      1fff] {     1000} Kern   /project/real-time/l4re/src/kernel/fiasco/mybuild/fiasco
    [     2000,      23d3] {      3d4} Root   mbi_rt
    [    9fc00,     9ffff] {      400} Arch   BIOS
    [    f0000,     fffff] {    10000} Arch   BIOS
    [   100000,    10f193] {     f194} Sigma0 ect/real-time/l4re/src/l4/mybuild/bin/x86_gen/l4f/sigma0
    [   140000,    1826e3] {    426e4} Root   roject/real-time/l4re/src/l4/mybuild/bin/x86_gen/l4f/moe
    [   2d0400,    2e04c7] {    100c8} Boot   bootstrap
    [   300000,    38ffff] {    90000} Kern   /project/real-time/l4re/src/kernel/fiasco/mybuild/fiasco
    [   400000,    49cfff] {    9d000} Kern   /project/real-time/l4re/src/kernel/fiasco/mybuild/fiasco
    [  1770000,   32fbfff] {  1b8c000} Root   Module
    [  7fe0000,   7ffffff] {    20000} Arch   BIOS
    [ fffc0000,  ffffffff] {    40000} Arch   BIOS
  found kernel options (via ELF) at 401000
  Sigma0 config    ip:001001fc sp:00000000
  Roottask config  ip:0014021c sp:00000000
  Starting kernel /project/real-time/l4re/src/kernel/fiasco/mybuild/fiasco at 00300794

[1;32mWelcome to L4/Fiasco.OC!
[0;32mL4/Fiasco.OC microkernel on ia32
Rev: r77 compiled with gcc 5.4.0 20160609 for x86-32    []
Build: #1 Tue May  1 16:26:26 CST 2018
[0m
[31mPerformance-critical config option(s) detected:
  CONFIG_NDEBUG is off
[m
Superpages: yes
Kmem:: TSS mem at 75ae000 (4096Bytes)
ACPI: RSDP[0xf6460]	r00 OEM:BOCHS.
FPU0: SSE 
ACPI: FACS phys=7fe0000 virt=0x203e0000
ACPI: HW sig=0
SERIAL ESC: allocated IRQ 4 for serial uart
Absolute KIP Syscalls using: Sysenter
Enable MSI support: chained IRQ mgr @ 0xfc5b1048
SERIAL ESC: allocated IRQ 4 for serial uart
Not using serial hack in slow timer handler.
CPU[0]: GenuineIntel (6:6:3:0)[00000663] Model: QEMU Virtual CPU version 2.5+ at 3199MHz

  32 KB L1 I Cache (8-way associative, 64 bytes per line)
  32 KB L1 D Cache (8-way associative, 64 bytes per line)
2048 KB L2 U Cache (8-way associative, 64 bytes per line)

Freeing init code/data: 28672 bytes (7 pages)

Calibrating timer loop... done.
MDB: use page size: 22
MDB: use page size: 12
SIGMA0: Hello!
  KIP @ 400000
  Found Fiasco: KIP syscalls: yes
  allocated 4KB for maintenance structures
SIGMA0: Dump of all resource maps
RAM:------------------------
[4:2000;2fff]
[0:3000;9efff]
[0:110000;13ffff]
[4:140000;182fff]
[0:183000;3fffff]
[0:496000;176ffff]
[4:1770000;32fbfff]
[0:32fc000;75abfff]
IOMEM:----------------------
[0:0;fff]
[0:9f000;fffff]
[0:7fe0000;febfffff]
[0:fec01000;fedfffff]
[0:fee01000;ffffffff]
IO PORTS--------------------------
[0:0;fffffff]
MOE: Hello world
MOE: found 90964 KByte free memory
MOE: found RAM from 2000 to 75ac000
MOE: allocated 117 KByte for the page array @0x3000
MOE: virtual user address space [0-bfffffff]
MOE: rom name space cap -> [C:103000]
MOE: rwfs name space cap -> [C:105000]
  BOOTFS: [1770000-17700b4] [C:107000] l4linux.cfg
  BOOTFS: [1771000-196f184] [C:109000] l4re
  BOOTFS: [1970000-1d326bc] [C:10b000] ned
  BOOTFS: [1d33000-22fbe10] [C:10d000] vmlinuz
  BOOTFS: [22fc000-32fc000] [C:10f000] drops-rd.rd
MOE: cmdline: /media/fedora_work/project/real-time/l4re/src/l4/mybuild/bin/x86_gen/l4f/moe rom/l4linux.cfg
MOE: Starting: rom/ned rom/l4linux.cfg
MOE: loading 'rom/ned'
Ned says: Hi World!
Ned: loading file: 'rom/l4linux.cfg'
[37mvmlinuz | libio: Warning: Query of 'vbus' failed![0m
[37mvmlinuz | PH  0 offs=00001000 flags=r-x PH-type=0x1[0m
[37mvmlinuz |       virt=[0m[37m00100000 evirt=00500000[0m
[37mvmlinuz |       phys=[0m[37m00100000 ephys=00500000[0m
[37mvmlinuz |       f_sz=[0m[37m00400000 memsz=00400000[0m
[37mvmlinuz | PH  1 offs=00401000 flags=rw- PH-type=0x1[0m
[37mvmlinuz |       virt=[0m[37m00500000 evirt=00a18000[0m
[37mvmlinuz |       phys=[0m[37m00500000 ephys=00a18000[0m
[37mvmlinuz |       f_sz=[0m[37m000687e2 memsz=00518000[0m
[37mvmlinuz | PH  2 offs=003384bc flags=--- PH-type=0x4[0m
[37mvmlinuz |       virt=[0m[37m004374bc evirt=004374e0[0m
[37mvmlinuz |       phys=[0m[37m004374bc ephys=004374e0[0m
[37mvmlinuz |       f_sz=[0m[37m00000024 memsz=00000024[0m
[37mvmlinuz | Starting binary at 0x100000, argc=7 argv=0xafff4f8c *argv=0xb1007ff4 argv0=rom/vmlinuz[0m
[37mvmlinuz | External resolver is at 0xa8000800[0m
[37mvmlinuz | [34;1m======> L4Linux starting... <========[0m[0m
[37mvmlinuz | Linux version 4.15.0-l4-svn58 (huddy1985@huddy1985) (gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.9)) #1 Tue May 1 15:28:27 CST 2018[0m
[37mvmlinuz | Binary name: rom/vmlinuz[0m
[37mvmlinuz | Linux kernel command line (6 args): mem=64M console=ttyLv0 l4x_rd=rom/ramdisk-x86.rd root=1:0 ramdisk_size=4000 init=/bin/sh[0m
[37mvmlinuz | CPU mapping (l:p)[1]: 0:0[0m
[37mvmlinuz | Image: 00100000 - 00a18000 [9312 KiB].[0m
[37mvmlinuz | Areas: Text:     00100000 - 00436ea0 [3291kB][0m
[37mvmlinuz |        RO-Data:  0043a000 - 00500000 [792kB][0m
[37mvmlinuz |        Data:     00500000 - 00533640 [205kB][0m
[37mvmlinuz |        Init:     0053e000 - 00569000 [172kB][0m
[37mvmlinuz |        BSS:      0056a000 - 00602000 [608kB][0m
[37mvmlinuz | gs=43   fs=43[0m
[37mvmlinuz | Device scan:[0m
[37mvmlinuz | Device scan done.[0m
[37mvmlinuz | l4x_x86_fiasco_gdt_entry_offset = 9[0m
[37mvmlinuz | l4lx_thread_create: Created thread 41a (cpu0) (u:b3000e00, v:b3000c00, sp:00501fac)[0m
[37mvmlinuz | main thread will be 41a[0m
[37mvmlinuz | L4x: section-with-init(-data): Virt: 0x500000 to 0xa17fff [5216 KiB][0m
[37mvmlinuz | L4x: section-with-init-text: Virt: 0x500000 to 0xa17fff [5216 KiB][0m
[37mvmlinuz | L4x:            data: Virt: 0x500000 to 0xa17fff [5216 KiB][0m
[37mvmlinuz | L4x: Main thread running, waiting...[0m
[37mvmlinuz | L4x: Memory size: 64MB[0m
[37mvmlinuz | L4x: Setting superpages for main memory[0m
[37mvmlinuz | L4x: Adjusted memory start: 00000000[0m
[37mvmlinuz | L4x:     Main memory: Virt: 0xc00000 to 0x4bfffff [65536 KiB][0m
[37mvmlinuz | L4x: vmalloc area: 04c00000 - 0cc00000[0m
[37mvmlinuz | Filling lower ptabs...[0m
[37mvmlinuz | Done (254 entries).[0m
[37mvmlinuz | L4x:            text: Virt: 0x100000 to 0x4fffff [4096 KiB][0m
[37mvmlinuz | Loading: rom/ramdisk-x86.rd[0m
[37mvmlinuz | Failed to query name 'rom/ramdisk-x86.rd': No such object found(-2)[0m
[37mvmlinuz | Failed to get initrd: No such object found(-2)[0m
[37mvmlinuz | Couldn't load ramdisk :([0m
[37mvmlinuz | Linux version 4.15.0-l4-svn58 (huddy1985@huddy1985) (gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.9)) #1 Tue May 1 15:28:27 CST 2018[0m[37m[0m
[37mvmlinuz | x86/fpu: x87 FPU will use FXSAVE[0m[37m[0m
[37mvmlinuz | e820: BIOS-provided physical RAM map:[0m[37m[0m
[37mvmlinuz | L4Lx-Memory: [mem 0x0000000000000000-0x00000000000fffff] reserved[0m[37m[0m
[37mvmlinuz | L4Lx-Memory: [mem 0x0000000000100000-0x0000000000a17fff] usable[0m[37m[0m
[37mvmlinuz | L4Lx-Memory: [mem 0x0000000000a18000-0x0000000000bfffff] unusable[0m[37m[0m
[37mvmlinuz | L4Lx-Memory: [mem 0x0000000000c00000-0x0000000004bfffff] usable[0m[37m[0m
[37mvmlinuz | Notice: NX (Execute Disable) protection missing in CPU![0m[37m[0m
[37mvmlinuz | .text .data .bss are not marked as E820_TYPE_RAM![0m[37m[0m
[37mvmlinuz | e820: last_pfn = 0x4c00 max_arch_pfn = 0x100000[0m[37m[0m
[37mvmlinuz | 76MB LOWMEM available.[0m[37m[0m
[37mvmlinuz |   mapped low ram: 0 - 04c00000[0m[37m[0m
[37mvmlinuz |   low ram: 0 - 04c00000[0m[37m[0m
[37mvmlinuz | Zone ranges:[0m[37m[0m
[37mvmlinuz |   DMA      empty[0m[37m[0m
[37mvmlinuz |   Normal   [mem 0x0000000000100000-0x0000000004bfffff][0m[37m[0m
[37mvmlinuz | Movable zone start for each node[0m[37m[0m
[37mvmlinuz | Early memory node ranges[0m[37m[0m
[37mvmlinuz |   node   0: [mem 0x0000000000100000-0x0000000000a17fff][0m[37m[0m
[37mvmlinuz |   node   0: [mem 0x0000000000c00000-0x0000000004bfffff][0m[37m[0m
[37mvmlinuz | Initmem setup node 0 [mem 0x0000000000100000-0x0000000004bfffff][0m[37m[0m
[37mvmlinuz | Reserved but unavailable: 16 pages[0m[37m[0m
[37mvmlinuz | e820: [mem 0x04c00000-0xffffffff] available for PCI devices[0m[37m[0m
[37mvmlinuz | clocksource: refined-jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 19112604462750000 ns[0m[37m[0m
[37mvmlinuz | random: fast init done[0m[37m[0m
[37mvmlinuz | Built 1 zonelists, mobility grouping on.  Total pages: 18562[0m[37m[0m
[37mvmlinuz | Kernel command line: mem=64M console=ttyLv0 l4x_rd=rom/ramdisk-x86.rd root=1:0 ramdisk_size=4000 init=/bin/sh[0m[37m[0m
[37mvmlinuz | Dentry cache hash table entries: 16384 (order: 4, 65536 bytes)[0m[37m[0m
[37mvmlinuz | Inode-cache hash table entries: 8192 (order: 3, 32768 bytes)[0m[37m[0m
[37mvmlinuz | Initializing CPU#0[0m[37m[0m
[37mvmlinuz | Memory: 68956K/74848K available (3291K kernel code, 205K rwdata, 792K rodata, 172K init, 608K bss, 5892K reserved, 0K cma-reserved)[0m[37m[0m
[37mvmlinuz | virtual kernel memory layout:[0m[37m[0m
[37mvmlinuz |     fixmap  : 0x0ce01000 - 0x0ce1a000   ( 100 kB)[0m[37m[0m
[37mvmlinuz |   cpu_entry : 0x0cc00000 - 0x0cc28000   ( 160 kB)[0m[37m[0m
[37mvmlinuz |     vmalloc : 0x04c00000 - 0x0cc00000   ( 128 MB)[0m[37m[0m
[37mvmlinuz |     lowmem  : 0x00000000 - 0x04c00000   (  76 MB)[0m[37m[0m
[37mvmlinuz |       .init : [0m[37m0x0053e000 - 0x00569000   ( 172 kB)[0m[37m[0m
[37mvmlinuz |       .data : 0x00436ea0 - 0x00533640   (1009 kB)[0m[37m[0m
[37mvmlinuz |       .text : 0x00100000 - 0x00436ea0   (3291 kB)[0m[37m[0m
[37mvmlinuz | NR_IRQS: 136, nr_irqs: 136, preallocated irqs: 64[0m[37m[0m
[37mvmlinuz | l4x: could not get ICU info: -2004[0m[37m[0m
[37mvmlinuz | Console: colour dummy device 80x25[0m[37m[0m
[37mvmlinuz | console [ttyLv0] enabled[0m[37m[0m
[37mvmlinuz | clocksource: l4kipclk: mask: 0xffffffffffffffff max_cycles: 0x1d854df40, max_idle_ns: 3526361616960 ns[0m[37m[0m
[37mvmlinuz | l4timer: Using IRQ64[0m[37m[0m
[37mvmlinuz | l4lx_thread_create: Created thread 41f (timer0) (u:b3000a00, v:00000000, sp:005a3fa8)[0m
[37mvmlinuz | tsc: Detected 3199.175 MHz processor[0m[37m[0m
[37mvmlinuz | Calibrating delay loop (skipped), value calculated using timer frequency.. 6398.35 BogoMIPS (lpj=31991750)[0m[37m[0m
[37mvmlinuz | pid_max: default: 32768 minimum: 301[0m[37m[0m
[37mvmlinuz | Mount-cache hash table entries: 1024 (order: 0, 4096 bytes)[0m[37m[0m
[37mvmlinuz | Mountpoint-cache hash table entries: 1024 (order: 0, 4096 bytes)[0m[37m[0m
[37mvmlinuz | WARNING: Unknown rdmsr: 00000140 at 0x1139cb[0m
[37mvmlinuz | WARNING: Unknown rdmsr: 000000ce at 0x113b69[0m
[37mvmlinuz | WARNING: Unknown wrmsr: 00000140 at 0x113bac[0m
[37mvmlinuz | Last level iTLB entries: 4KB 0, 2MB 0, 4MB 0[0m[37m[0m
[37mvmlinuz | Last level dTLB entries: 4KB 0, 2MB 0, 4MB 0, 1GB 0[0m[37m[0m
[37mvmlinuz | CPU: Intel QEMU Virtual CPU version 2.5+ (family: 0x6, model: 0x6, stepping: 0x3)[0m[37m[0m
[37mvmlinuz | Spectre V2 mitigation: Mitigation: Full generic retpoline[0m[37m[0m
[37mvmlinuz | Spectre V2 mitigation: Filling RSB on context switch[0m[37m[0m
[37mvmlinuz | WARNING: Unknown rdmsr: 00000186 at 0x54618c[0m
[37mvmlinuz | WARNING: Unknown rdmsr: 00000187 at 0x54618c[0m
[37mvmlinuz | WARNING: Unknown rdmsr: 000000c2 at 0x54624a[0m
[37mvmlinuz | WARNING: Unknown wrmsr: 000000c2 at 0x54625d[0m
[37mvmlinuz | WARNING: Unknown rdmsr: 000000c2 at 0x546263[0m
[37mvmlinuz | Performance Events: PMU not available due to virtualization, using software events only.[0m[37m[0m
[37mvmlinuz | clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 19112604462750000 ns[0m[37m[0m
[37mvmlinuz | futex hash table entries: 256 (order: -1, 3072 bytes)[0m[37m[0m
[37mvmlinuz | NET: Registered protocol family 16[0m[37m[0m
[37mvmlinuz | clocksource: Switched to clocksource l4kipclk[0m[37m[0m
[37mvmlinuz | NET: Registered protocol family 2[0m[37m[0m
[37mvmlinuz | TCP established hash table entries: 1024 (order: 0, 4096 bytes)[0m[37m[0m
[37mvmlinuz | TCP bind hash table entries: 1024 (order: 0, 4096 bytes)[0m[37m[0m
[37mvmlinuz | TCP: Hash tables configured (established 1024 bind 1024)[0m[37m[0m
[37mvmlinuz | UDP hash table entries: 256 (order: 0, 4096 bytes)[0m[37m[0m
[37mvmlinuz | UDP-Lite hash table entries: 256 (order: 0, 4096 bytes)[0m[37m[0m
[37mvmlinuz | NET: Registered protocol family 1[0m[37m[0m
[37mvmlinuz | l4x: Checks passed.[0m[37m[0m
[37mvmlinuz | platform rtc_cmos: registered platform RTC device (no PNP device found)[0m[37m[0m
[37mvmlinuz | workingset: timestamp_bits=30 max_order=15 bucket_order=0[0m[37m[0m
[37mvmlinuz | io scheduler noop registered[0m[37m[0m
[37mvmlinuz | io scheduler deadline registered[0m[37m[0m
[37mvmlinuz | io scheduler cfq registered (default)[0m[37m[0m
[37mvmlinuz | io scheduler mq-deadline registered[0m[37m[0m
[37mvmlinuz | io scheduler kyber registered[0m[37m[0m
[37mvmlinuz | l4fb.0: looking for capability 'fb' as goos session[0m[37m[0m
[37mvmlinuz | l4fb.0: init failed err=-2[0m[37m[0m
[37mvmlinuz | could not allocate fb device: fb[0m[37m[0m
[37mvmlinuz | L4 serial driver[0m[37m[0m
[37mvmlinuz | serial-ttyLv.0: ttyLv0 at MMIO 0x1 (irq = 0, base_baud = 230400) is a L4-vcon[0m[37m[0m
[37mvmlinuz | l4ser_shm: L4 shared mem serial driver[0m[37m[0m
[37mvmlinuz | l4cdds: No name given, not starting.[0m[37m[0m
[37mvmlinuz | brd: module loaded[0m[37m[0m
[37mvmlinuz | l4x: Faking dummy RTC[0m[37m[0m
[37mvmlinuz | rtc_cmos rtc_cmos: rtc core: registered rtc_cmos as rtc0[0m[37m[0m
[37mvmlinuz | rtc_cmos rtc_cmos: only 24-hr supported[0m[37m[0m
[37mvmlinuz | rtc-l4x: l4x-rtc: Could not find 'rtc' cap.[0m[37m[0m
[37mvmlinuz | rtc-l4x: probe of rtc-l4x failed with error -2[0m[37m[0m
[37mvmlinuz | NET: Registered protocol family 10[0m[37m[0m
[37mvmlinuz | Segment Routing with IPv6[0m[37m[0m
[37mvmlinuz | sit: IPv6, IPv4 and MPLS over IPv4 tunneling driver[0m[37m[0m
[37mvmlinuz | NET: Registered protocol family 17[0m[37m[0m
[37mvmlinuz | sched_clock: Marking stable (299000000, 0)->(288157401, 10842599)[0m[37m[0m
[37mvmlinuz | hctosys: unable to open rtc device (rtc0)[0m[37m[0m
[37mvmlinuz | List of all partitions:[0m[37m[0m
[37mvmlinuz | 0100            4000 ram0 [0m[37m[0m
[37mvmlinuz |  (driver?)[0m[37m[0m
[37mvmlinuz | 0101            4000 ram1 [0m[37m[0m
[37mvmlinuz |  (driver?)[0m[37m[0m
[37mvmlinuz | 0102            4000 ram2 [0m[37m[0m
[37mvmlinuz |  (driver?)[0m[37m[0m
[37mvmlinuz | 0103            4000 ram3 [0m[37m[0m
[37mvmlinuz |  (driver?)[0m[37m[0m
[37mvmlinuz | 0104            4000 ram4 [0m[37m[0m
[37mvmlinuz |  (driver?)[0m[37m[0m
[37mvmlinuz | 0105            4000 ram5 [0m[37m[0m
[37mvmlinuz |  (driver?)[0m[37m[0m
[37mvmlinuz | 0106            4000 ram6 [0m[37m[0m
[37mvmlinuz |  (driver?)[0m[37m[0m
[37mvmlinuz | 0107            4000 ram7 [0m[37m[0m
[37mvmlinuz |  (driver?)[0m[37m[0m
[37mvmlinuz | 0108            4000 ram8 [0m[37m[0m
[37mvmlinuz |  (driver?)[0m[37m[0m
[37mvmlinuz | 0109            4000 ram9 [0m[37m[0m
[37mvmlinuz |  (driver?)[0m[37m[0m
[37mvmlinuz | 010a            4000 ram10 [0m[37m[0m
[37mvmlinuz |  (driver?)[0m[37m[0m
[37mvmlinuz | 010b            4000 ram11 [0m[37m[0m
[37mvmlinuz |  (driver?)[0m[37m[0m
[37mvmlinuz | 010c            4000 ram12 [0m[37m[0m
[37mvmlinuz |  (driver?)[0m[37m[0m
[37mvmlinuz | 010d            4000 ram13 [0m[37m[0m
[37mvmlinuz |  (driver?)[0m[37m[0m
[37mvmlinuz | 010e            4000 ram14 [0m[37m[0m
[37mvmlinuz |  (driver?)[0m[37m[0m
[37mvmlinuz | 010f            4000 ram15 [0m[37m[0m
[37mvmlinuz |  (driver?)[0m[37m[0m
[37mvmlinuz | No filesystem could mount root, tried: [0m[37m[0m
[37mvmlinuz |  ext3[0m[37m[0m
[37mvmlinuz |  ext2[0m[37m[0m
[37mvmlinuz |  ext4[0m[37m[0m
[37mvmlinuz | [0m
[37mvmlinuz | Kernel panic - not syncing: VFS: Unable to mount root fs on unknown-block(1,0)[0m[37m[0m
[37mvmlinuz | CPU: 0 PID: 1 Comm: swapper Not tainted 4.15.0-l4-svn58 #1[0m[37m[0m
[37mvmlinuz | Call Trace:[0m[37m[0m
[37mvmlinuz |  ? dump_stack+0x16/0x19[0m[37m[0m
[37mvmlinuz |  ? panic+0x85/0x1ad[0m[37m[0m
[37mvmlinuz |  ? mount_block_root+0x1ff/0x20f[0m[37m[0m
[37mvmlinuz |  ? mount_root+0x63/0x68[0m[37m[0m
[37mvmlinuz |  ? prepare_namespace+0x140/0x167[0m[37m[0m
[37mvmlinuz |  ? kernel_init_freeable+0x144/0x151[0m[37m[0m
[37mvmlinuz |  ? rest_init+0x80/0x80[0m[37m[0m
[37mvmlinuz |  ? kernel_init+0xb/0xf0[0m[37m[0m
[37mvmlinuz |  ? schedule_tail_wrapper+0x9/0xc[0m[37m[0m
[37mvmlinuz |  ? ret_from_fork+0x33/0x40[0m[37m[0m
[37mvmlinuz | Kernel Offset: disabled[0m[37m[0m
[37mvmlinuz | ---[ end Kernel panic - not syncing: VFS: Unable to mount root fs on unknown-block(1,0)[0m[37m[0m
[37mvmlinuz | WARNING: CPU: 0 PID: 1 at arch/l4/kernel/main.c:2206 l4x_blink+0x9/0x50[0m[37m[0m
[37mvmlinuz | Modules linked in:[0m[37m[0m
[37mvmlinuz | CPU: 0 PID: 1 Comm: swapper Not tainted 4.15.0-l4-svn58 #1[0m[37m[0m
[37mvmlinuz | EIP: l4x_blink+0x9/0x50[0m[37m[0m
[37mvmlinuz | EFLAGS: 00000216 CPU: 0[0m[37m[0m
[37mvmlinuz | EAX: 00000001 EBX: 00000000 ECX: b3000c74 EDX: 00101300[0m[37m[0m
[37mvmlinuz | ESI: 00000001 EDI: 00000000 EBP: 0441ff0c ESP: 0441fc5c[0m[37m[0m
[37mvmlinuz |  DS: bb48 ES: ff09 FS: 0043 GS: 0000 SS: 0023[0m[37m[0m
[37mvmlinuz | Call Trace:[0m[37m[0m
[37mvmlinuz |  ? __sprint_symbol+0x9f/0xd0[0m[37m[0m
[37mvmlinuz |  ? string+0x6f/0x80[0m[37m[0m
[37mvmlinuz |  ? symbol_string+0x5f/0x80[0m[37m[0m
[37mvmlinuz |  ? pagevec_lookup_range_tag+0x2b/0x40[0m[37m[0m
[37mvmlinuz |  ? irq_exit+0x6d/0x80[0m[37m[0m
[37mvmlinuz |  ? do_IRQ+0x5c/0xa7[0m[37m[0m
[37mvmlinuz |  ? kfree+0x4d/0x60[0m[37m[0m
[37mvmlinuz |  ? cyc2ns_read_begin+0x52/0x90[0m[37m[0m
[37mvmlinuz |  ? l4x_vcpu_entry+0x78d/0x16b0[0m[37m[0m
[37mvmlinuz |  ? native_sched_clock+0x2f/0xe0[0m[37m[0m
[37mvmlinuz |  ? cyc2ns_read_begin+0x52/0x90[0m[37m[0m
[37mvmlinuz |  ? native_sched_clock+0x2f/0xe0[0m[37m[0m
[37mvmlinuz |  ? cyc2ns_read_begin+0x52/0x90[0m[37m[0m
[37mvmlinuz |  ? native_sched_clock+0x2f/0xe0[0m[37m[0m
[37mvmlinuz |  ? irq_exit+0x6d/0x80[0m[37m[0m
[37mvmlinuz |  ? do_IRQ+0x5c/0xa7[0m[37m[0m
[37mvmlinuz |  ? console_unlock+0x2bd/0x410[0m[37m[0m
[37mvmlinuz |  ? l4x_vcpu_handle_irq+0x3c/0x90[0m[37m[0m
[37mvmlinuz |  ? do_vcpu_irq+0x1b/0x20[0m[37m[0m
[37mvmlinuz |  ? vprintk_default+0x2f/0x40[0m[37m[0m
[37mvmlinuz |  ? l4x_vcpu_entry_kern+0xe60/0xe60[0m[37m[0m
[37mvmlinuz |  ? panic+0x178/0x1ad[0m[37m[0m
[37mvmlinuz |  ? mount_block_root+0x1ff/0x20f[0m[37m[0m
[37mvmlinuz |  ? mount_root+0x63/0x68[0m[37m[0m
[37mvmlinuz |  ? prepare_namespace+0x140/0x167[0m[37m[0m
[37mvmlinuz |  ? kernel_init_freeable+0x144/0x151[0m[37m[0m
[37mvmlinuz |  ? rest_init+0x80/0x80[0m[37m[0m
[37mvmlinuz |  ? kernel_init+0xb/0xf0[0m[37m[0m
[37mvmlinuz |  ? schedule_tail_wrapper+0x9/0xc[0m[37m[0m
[37mvmlinuz |  ? ret_from_fork+0x33/0x40[0m[37m[0m
[37mvmlinuz | Code: 75 b0 85 c9 75 ac 85 c0 75 a8 83 c3 14 81 fb e8 23 50 00 75 e1 e8 e8 9b 01 00 83 c4 1c 5b 5e 5d c3 90 55 89 e5 57 56 53 83 ec 04 <0f> ff c7 04 24 60 ed 4a 00 e8 a3 62 05 00 e8 f4 2f 00 00 e8 cf[0m[37m[0m
[37mvmlinuz | ---[ end trace a1250fc4832a861e ]---[0m[37m[0m
[37mvmlinuz | panic: going to sleep forever, bye[0m[37m[0m
[37mvmlinuz | panic: going to sleep forever, bye[0m
make[1]: Leaving directory '/media/fedora_work/project/real-time/l4re/src/l4'
