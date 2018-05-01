// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef cpu_h
#define cpu_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu.cpp"

#include "cpu_mask.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu.cpp"
#include "member_offs.h"
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

#include "types.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "initcalls.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "regdefs.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "per_cpu_data.h"
#line 226 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

#include "l4_types.h"
#line 228 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "initcalls.h"
#line 229 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "per_cpu_data.h"
#line 230 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "gdt.h"
#line 231 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "lock_guard.h"
#line 232 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "spin_lock.h"

//
// INTERFACE definition follows 
//

#line 233 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

class Gdt;
#line 235 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
class Tss;
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu.cpp"

class Cpu
{
  MEMBER_OFFSET();

public:
  struct By_phys_id
  {
    Cpu_phys_id _p;
    By_phys_id(Cpu_phys_id p) : _p(p) {}
    template<typename CPU>
    bool operator () (CPU const &c) const { return _p == c.phys_id(); }
  };
  // we actually use a mask that has one CPU more that we can physically,
  // have, to avoid lots of special cases for an invalid CPU number
  typedef Cpu_mask_t<Config::Max_num_cpus + 1> Online_cpu_mask;

  enum { Invalid = Config::Max_num_cpus };
  static Cpu_number invalid() { return Cpu_number(Invalid); }

  /** Get the logical ID of this CPU */
  Cpu_number id() const;


  /**
   * Set this CPU to online state.
   * NOTE: This does not activate an inactive CPU, Just set the given state.
   */
  void set_online(bool o);
  void set_present(bool o);

  /** Convenience for Cpu::cpus.cpu(cpu).online() */
  static bool online(Cpu_number cpu);
  /** Is this CPU online ? */
  bool online() const;

  static Online_cpu_mask const &online_mask();
  static Online_cpu_mask const &present_mask();

private:

  static Online_cpu_mask _online_mask;
  static Online_cpu_mask _present_mask;

#line 64 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu.cpp"
private:

private:
  void set_id(Cpu_number) {}

#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
private:

public:

  enum Vendor
  {
    Vendor_unknown = 0,
    Vendor_intel,
    Vendor_amd,
    Vendor_cyrix,
    Vendor_via,
    Vendor_umc,
    Vendor_nexgen,
    Vendor_rise,
    Vendor_transmeta,
    Vendor_sis,
    Vendor_nsc
  };

  enum CacheTLB
  {
    Cache_unknown = 0,
    Cache_l1_data,
    Cache_l1_inst,
    Cache_l1_trace,
    Cache_l2,
    Cache_l3,
    Tlb_data_4k,
    Tlb_inst_4k,
    Tlb_data_4M,
    Tlb_inst_4M,
    Tlb_data_4k_4M,
    Tlb_inst_4k_4M,
    Tlb_data_2M_4M,
  };

  enum
  {
    Ldt_entry_size = 8,
  };

  enum Local_features
  {
    Lf_rdpmc		= 0x00000001,
    Lf_rdpmc32		= 0x00000002,
  };

  Unsigned64 time_us() const;
  int can_wrmsr() const;

private:
  void init();
  Unsigned64 _frequency;
  Unsigned32 _version;
  Unsigned32 _brand;
  Unsigned32 _features;
  Unsigned32 _ext_features;
  Unsigned32 _ext_07_ebx;
  Unsigned32 _ext_8000_0001_ecx;
  Unsigned32 _ext_8000_0001_edx;
  Unsigned32 _local_features;

  Unsigned16 _inst_tlb_4k_entries;
  Unsigned16 _data_tlb_4k_entries;
  Unsigned16 _inst_tlb_4m_entries;
  Unsigned16 _data_tlb_4m_entries;
  Unsigned16 _inst_tlb_4k_4m_entries;
  Unsigned16 _data_tlb_4k_4m_entries;
  Unsigned16 _l2_inst_tlb_4k_entries;
  Unsigned16 _l2_data_tlb_4k_entries;
  Unsigned16 _l2_inst_tlb_4m_entries;
  Unsigned16 _l2_data_tlb_4m_entries;

  Unsigned16 _l1_trace_cache_size;
  Unsigned16 _l1_trace_cache_asso;

