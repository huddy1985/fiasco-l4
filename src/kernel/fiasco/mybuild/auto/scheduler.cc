// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "scheduler.h"
#include "scheduler_i.h"

#line 34 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"


JDB_DEFINE_TYPENAME(Scheduler, "\033[34mSched\033[m");
#line 37 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"
Scheduler Scheduler::scheduler;

#line 38 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"

void
Scheduler::operator delete (void *)
{
  printf("WARNING: tried to delete kernel scheduler object.\n"
         "         The system is now useless\n");
}

#line 51 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"



L4_msg_tag
Scheduler::sys_run(L4_fpage::Rights, Syscall_frame *f, Utcb const *utcb)
{
  L4_msg_tag tag = f->tag();
  Cpu_number const curr_cpu = current_cpu();

  if (EXPECT_FALSE(tag.words() < 5))
    return commit_result(-L4_err::EInval);

  unsigned long sz = sizeof (L4_sched_param_legacy);

    {
      L4_sched_param const *sched_param = reinterpret_cast<L4_sched_param const*>(&utcb->values[1]);
      if (sched_param->sched_class < 0)
        sz = sched_param->length;

      sz += sizeof(Mword) - 1;
      sz /= sizeof(Mword);

      if (sz + 1 > tag.words())
	return commit_result(-L4_err::EInval);
    }

  Ko::Rights rights;
  Thread *thread = Ko::deref<Thread>(&tag, utcb, &rights);
  if (!thread)
    return tag;


  Mword _store[sz];
  memcpy(_store, &utcb->values[1], sz * sizeof(Mword));

  L4_sched_param const *sched_param = reinterpret_cast<L4_sched_param const *>(_store);

  Thread::Migration info;

  Cpu_number const t_cpu = thread->home_cpu();

  if (Cpu::online(t_cpu) && sched_param->cpus.contains(t_cpu))
    info.cpu = t_cpu;
  else if (sched_param->cpus.contains(curr_cpu))
    info.cpu = curr_cpu;
  else
    info.cpu = sched_param->cpus.first(Cpu::present_mask(), Config::max_num_cpus());

  info.sp = sched_param;
  if (0)
    printf("CPU[%u]: run(thread=%lx, cpu=%u (%lx,%u,%u)\n",
           cxx::int_value<Cpu_number>(curr_cpu), thread->dbg_id(),
           cxx::int_value<Cpu_number>(info.cpu),
           utcb->values[2],
           cxx::int_value<Cpu_number>(sched_param->cpus.offset()),
           cxx::int_value<Order>(sched_param->cpus.granularity()));

  thread->migrate(&info);

  return commit_result(0);
}

#line 112 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"


L4_msg_tag
Scheduler::op_sched_idle(L4_cpu_set const &cpus, Cpu_time *time)
{
  Cpu_number const cpu = cpus.first(Cpu::online_mask(), Config::max_num_cpus());
  if (EXPECT_FALSE(cpu == Config::max_num_cpus()))
    return commit_result(-L4_err::EInval);

  *time = Context::kernel_context(cpu)->consumed_time();
  return commit_result(0);
}

#line 124 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"


L4_msg_tag
Scheduler::op_sched_info(L4_cpu_set_descr const &s, Mword *m, Mword *max_cpus)
{
  Mword rm = 0;
  Cpu_number max = Config::max_num_cpus();
  Order granularity = s.granularity();
  Cpu_number const offset = s.offset();

  if (offset >= max)
    return commit_result(-L4_err::ERange);

  if (max > offset + Cpu_number(MWORD_BITS) << granularity)
    max = offset + Cpu_number(MWORD_BITS) << granularity;

  for (Cpu_number i = Cpu_number::first(); i < max - offset; ++i)
    if (Cpu::present_mask().get(i + offset))
      rm |= (1 << cxx::int_value<Cpu_number>(i >> granularity));

  *m = rm;
  *max_cpus = Config::Max_num_cpus;
  return commit_result(0);
}

#line 168 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"


L4_msg_tag
Scheduler::op_icu_bind(unsigned irqnum, Ko::Cap<Irq> const &irq)
{
  if (irqnum > 0)
    return commit_result(-L4_err::EInval);

  if (_irq)
    _irq->unbind();

  if (!Ko::check_rights(irq.rights, Ko::Rights::CW()))
    return commit_result(-L4_err::EPerm);

  Irq_chip_soft::bind(irq.obj, irqnum);
  _irq = irq.obj;
  return commit_result(0);
}

#line 186 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"


L4_msg_tag
Scheduler::op_icu_set_mode(Mword pin, Irq_chip::Mode)
{
  if (pin != 0)
    return commit_result(-L4_err::EInval);

  if (_irq)
    _irq->switch_mode(true);
  return commit_result(0);
}

#line 206 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/scheduler.cpp"


L4_msg_tag
Scheduler::kinvoke(L4_obj_ref ref, L4_fpage::Rights rights, Syscall_frame *f,
                   Utcb const *iutcb, Utcb *outcb)
{
  switch (f->tag().proto())
    {
    case L4_msg_tag::Label_irq:
      return Icu::icu_invoke(ref, rights, f, iutcb,outcb);
    case L4_msg_tag::Label_scheduler:
      break;
    default:
      return commit_result(-L4_err::EBadproto);
    }

  switch (iutcb->values[0])
    {
    case Info:       return Msg_sched_info::call(this, f->tag(), iutcb, outcb);
    case Run_thread: return sys_run(rights, f, iutcb);
    case Idle_time:  return Msg_sched_idle::call(this, f->tag(), iutcb, outcb);
    default:         return commit_result(-L4_err::ENosys);
    }
}
