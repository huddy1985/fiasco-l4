// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "apic.h"
#include "apic_i.h"

#line 104 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

DEFINE_PER_CPU Per_cpu<Static_object<Apic> >  Apic::apic;
#line 114 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

// FIXME: workaround for missing lambdas in gcc < 4.5
namespace {
struct By_id
{
  Unsigned32 p;
  By_id(Unsigned32 p) : p(p) {}
  bool operator () (Apic const *a) const { return a && a->apic_id() == p; }
};
}
#line 137 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

//----------------------------------------------------------------------------

#line 220 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

unsigned apic_spurious_interrupt_bug_cnt;
#line 222 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
unsigned apic_spurious_interrupt_cnt;
#line 223 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
unsigned apic_error_cnt;
#line 224 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
Address  apic_io_base;
#line 225 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

int        Apic::present;
#line 227 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
int        Apic::good_cpu;
#line 228 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
const Address Apic::io_base = Mem_layout::Local_apic_page;
#line 229 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
Address    Apic::phys_base;
#line 230 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
unsigned   Apic::timer_divisor = 1;
#line 231 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
unsigned   Apic::frequency_khz;
#line 232 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"
Unsigned64 Apic::scaler_us_to_apic;
#line 233 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

int ignore_invalid_apic_reg_access;

#line 249 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline int
Apic::is_integrated()
{
  return reg_read(APIC_lvr) & 0xF0;
}

#line 256 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline Unsigned32
Apic::get_max_lvt_local()
{
  return ((reg_read(APIC_lvr) >> 16) & 0xFF);
}

#line 263 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline Unsigned32
Apic::get_num_errors()
{
  reg_write(APIC_esr, 0);
  return reg_read(APIC_esr);
}

#line 271 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


inline void
Apic::clear_num_errors()
{
  reg_write(APIC_esr, 0);
  reg_write(APIC_esr, 0);
}

#line 109 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"



Cpu &
Apic::cpu() { return *Cpu::boot_cpu(); }

#line 124 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


Cpu_number
Apic::find_cpu(Unsigned32 phys_id)
{
  return apic.find_cpu(By_id(phys_id));
}

#line 131 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

void
Apic::pm_on_suspend(Cpu_number)
{
  _saved_apic_timer = timer_reg_read();
}

#line 140 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

void
Apic::pm_on_resume(Cpu_number)
{
  Apic::init(true);
  timer_reg_write(_saved_apic_timer);
}

#line 341 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

// set the global pagetable entry for the Local APIC device registers

FIASCO_INIT_AND_PM
void
Apic::map_apic_page()
{
  Address offs;
  Address base = apic_page_phys();
  // We should not change the physical address of the Local APIC page if
  // possible since some versions of VMware would complain about a
  // non-implemented feature
  Kmem::map_phys_page(base, Mem_layout::Local_apic_page,
		      false, true, &offs);

  Kip::k()->add_mem_region(Mem_desc(base, base + Config::PAGE_SIZE - 1, Mem_desc::Reserved));

  assert(offs == 0);
}

#line 360 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

// check CPU type if APIC could be present
FIASCO_INIT_AND_PM
int
Apic::test_cpu()
{
  if (!cpu().can_wrmsr() || !(cpu().features() & FEAT_TSC))
    return 0;

  if (cpu().vendor() == Cpu::Vendor_intel)
    {
      if (cpu().family() == 15)
	return 1;
      if (cpu().family() >= 6)
	return 1;
    }
  if (cpu().vendor() == Cpu::Vendor_amd && cpu().family() >= 6)
    return 1;

  return 0;
}

#line 454 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


void
Apic::timer_set_divisor(unsigned newdiv)
{
  int i;
  int div = -1;
  int divval = newdiv;
  Unsigned32 tmp_value;

  static int divisor_tab[8] =
    {
      APIC_tdr_div_1,  APIC_tdr_div_2,  APIC_tdr_div_4,  APIC_tdr_div_8,
      APIC_tdr_div_16, APIC_tdr_div_32, APIC_tdr_div_64, APIC_tdr_div_128
    };

  for (i=0; i<8; i++)
    {
      if (divval & 1)
	{
	  if (divval & ~1)
	    {
	      printf("bad APIC divisor %u\n", newdiv);
	      return;
	    }
	  div = divisor_tab[i];
	  break;
	}
      divval >>= 1;
    }

  if (div != -1)
    {
      timer_divisor = newdiv;
      tmp_value = reg_read(APIC_tdcr);
      tmp_value &= ~0x1F;
      tmp_value |= div;
      reg_write(APIC_tdcr, tmp_value);
    }
}

#line 494 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


int
Apic::get_max_lvt()
{
  return is_integrated() ? get_max_lvt_local() : 2;
}

#line 515 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