  Unsigned16 _l1_data_cache_size;
  Unsigned16 _l1_data_cache_asso;
  Unsigned16 _l1_data_cache_line_size;

  Unsigned16 _l1_inst_cache_size;
  Unsigned16 _l1_inst_cache_asso;
  Unsigned16 _l1_inst_cache_line_size;

  Unsigned16 _l2_cache_size;
  Unsigned16 _l2_cache_asso;
  Unsigned16 _l2_cache_line_size;

  Unsigned32 _l3_cache_size;
  Unsigned16 _l3_cache_asso;
  Unsigned16 _l3_cache_line_size;

  Unsigned8 _phys_bits;
  Unsigned8 _virt_bits;

  Vendor _vendor;
  char _model_str[52];

  Unsigned32 _arch_perfmon_info_eax;
  Unsigned32 _arch_perfmon_info_ebx;
  Unsigned32 _arch_perfmon_info_ecx;

  Unsigned32 _monitor_mwait_eax;
  Unsigned32 _monitor_mwait_ebx;
  Unsigned32 _monitor_mwait_ecx;
  Unsigned32 _monitor_mwait_edx;

  Unsigned32 _thermal_and_pm_eax;

  Unsigned32 scaler_tsc_to_ns;
  Unsigned32 scaler_tsc_to_us;
  Unsigned32 scaler_ns_to_tsc;

public:

  void disable(Cpu_number cpu, char const *reason);

  char const *model_str() const { return _model_str; }
  Vendor vendor() const { return _vendor; }

  unsigned family() const
  { return (_version >> 8 & 0xf) + (_version >> 20 & 0xff); }

  char const *vendor_str() const
  { return _vendor == Vendor_unknown ? "Unknown" : vendor_ident[_vendor]; }

  unsigned model() const
  { return (_version >> 4 & 0xf) + (_version >> 12 & 0xf0); }

  unsigned stepping() const { return _version & 0xF; }
  unsigned type() const { return (_version >> 12) & 0x3; }
  Unsigned64 frequency() const { return _frequency; }
  unsigned brand() const { return _brand & 0xFF; }
  unsigned features() const { return _features; }
  unsigned ext_features() const { return _ext_features; }
  bool has_monitor_mwait() const { return _ext_features & (1 << 3); }
  bool has_monitor_mwait_irq() const { return _monitor_mwait_ecx & 3; }

  bool __attribute__((const)) has_smep() const
  { return _ext_07_ebx & FEATX_SMEP; }

  unsigned ext_8000_0001_ecx() const { return _ext_8000_0001_ecx; }
  unsigned ext_8000_0001_edx() const { return _ext_8000_0001_edx; }
  unsigned local_features() const { return _local_features; }
  bool superpages() const { return features() & FEAT_PSE; }
  bool tsc() const { return features() & FEAT_TSC; }
  bool sysenter() const { return features() & FEAT_SEP; }
  bool syscall() const { return ext_8000_0001_edx() & FEATA_SYSCALL; }
  bool vmx() { return boot_cpu()->ext_features() & FEATX_VMX; }
  bool svm() { return boot_cpu()->ext_8000_0001_ecx() & FEATA_SVM; }
  bool has_amd_osvw() { return  boot_cpu()->ext_8000_0001_ecx() & (1<<9); }
  unsigned virt_bits() const { return _virt_bits; }
  unsigned phys_bits() const { return _phys_bits; }
  Unsigned32 get_scaler_tsc_to_ns() const { return scaler_tsc_to_ns; }
  Unsigned32 get_scaler_tsc_to_us() const { return scaler_tsc_to_us; }
  Unsigned32 get_scaler_ns_to_tsc() const { return scaler_ns_to_tsc; }

  Address volatile &kernel_sp() const;

public:
  static Per_cpu<Cpu> cpus;
  static Cpu *boot_cpu() { return _boot_cpu; }

  static bool have_superpages() { return boot_cpu()->superpages(); }
  static bool have_sysenter() { return boot_cpu()->sysenter(); }
  static bool have_syscall() { return boot_cpu()->syscall(); }
  static bool have_fxsr() { return boot_cpu()->features() & FEAT_FXSR; }
  static bool have_pge() { return boot_cpu()->features() & FEAT_PGE; }
  static bool have_xsave() { return boot_cpu()->ext_features() & FEATX_XSAVE; }

