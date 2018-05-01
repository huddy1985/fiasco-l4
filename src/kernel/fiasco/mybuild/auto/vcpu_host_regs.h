// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef vcpu_host_regs_h
#define vcpu_host_regs_h

//
// INTERFACE definition follows 
//

#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/vcpu_host_regs-ia32.cpp"

// This is used as the architecture-specific version
// in the vCPU state structure. This version has to be
// changed / increased whenever any of the data structures
// within the vCPU state changes its layout or its semantics.
enum { Vcpu_arch_version = 0x43 };
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/vcpu_host_regs-ia32.cpp"

struct Vcpu_host_regs {};

#endif // vcpu_host_regs_h