// check if APIC is working (check timer functionality)
FIASCO_INIT_AND_PM
int
Apic::check_working()
{
  Unsigned64 tsc_until;

  timer_disable_irq();
  timer_set_divisor(1);
  timer_reg_write(0x10000000);

  tsc_until = Cpu::rdtsc() + 0x400;  // we only have to wait for one bus cycle

  do
    {
      if (timer_reg_read() != 0x10000000)
        return 1;
    } while (Cpu::rdtsc() < tsc_until);

  return 0;
}

#line 537 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

FIASCO_INIT_CPU_AND_PM
void
Apic::init_spiv()
{
  Unsigned32 tmp_val;

  tmp_val = reg_read(APIC_spiv);
  tmp_val |= (1<<8);            // enable APIC
  tmp_val &= ~(1<<9);           // enable Focus Processor Checking
  tmp_val &= ~0xff;
  tmp_val |= APIC_IRQ_BASE + 0xf; // Set spurious IRQ vector to 0x3f
                              // bit 0..3 are hardwired to 1 on PPro!
  reg_write(APIC_spiv, tmp_val);
}

#line 562 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

FIASCO_INIT_CPU_AND_PM
void
Apic::init_tpr()
{
  reg_write(APIC_tpr, 0);
}

#line 569 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

// activate APIC error interrupt
FIASCO_INIT_CPU_AND_PM
void
Apic::enable_errors()
{
  if (is_integrated())
    {
      Unsigned32 tmp_val, before, after;

      if (get_max_lvt() > 3)
	clear_num_errors();
      before = get_num_errors();

      tmp_val = reg_read(APIC_lvterr);
      tmp_val &= 0xfffeff00;         // unmask error IRQ vector
      tmp_val |= APIC_IRQ_BASE + 3;  // Set error IRQ vector to 0x63
      reg_write(APIC_lvterr, tmp_val);

      if (get_max_lvt() > 3)
	clear_num_errors();
      after = get_num_errors();
      if (Config::Warn_level >= 2)
        printf("APIC ESR value before/after enabling: %08x/%08x\n",
               before, after);
    }
}

#line 596 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

// activate APIC after activating by MSR was successful
// see "Intel Architecture Software Developer's Manual,
//      Volume 3: System Programming Guide, Appendix E"
FIASCO_INIT_AND_PM
void
Apic::route_pic_through_apic()
{
  Unsigned32 tmp_val;
  auto guard = lock_guard(cpu_lock);

  // mask 8259 interrupts
  Unsigned16 old_irqs = Pic::disable_all_save();

  // set LINT0 to ExtINT, edge triggered
  tmp_val = reg_read(APIC_lvt0);
  tmp_val &= 0xfffe5800;
  tmp_val |= 0x00000700;
  reg_write(APIC_lvt0, tmp_val);

  // set LINT1 to NMI, edge triggered
  tmp_val = reg_read(APIC_lvt1);
  tmp_val &= 0xfffe5800;
  tmp_val |= 0x00000400;
  reg_write(APIC_lvt1, tmp_val);

  // unmask 8259 interrupts
  Pic::restore_all(old_irqs);

  printf("APIC was disabled --- routing PIC through APIC\n");
}

#line 627 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

FIASCO_INIT_CPU_AND_PM
void
Apic::init_lvt()
{
  auto guard = lock_guard(cpu_lock);

  // mask timer interrupt and set vector to _not_ invalid value
  reg_write(APIC_lvtt, reg_read(APIC_lvtt) | APIC_lvt_masked | 0xff);

  if (have_pcint())
    // mask performance interrupt and set vector to a valid value
    reg_write(APIC_lvtpc, reg_read(APIC_lvtpc) | APIC_lvt_masked | 0xff);

  if (have_tsint())
    // mask thermal sensor interrupt and set vector to a valid value
    reg_write(APIC_lvtthmr, reg_read(APIC_lvtthmr) | APIC_lvt_masked | 0xff);
}

#line 645 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

// give us a hint if we have an APIC but it is disabled

int
Apic::test_present_but_disabled()
{
  if (!good_cpu)
    return 0;

  Unsigned64 msr = Cpu::rdmsr(APIC_base_msr);
  return ((msr & 0xffffff000ULL) == 0xfee00000ULL);
}

#line 657 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

// activate APIC by writing to appropriate MSR
FIASCO_INIT_CPU_AND_PM
void
Apic::activate_by_msr()
{
  Unsigned64 msr;

  msr = Cpu::rdmsr(APIC_base_msr);
  phys_base = msr & 0xfffff000;
  msr |= (1<<11);
  Cpu::wrmsr(msr, APIC_base_msr);

  // now the CPU feature flags may have changed
  cpu().update_features_info();
}

#line 673 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