  bool has_xsave() const { return ext_features() & FEATX_XSAVE; }

private:

  static Cpu *_boot_cpu;

  struct Vendor_table {
    Unsigned32 vendor_mask;
    Unsigned32 vendor_code;
    Unsigned16 l2_cache;
    char       vendor_string[32];
  } __attribute__((packed));

  struct Cache_table {
    Unsigned8  desc;
    Unsigned8  level;
    Unsigned16 size;
    Unsigned8  asso;
    Unsigned8  line_size;
  };

  static Vendor_table const intel_table[];
  static Vendor_table const amd_table[];
  static Vendor_table const cyrix_table[];
  static Vendor_table const via_table[];
  static Vendor_table const umc_table[];
  static Vendor_table const nexgen_table[];
  static Vendor_table const rise_table[];
  static Vendor_table const transmeta_table[];
  static Vendor_table const sis_table[];
  static Vendor_table const nsc_table[];

  static Cache_table const intel_cache_table[];

  static char const * const vendor_ident[];
  static Vendor_table const * const vendor_table[];

  static char const * const exception_strings[];

#line 236 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
private:

public:
  enum Lbr
  {
    Lbr_uninitialized = 0,
    Lbr_unsupported,
    Lbr_pentium_6,
    Lbr_pentium_4,
    Lbr_pentium_4_ext,
  };

  enum Bts
  {
    Bts_uninitialized = 0,
    Bts_unsupported,
    Bts_pentium_m,
    Bts_pentium_4,
  };

private:
  /** Flags if lbr or bts facilities are activated, used by double-fault
   *  handler to reset the debugging facilities
   */
  Unsigned32 debugctl_busy;

  /** debugctl value for activating lbr or bts */
  Unsigned32 debugctl_set;

  /** debugctl value to reset activated lr/bts facilities in the double-faukt
   *  handler
   */
  Unsigned32 debugctl_reset;

  /** supported lbr type */
  Lbr _lbr;

  /** supported bts type */
  Bts _bts;

  /** is lbr active ? */
  char lbr_active;

  /** is btf active ? */
  char btf_active;

  /** is bts active ? */
  char bts_active;

  Gdt *gdt;
  Tss *tss;
  Tss *tss_dbf;

public:
  Lbr lbr_type() const { return _lbr; }
  Bts bts_type() const { return _bts; }
  bool lbr_status() const { return lbr_active; }
  bool bts_status() const { return bts_active; }
  bool btf_status() const { return btf_active; }

  Gdt* get_gdt() const { return gdt; }
  Tss* get_tss() const { return tss; }
  void set_gdt() const
  {
    Pseudo_descriptor desc((Address)gdt, Gdt::gdt_max-1);
    Gdt::set (&desc);
  }

  static void set_tss() { set_tr(Gdt::gdt_tss); }

private:
  void init_lbr_type();
  void init_bts_type();


#line 1283 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
private:

private:
  Unsigned64 _suspend_tsc;

#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
private:

  Mword _sysenter_eip;

public:  
#line 676 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  explicit FIASCO_INIT_CPU
  Cpu(Cpu_number cpu);
  
#line 692 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static void
  init_global_features();
  
#line 697 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static char const *
  exception_string(Mword trapno);
  
#line 705 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline FIASCO_INIT_CPU_AND_PM
  void
  cpuid(Unsigned32 mode,
             Unsigned32 *eax, Unsigned32 *ebx,
             Unsigned32 *ecx, Unsigned32 *edx);
  
#line 715 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline FIASCO_INIT_CPU
  void
  cpuid(Unsigned32 mode, Unsigned32 ecx_val,
             Unsigned32 *eax, Unsigned32 *ebx,
             Unsigned32 *ecx, Unsigned32 *edx);
  
#line 726 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  void
  update_features_info();
  
#line 874 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static unsigned
  amd_cpuid_mnc();
  
#line 907 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  inline FIASCO_INIT_CPU
  void
  arch_perfmon_info(Unsigned32 *eax, Unsigned32 *ebx, Unsigned32 *ecx) const;
  
#line 917 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static unsigned long
  get_features();
  
#line 948 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  /** Identify the CPU features.
      Attention: This function may be called more than once. The reason is
      that enabling a Local APIC that was previously disabled by the BIOS
      may change the processor features. Therefore, this function has to
      be called again after the Local APIC was enabled.
   */
  FIASCO_INIT_CPU
  void
  identify();
  
#line 1120 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  inline void
  busy_wait_ns(Unsigned64 ns);
  
#line 1130 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  bool
  if_show_infos() const;
  
#line 1142 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  void
  show_cache_tlb_info(const char *indent) const;
  
#line 1210 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  // Function used for calculating apic scaler
  
