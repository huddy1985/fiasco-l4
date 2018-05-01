# fiasco-l4
This repository contains the source codes microkernel also known as the Fiasco.OC microkernel including the L4Linux of Linux4-15.

Why create this repository?
Because when we want to make a complete l4re environment, fiasco microkernel, l4re and l4linux, it build system are so rough, very hard to use.

| Arch   |  32bit |  64bit   |
|--------|--------|----------|
|   X86  |    Y   |working   |

## file list
1. **l4linux**
L4linux-4.15 source tree.
1. **src**
All of fiasco microkernel codes and l4re codes.
```
├── kernel
│   └── fiasco
├── l4
│   ├── BENCHMARKING
│   ├── conf
│   ├── COPYING-GPL-2
│   ├── COPYING-LGPL-2.1
│   ├── LICENSING
│   ├── Makefile
│   ├── mk
│   ├── mybuild
│   ├── pkg
│   └── tool
└── repomgr
```
3. resource
This directory contains the rootfs of drops and ramfs.

## More
The more documents please goto doc directory, includes build and others, comming soon.