// check if we still receive interrupts after we changed the IRQ routing
FIASCO_INIT_CPU
int
Apic::check_still_getting_interrupts()
{
  if (!Config::apic)
    return 0;

  Unsigned64 tsc_until;
  Cpu_time clock_start = Kip::k()->clock;

  tsc_until = Cpu::rdtsc();
  tsc_until += 0x01000000; // > 10 Mio cycles should be sufficient until
                           // we have processors with more than 10 GHz
  do
    {
      // kernel clock by timer interrupt updated?
      if (Kip::k()->clock != clock_start)
	// yes, succesful
	return 1;
    } while (Cpu::rdtsc() < tsc_until);

  // timeout
  return 0;
}

#line 706 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


void
Apic::set_perf_nmi()
{
  if (have_pcint())
    reg_write(APIC_lvtpc, 0x400);
}

#line 714 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

FIASCO_INIT_CPU_AND_PM
void
Apic::calibrate_timer()
{
  const unsigned calibrate_time = 50;
  Unsigned32 count, tt1, tt2, result, dummy;
  Unsigned32 runs = 0, frequency_ok;

  do
    {
      frequency_khz = 0;

      timer_disable_irq();
      timer_set_divisor(1);
      timer_reg_write(1000000000);

        {
          auto guard = lock_guard(cpu_lock);

          Pit::setup_channel2_to_20hz();

          count = 0;

          tt1 = timer_reg_read();
          do
            {
              count++;
            }
          while ((Io::in8(0x61) & 0x20) == 0);
          tt2 = timer_reg_read();
        }

      result = (tt1 - tt2) * timer_divisor;

      // APIC not running
      if (count <= 1)
        return;

      asm ("divl %2"
          :"=a" (frequency_khz), "=d" (dummy)
          : "r" (calibrate_time), "a" (result), "d" (0));

      frequency_ok = (frequency_khz < (1000<<11));
    }
  while (++runs < 10 && !frequency_ok);

  if (!frequency_ok)
    panic("APIC frequency too high, adapt Apic::scaler_us_to_apic");

  Kip::k()->frequency_bus = frequency_khz;
  scaler_us_to_apic       = Cpu::muldiv(1<<21, frequency_khz, 1000);
}

#line 767 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


void
Apic::error_interrupt(Return_frame *regs)
{
  Unsigned32 err1, err2;

  // we are entering with disabled interrupts
  err1 = Apic::get_num_errors();
  Apic::clear_num_errors();
  err2 = Apic::get_num_errors();
  Apic::irq_ack();

  cpu_lock.clear();

  if (err1 == 0x80 || err2 == 0x80)
    {
      // ignore possible invalid access which may happen in
      // jdb::do_dump_memory()
      if (ignore_invalid_apic_reg_access)
	return;

      printf("CPU%u: APIC invalid register access error at " L4_PTR_FMT "\n",
	     cxx::int_value<Cpu_number>(current_cpu()), regs->ip());
      return;
    }

  apic_error_cnt++;
  printf("CPU%u: APIC error %08x(%08x)\n",
         cxx::int_value<Cpu_number>(current_cpu()), err1, err2);
}

#line 798 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

// deactivate APIC by writing to appropriate MSR

void
Apic::done()
{
  Unsigned64 val;

  if (!present)
    return;

  val = reg_read(APIC_spiv);
  val &= ~(1<<8);
  reg_write(APIC_spiv, val);

  val = Cpu::rdmsr(APIC_base_msr);
  val  &= ~(1<<11);
  Cpu::wrmsr(val, APIC_base_msr);
}

#line 817 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"

FIASCO_INIT_CPU_AND_PM
void
Apic::init_timer()
{
  calibrate_timer();
  timer_set_divisor(1);
  enable_errors();
}

#line 826 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


void
Apic::dump_info()
{
  if (Config::Warn_level >= 2)
    printf("Local APIC[%02x]: version=%02x max_lvt=%d\n",
           get_id() >> 24, get_version(), get_max_lvt());
}

#line 835 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/apic-ia32.cpp"


void
Apic::init(bool resume)
{
  int was_present;
  // FIXME: reset cached CPU features, we should add a special function
  // for the apic bit
  if(resume)
    cpu().update_features_info();

  was_present = present = test_present();

  if (!was_present)
    {
      good_cpu = test_cpu();

      if (good_cpu && Config::apic)
        {
          // activate; this could lead an disabled APIC to appear
          // set base address of I/O registers to be able to access the registers
          activate_by_msr();
          present = test_present();
        }
    }

  if (!Config::apic)
    return;

  // initialize if available
  if (present)
    {
      // map the Local APIC device registers
      if (!resume)
        map_apic_page();

      // set some interrupt vectors to appropriate values
      init_lvt();

      // initialize APIC_spiv register
      init_spiv();

      // initialize task-priority register
      init_tpr();

      // test if local timer counts down
      if ((present = check_working()))
        {
          if (!was_present)
            // APIC _was_ not present before writing to msr so we have
            // to set APIC_lvt0 and APIC_lvt1 to appropriate values
            route_pic_through_apic();
        }
    }

  if (!present)
    panic("Local APIC not found");

  dump_info();

  apic_io_base = Mem_layout::Local_apic_page;
  init_timer();
}