  static inline Unsigned32
  muldiv(Unsigned32 val, Unsigned32 mul, Unsigned32 div);
  
#line 1225 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Unsigned16
  get_cs();
  
#line 1234 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Unsigned16
  get_ds();
  
#line 1243 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Unsigned16
  get_es();
  
#line 1252 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Unsigned16
  get_ss();
  
#line 1261 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  set_ds(Unsigned16 val);
  
#line 1266 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  set_es(Unsigned16 val);
  
#line 1290 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  FIASCO_INIT_AND_PM
  void
  pm_suspend();
  
#line 1301 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  FIASCO_INIT_AND_PM
  void
  pm_resume();
  
#line 1328 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  set_cr0(unsigned long val);
  
#line 1333 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  set_pdbr(unsigned long addr);
  
#line 1338 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  set_cr4(unsigned long val);
  
#line 1343 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  set_ldt(Unsigned16 val);
  
#line 1349 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  set_ss(Unsigned16 val);
  
#line 1354 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  set_tr(Unsigned16 val);
  
#line 1359 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  xsetbv(Unsigned64 val, Unsigned32 xcr);
  
#line 1368 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Unsigned64
  xgetbv(Unsigned32 xcr);
  
#line 1380 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Mword
  get_cr0();
  
#line 1389 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Address
  get_pdbr();
  
#line 1394 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Mword
  get_cr4();
  
#line 1399 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Unsigned16
  get_ldt();
  
#line 1404 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Unsigned16
  get_tr();
  
#line 1414 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Unsigned64
  rdmsr(Unsigned32 reg);
  
#line 1424 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Unsigned64
  rdpmc(Unsigned32 idx, Unsigned32);
  
#line 1434 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  wrmsr(Unsigned32 low, Unsigned32 high, Unsigned32 reg);
  
#line 1439 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  wrmsr(Unsigned64 msr, Unsigned32 reg);
  
#line 1444 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  enable_rdpmc();
  
#line 1494 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  inline void
  lbr_enable(bool on);
  
#line 1517 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  inline void
  btf_enable(bool on);
  
#line 1541 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  void
  bts_enable(bool on);
  
#line 1572 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  inline void
  debugctl_enable();
  
#line 1580 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  inline void
  debugctl_disable();
  
#line 1587 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  /*
   * AMD OS-Visible Workaround Information
   * print a warning if a CPU is affected by any known erratum
   */
  
  void
  print_errata();
  
#line 1703 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  void
  print_infos() const;
  
#line 1797 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  inline void
  enable_ldt(Address addr, int size);
  
#line 1814 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Unsigned16
  get_fs();
  
#line 1819 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline Unsigned16
  get_gs();
  
#line 1824 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  set_fs(Unsigned16 val);
  
#line 1829 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  static inline void
  set_gs(Unsigned16 val);
  
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  static inline Mword
  stack_align(Mword stack);
  
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  inline Unsigned64
  ns_to_tsc(Unsigned64 ns) const;
  
#line 40 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  inline Unsigned64
  tsc_to_ns(Unsigned64 tsc) const;
  
#line 62 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  inline Unsigned64
  tsc_to_us(Unsigned64 tsc) const;
  
#line 83 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  inline void
  tsc_to_s_and_ns(Unsigned64 tsc, Unsigned32 *s, Unsigned32 *ns) const;
  
#line 107 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  static inline Unsigned64
  rdtsc();
  
#line 116 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  static inline Unsigned32
  get_flags();
  
#line 121 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  static inline void
  set_flags(Unsigned32 efl);
  
#line 134 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  static inline void
  set_cs();
  
#line 144 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  FIASCO_INIT_CPU
  void
  init_tss_dbf(Address tss_dbf_mem, Address kdir);
  
#line 169 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  FIASCO_INIT_CPU
  void
  init_tss(Address tss_mem, size_t tss_size);
  
#line 185 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  FIASCO_INIT_CPU
  void
  init_gdt(Address gdt_mem, Address user_max);
  
#line 223 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  void
  set_fast_entry(void (*func)(void));
  
#line 233 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  inline void
  setup_sysenter() const;
  
#line 241 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  FIASCO_INIT_AND_PM
  void
  init_sysenter();

private:  
#line 732 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  FIASCO_INIT_CPU
  void
  cache_tlb_intel();
  
#line 812 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  FIASCO_INIT_CPU
  void
  cache_tlb_l1();
  
#line 833 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  FIASCO_INIT_CPU
  void
  cache_tlb_l2_l3();
  
#line 862 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  FIASCO_INIT_CPU
  void
  addr_size_info();
  
#line 886 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  FIASCO_INIT_CPU
  void
  set_model_str();
  
#line 1617 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  /**
   * Enable hardware controlled performance states (HWP) if available.
   *
   * HWP enables the processor to autonomously select performance states. The OS
   * can hint the CPU at the desired optimizations. For example, a system running
   * on battery may hint the CPU to optimize for low power consumption. We just
   * enable HWP and configure it to select the performance target autonomously.
   *
   * See Intel Manual Volume 3 Chapter 14.4 for details.
   */
  FIASCO_INIT_CPU
  void
  try_enable_hw_performance_states(bool resume);
  
#line 1716 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  // Return 2^32 / (tsc clocks per usec)
  FIASCO_INIT_CPU
  void
  calibrate_tsc();
  
#line 1837 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
  inline FIASCO_INIT_CPU_AND_PM
  void
  init_indirect_branch_mitigation();
  
#line 214 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
  inline void
  set_sysenter(void (*func)(void));
};
#line 70 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu.cpp"


// --------------------------------------------------------------------------

#line 218 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


//-----------------------------------------------------------------------------
/*
 * Fiasco ia32-native
 * Architecture specific cpu init code
 */

#line 313 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

//-----------------------------------------------------------------------------


//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 1280 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
#include "processor.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"
#include "tss.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 704 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

inline FIASCO_INIT_CPU_AND_PM
void
Cpu::cpuid(Unsigned32 mode,
           Unsigned32 *eax, Unsigned32 *ebx,
           Unsigned32 *ecx, Unsigned32 *edx)
{
  asm volatile ("cpuid" : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
                        : "a" (mode));
}

#line 714 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

inline FIASCO_INIT_CPU
void
Cpu::cpuid(Unsigned32 mode, Unsigned32 ecx_val,
           Unsigned32 *eax, Unsigned32 *ebx,
           Unsigned32 *ecx, Unsigned32 *edx)
{
  asm volatile ("cpuid" : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
                        : "a" (mode), "c" (ecx_val));
}

#line 906 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

inline FIASCO_INIT_CPU
void
Cpu::arch_perfmon_info(Unsigned32 *eax, Unsigned32 *ebx, Unsigned32 *ecx) const
{
  *eax = _arch_perfmon_info_eax;
  *ebx = _arch_perfmon_info_ebx;
  *ecx = _arch_perfmon_info_ecx;
}

#line 1118 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::busy_wait_ns(Unsigned64 ns)
{
  Unsigned64 stop = rdtsc () + ns_to_tsc(ns);

  while (rdtsc() < stop)
    Proc::pause();
}

#line 1209 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

// Function used for calculating apic scaler

inline Unsigned32
Cpu::muldiv(Unsigned32 val, Unsigned32 mul, Unsigned32 div)
{
  Unsigned32 dummy;

  asm volatile ("mull %3 ; divl %4\n\t"
               :"=a" (val), "=d" (dummy)
               : "0" (val),  "d" (mul),  "c" (div));
  return val;
}

#line 1222 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"



inline Unsigned16
Cpu::get_cs()
{
  Unsigned16 val;
  asm volatile ("mov %%cs, %0" : "=rm" (val));
  return val;
}

#line 1232 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Unsigned16
Cpu::get_ds()
{
  Unsigned16 val;
  asm volatile ("mov %%ds, %0" : "=rm" (val));
  return val;
}

#line 1241 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Unsigned16
Cpu::get_es()
{
  Unsigned16 val;
  asm volatile ("mov %%es, %0" : "=rm" (val));
  return val;
}

#line 1250 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Unsigned16
Cpu::get_ss()
{
  Unsigned16 val;
  asm volatile ("mov %%ss, %0" : "=rm" (val));
  return val;
}

#line 1259 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::set_ds(Unsigned16 val)
{ asm volatile ("mov %0, %%ds" : : "rm" (val)); }

#line 1264 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::set_es(Unsigned16 val)
{ asm volatile ("mov %0, %%es" : : "rm" (val)); }

#line 1326 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::set_cr0(unsigned long val)
{ asm volatile ("mov %0, %%cr0" : : "r" (val)); }

#line 1331 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::set_pdbr(unsigned long addr)
{ asm volatile ("mov %0, %%cr3" : : "r" (addr)); }

#line 1336 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::set_cr4(unsigned long val)
{ asm volatile ("mov %0, %%cr4" : : "r" (val)); }

#line 1341 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::set_ldt(Unsigned16 val)
{ asm volatile ("lldt %0" : : "rm" (val)); }

#line 1346 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"



inline void
Cpu::set_ss(Unsigned16 val)
{ asm volatile ("mov %0, %%ss" : : "r" (val)); }

#line 1352 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::set_tr(Unsigned16 val)
{ asm volatile ("ltr %0" : : "rm" (val)); }

#line 1357 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::xsetbv(Unsigned64 val, Unsigned32 xcr)
{
  asm volatile ("xsetbv" : : "a" ((Mword)val),
                             "d" ((Mword)(val >> 32)),
                             "c" (xcr));
}

#line 1366 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Unsigned64
Cpu::xgetbv(Unsigned32 xcr)
{
  Unsigned32 eax, edx;
  asm volatile("xgetbv"
               : "=a" (eax),
                 "=d" (edx)
               : "c" (xcr));
  return eax | ((Unsigned64)edx << 32);
}

#line 1378 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Mword
Cpu::get_cr0()
{
  Mword val;
  asm volatile ("mov %%cr0, %0" : "=r" (val));
  return val;
}

#line 1387 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Address
Cpu::get_pdbr()
{ Address addr; asm volatile ("mov %%cr3, %0" : "=r" (addr)); return addr; }

#line 1392 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Mword
Cpu::get_cr4()
{ Mword val; asm volatile ("mov %%cr4, %0" : "=r" (val)); return val; }

#line 1397 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Unsigned16
Cpu::get_ldt()
{ Unsigned16 val; asm volatile ("sldt %0" : "=rm" (val)); return val; }

#line 1402 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Unsigned16
Cpu::get_tr()
{ Unsigned16 val; asm volatile ("str %0" : "=rm" (val)); return val; }

#line 1412 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Unsigned64
Cpu::rdmsr(Unsigned32 reg)
{
  Unsigned32 l,h;

  asm volatile ("rdmsr" : "=a" (l), "=d" (h) : "c" (reg));
  return ((Unsigned64)h << 32) + (Unsigned64)l;
}

#line 1422 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Unsigned64
Cpu::rdpmc(Unsigned32 idx, Unsigned32)
{
  Unsigned32 l,h;

  asm volatile ("rdpmc" : "=a" (l), "=d" (h) : "c" (idx));
  return ((Unsigned64)h << 32) + (Unsigned64)l;
}

#line 1432 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::wrmsr(Unsigned32 low, Unsigned32 high, Unsigned32 reg)
{ asm volatile ("wrmsr" : : "a" (low), "d" (high), "c" (reg)); }

#line 1437 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::wrmsr(Unsigned64 msr, Unsigned32 reg)
{ asm volatile ("wrmsr" : : "a" ((Unsigned32)msr), "d" ((Unsigned32)(msr >> 32)), "c" (reg)); }

#line 1442 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::enable_rdpmc()
{ set_cr4(get_cr4() | CR4_PCE); }

#line 1491 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"



inline void
Cpu::lbr_enable(bool on)
{
  if (lbr_type() != Lbr_unsupported)
    {
      if (on)
	{
	  lbr_active    = true;
	  debugctl_set |= 1;
	  debugctl_busy = true;
	}
      else
	{
	  lbr_active    = false;
	  debugctl_set &= ~1;
	  debugctl_busy = lbr_active || bts_active;
	  wrmsr(debugctl_reset, MSR_DEBUGCTLA);
	}
    }
}

#line 1514 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"



inline void
Cpu::btf_enable(bool on)
{
  if (lbr_type() != Lbr_unsupported)
    {
      if (on)
	{
	  btf_active      = true;
	  debugctl_set   |= 2;
	  debugctl_reset |= 2; /* don't disable bit in kernel */
	  wrmsr(2, MSR_DEBUGCTLA);     /* activate _now_ */
	}
      else
	{
	  btf_active    = false;
	  debugctl_set &= ~2;
	  debugctl_busy = lbr_active || bts_active;
	  wrmsr(debugctl_reset, MSR_DEBUGCTLA);
	}
    }
}

#line 1570 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::debugctl_enable()
{
  if (debugctl_busy)
    wrmsr(debugctl_set, MSR_DEBUGCTLA);
}

#line 1578 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::debugctl_disable()
{
  if (debugctl_busy)
    wrmsr(debugctl_reset, MSR_DEBUGCTLA);
}

#line 1794 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"



inline void
Cpu::enable_ldt(Address addr, int size)
{
  if (!size)
    {
      get_gdt()->clear_entry (Gdt::gdt_ldt / 8);
      set_ldt(0);
    }
  else
    {
      get_gdt()->set_entry_byte(Gdt::gdt_ldt / 8, addr, size-1, 2/*=ldt*/, 0);
      set_ldt(Gdt::gdt_ldt);
    }
}

#line 1811 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"



inline Unsigned16
Cpu::get_fs()
{ Unsigned16 val; asm volatile ("mov %%fs, %0" : "=rm" (val)); return val; }

#line 1817 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Unsigned16
Cpu::get_gs()
{ Unsigned16 val; asm volatile ("mov %%gs, %0" : "=rm" (val)); return val; }

#line 1822 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::set_fs(Unsigned16 val)
{ asm volatile ("mov %0, %%fs" : : "rm" (val)); }

#line 1827 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline void
Cpu::set_gs(Unsigned16 val)
{ asm volatile ("mov %0, %%gs" : : "rm" (val)); }

#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"


inline Mword
Cpu::stack_align(Mword stack)
{ return stack & ~0x3; }

#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"



inline Unsigned64
Cpu::ns_to_tsc(Unsigned64 ns) const
{
  Unsigned32 dummy;
  Unsigned64 tsc;
  asm volatile
	("movl  %%edx, %%ecx		\n\t"
	 "mull	%3			\n\t"
	 "movl	%%ecx, %%eax		\n\t"
	 "movl	%%edx, %%ecx		\n\t"
	 "mull	%3			\n\t"
	 "addl	%%ecx, %%eax		\n\t"
	 "adcl	$0, %%edx		\n\t"
	 "shld	$5, %%eax, %%edx	\n\t"
	 "shll	$5, %%eax		\n\t"
	:"=A" (tsc), "=&c" (dummy)
	: "0" (ns),  "b" (scaler_ns_to_tsc)
	);
  return tsc;
}

#line 38 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"


inline Unsigned64
Cpu::tsc_to_ns(Unsigned64 tsc) const
{
  Unsigned32 dummy;
  Unsigned64 ns;
  asm volatile
	("movl  %%edx, %%ecx		\n\t"
	 "mull	%3			\n\t"
	 "movl	%%ecx, %%eax		\n\t"
	 "movl	%%edx, %%ecx		\n\t"
	 "mull	%3			\n\t"
	 "addl	%%ecx, %%eax		\n\t"
	 "adcl	$0, %%edx		\n\t"
	 "shld	$5, %%eax, %%edx	\n\t"
	 "shll	$5, %%eax		\n\t"
	:"=A" (ns), "=&c" (dummy)
	: "0" (tsc), "b" (scaler_tsc_to_ns)
	);
  return ns;
}

#line 60 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"


inline Unsigned64
Cpu::tsc_to_us(Unsigned64 tsc) const
{
  Unsigned32 dummy;
  Unsigned64 us;
  asm volatile
	("movl  %%edx, %%ecx		\n\t"
	 "mull	%3			\n\t"
	 "movl	%%ecx, %%eax		\n\t"
	 "movl	%%edx, %%ecx		\n\t"
	 "mull	%3			\n\t"
	 "addl	%%ecx, %%eax		\n\t"
	 "adcl	$0, %%edx		\n\t"
	:"=A" (us), "=&c" (dummy)
	: "0" (tsc), "S" (scaler_tsc_to_us)
	);
  return us;
}

#line 80 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"



inline void
Cpu::tsc_to_s_and_ns(Unsigned64 tsc, Unsigned32 *s, Unsigned32 *ns) const
{
    Unsigned32 dummy;
    __asm__
	("				\n\t"
	 "movl  %%edx, %%ecx		\n\t"
	 "mull	%4			\n\t"
	 "movl	%%ecx, %%eax		\n\t"
	 "movl	%%edx, %%ecx		\n\t"
	 "mull	%4			\n\t"
	 "addl	%%ecx, %%eax		\n\t"
	 "adcl	$0, %%edx		\n\t"
	 "movl  $1000000000, %%ecx	\n\t"
	 "shld	$5, %%eax, %%edx	\n\t"
	 "shll	$5, %%eax		\n\t"
	 "divl  %%ecx			\n\t"
	:"=a" (*s), "=d" (*ns), "=&c" (dummy)
	: "A" (tsc), "g" (scaler_tsc_to_ns)
	);
}

#line 104 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"



inline Unsigned64
Cpu::rdtsc()
{
  Unsigned64 tsc;
  asm volatile ("rdtsc" : "=A" (tsc));
  return tsc;
}

#line 114 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"


inline Unsigned32
Cpu::get_flags()
{ Unsigned32 efl; asm volatile ("pushfl ; popl %0" : "=r"(efl)); return efl; }

#line 119 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"


inline void
Cpu::set_flags(Unsigned32 efl)
{ asm volatile ("pushl %0 ; popfl" : : "rm" (efl) : "memory"); }

#line 132 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"


inline void
Cpu::set_cs()
{
  asm volatile("ljmp %0, $1f ; 1:"
               : : "i"(Gdt::gdt_code_kernel | Gdt::Selector_kernel));
}

#line 231 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"


inline void
Cpu::setup_sysenter() const
{
  wrmsr(Gdt::gdt_code_kernel, 0, MSR_SYSENTER_CS);
  wrmsr((unsigned long)&kernel_sp(), 0, MSR_SYSENTER_ESP);
  wrmsr(_sysenter_eip, 0, MSR_SYSENTER_EIP);
}

#line 77 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu.cpp"


inline Cpu::Online_cpu_mask const &
Cpu::online_mask()
{ return _online_mask; }

#line 82 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu.cpp"


inline Cpu::Online_cpu_mask const &
Cpu::present_mask()
{ return _present_mask; }

#line 87 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu.cpp"


inline void
Cpu::set_online(bool o)
{
  if (o)
    _online_mask.atomic_set(id());
  else
    _online_mask.atomic_clear(id());
}

#line 97 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu.cpp"


inline void
Cpu::set_present(bool o)
{
  if (o)
    _present_mask.atomic_set(id());
  else
    _present_mask.atomic_clear(id());
}

#line 128 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu.cpp"


inline Cpu_number
Cpu::id() const
{ return Cpu_number::boot_cpu(); }

#line 133 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu.cpp"


inline bool
Cpu::online() const
{ return true; }

#line 138 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/cpu.cpp"


inline bool
Cpu::online(Cpu_number _cpu)
{ return _cpu == Cpu_number::boot_cpu(); }

#line 1407 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline int
Cpu::can_wrmsr() const
{ return features() & FEAT_MSR; }

#line 1787 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


inline Unsigned64
Cpu::time_us() const
{
  return tsc_to_us (rdtsc());
}

#line 124 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/32/cpu-32.cpp"


inline Address volatile &
Cpu::kernel_sp() const
{ return *reinterpret_cast<Address volatile *>(&get_tss()->_esp0); }

#endif // cpu_h
