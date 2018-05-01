// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "task.h"
#include "task_i.h"

#line 65 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"

JDB_DEFINE_TYPENAME(Task, "\033[31mTask\033[m");
#line 67 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
static Kmem_slab_t<Task::Ku_mem> _k_u_mem_list_alloc("Ku_mem");
#line 68 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
Slab_cache *Space::Ku_mem::a = _k_u_mem_list_alloc.slab();
#line 69 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"

extern "C" void vcpu_resume(Trap_state *, Return_frame *sp)
   FIASCO_FASTCALL FIASCO_NORETURN;
#line 286 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"

// The allocator for tasks
static Kmem_slab_t<Task> _task_allocator("Task");
#line 594 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"

namespace {
static inline void __attribute__((constructor)) FIASCO_INIT
register_factory()
{
  Kobject_iface::set_factory(L4_msg_tag::Label_task,
                             &Task::generic_factory<Task, true, 2>);
}
}
#line 603 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"

//---------------------------------------------------------------------------

#line 613 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"


// ---------------------------------------------------------------------------


#line 195 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"


inline void
Task::free_ku_mem(Ku_mem *m)
{
  free_ku_mem_chunk(m->k_addr, m->u_addr, m->size, m->size);
  m->free(ram_quota());
}

#line 380 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"


inline L4_msg_tag
Task::sys_map(L4_fpage::Rights rights, Syscall_frame *f, Utcb *utcb)
{
  LOG_TRACE("Task map", "map", ::current(), Log_unmap,
      l->id = dbg_id();
      l->mask  = utcb->values[1];
      l->fpage = utcb->values[2]);

  if (EXPECT_FALSE(!(rights & L4_fpage::Rights::CW())))
    return commit_result(-L4_err::EPerm);

  L4_msg_tag tag = f->tag();

  L4_fpage::Rights mask;
  Task *_from = Ko::deref<Task>(&tag, utcb, &mask);
  if (!_from)
    return tag;

  L4_fpage sfp(utcb->values[2]);

  if (sfp.type() == L4_fpage::Obj)
    {
      // handle Rights::CS() bit masking for capabilities
      mask &= rights;
      mask |= L4_fpage::Rights::CD() | L4_fpage::Rights::CRW();

      // diminish when sending via restricted ipc gates
      sfp.mask_rights(mask);
    }

  Kobject::Reap_list rl;
  L4_error ret;

    {
      Ref_ptr<Task> from(_from);
      Ref_ptr<Task> self(this);
      // enforce lock order to prevent deadlocks.
      // always take lock from task with the lower memory address first
      Lock_guard_2<Lock> guard;

      // FIXME: avoid locking the current task, it is not needed
      if (!guard.check_and_lock(&existence_lock, &from->existence_lock))
        return commit_result(-L4_err::EInval);

      cpu_lock.clear();

      ret = fpage_map(from.get(), sfp, this,
                      L4_fpage::all_spaces(), L4_msg_item(utcb->values[1]), &rl);
      cpu_lock.lock();
    }

  cpu_lock.clear();
  rl.del();
  cpu_lock.lock();

  // FIXME: treat reaped stuff
  if (ret.ok())
    return commit_result(0);
  else
    return commit_error(utcb, ret);
}

#line 443 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"



inline L4_msg_tag
Task::sys_unmap(Syscall_frame *f, Utcb *utcb)
{
  Kobject::Reap_list rl;
  unsigned words = f->tag().words();

  LOG_TRACE("Task unmap", "unm", ::current(), Log_unmap,
            l->id = dbg_id();
            l->mask  = utcb->values[1];
            l->fpage = utcb->values[2]);

    {
      Ref_ptr<Task> self(this);
      Lock_guard<Lock> guard;

      // FIXME: avoid locking the current task, it is not needed
      if (!guard.check_and_lock(&existence_lock))
        return commit_error(utcb, L4_error::Not_existent);

      cpu_lock.clear();

      L4_map_mask m(utcb->values[1]);

      for (unsigned i = 2; i < words; ++i)
        {
          L4_fpage::Rights const flushed
            = fpage_unmap(this, L4_fpage(utcb->values[i]), m, rl.list());

          utcb->values[i] = (utcb->values[i] & ~0xfUL)
                          | cxx::int_value<L4_fpage::Rights>(flushed);
        }
      cpu_lock.lock();
    }

  cpu_lock.clear();
  rl.del();
  cpu_lock.lock();

  return commit_result(0, words);
}

#line 486 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"


inline L4_msg_tag
Task::sys_cap_valid(Syscall_frame *, Utcb *utcb)
{
  L4_obj_ref obj(utcb->values[1]);

  if (obj.special())
    return commit_result(0);

  Obj_space::Capability cap = lookup(obj.cap());
  if (EXPECT_TRUE(cap.valid()))
    {
      if (!(utcb->values[1] & 1))
        return commit_result(1);
      else
        return commit_result(cap.obj()->map_root()->cap_ref_cnt());
    }
  else
    return commit_result(0);
}

#line 507 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"


inline L4_msg_tag
Task::sys_caps_equal(Syscall_frame *, Utcb *utcb)
{
  L4_obj_ref obj_a(utcb->values[1]);
  L4_obj_ref obj_b(utcb->values[2]);

  if (obj_a == obj_b)
    return commit_result(1);

  if (obj_a.special() || obj_b.special())
    return commit_result(obj_a.special_cap() == obj_b.special_cap());

  Obj_space::Capability c_a = lookup(obj_a.cap());
  Obj_space::Capability c_b = lookup(obj_b.cap());

  return commit_result(c_a == c_b);
}

#line 526 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"


inline L4_msg_tag
Task::sys_add_ku_mem(Syscall_frame *f, Utcb *utcb)
{
  unsigned const w = f->tag().words();
  for (unsigned i = 1; i < w; ++i)
    {
      L4_fpage ku_fp(utcb->values[i]);
      if (!ku_fp.is_valid() || !ku_fp.is_mempage())
        return commit_result(-L4_err::EInval);

      int e = alloc_ku_mem(ku_fp);
      if (e < 0)
        return commit_result(e);
    }

  return commit_result(0);
}

#line 545 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"


inline L4_msg_tag
Task::sys_cap_info(Syscall_frame *f, Utcb *utcb)
{
  L4_msg_tag const &tag = f->tag();

  switch (tag.words())
    {
    default: return commit_result(-L4_err::EInval);
    case 2:  return sys_cap_valid(f, utcb);
    case 3:  return sys_caps_equal(f, utcb);
    }
}

#line 72 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"


int
Task::resume_vcpu(Context *ctxt, Vcpu_state *vcpu, bool user_mode)
{
  Trap_state ts;
  ctxt->copy_and_sanitize_trap_state(&ts, &vcpu->_regs.s);

  // FIXME: UX is currently broken
  /* UX:ctxt->vcpu_resume_user_arch(); */
  if (user_mode)
    {
      ctxt->state_add_dirty(Thread_vcpu_user);
      vcpu->state |= Vcpu_state::F_traps | Vcpu_state::F_exceptions
                     | Vcpu_state::F_debug_exc;

      ctxt->vcpu_pv_switch_to_user(vcpu, true);
    }

  ctxt->space_ref()->user_mode(user_mode);
  switchin_context(ctxt->space());
  vcpu_resume(&ts, ctxt->regs());
}

#line 95 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"


bool
Task::put()
{ return dec_ref() == 0; }

#line 100 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"


int
Task::alloc_ku_mem_chunk(User<void>::Ptr u_addr, unsigned size, void **k_addr)
{
  assert ((size & (size - 1)) == 0);

  Kmem_alloc *const alloc = Kmem_alloc::allocator();
  void *p = alloc->q_unaligned_alloc(ram_quota(), size);

  if (EXPECT_FALSE(!p))
    return -L4_err::ENomem;

  // clean up utcbs
  memset(p, 0, size);

  Virt_addr base((Address)p);
  Mem_space::Page_order page_size(Config::PAGE_SHIFT);

  // the following works because the size is a power of two
  // and once we have size larger than a super page we have
  // always multiples of superpages
  if (size >= Config::SUPERPAGE_SIZE)
    page_size = Mem_space::Page_order(Config::SUPERPAGE_SHIFT);

  for (Virt_size i = Virt_size(0); i < Virt_size(size);
       i += Virt_size(1) << page_size)
    {
      Virt_addr kern_va = base + i;
      Virt_addr user_va = Virt_addr((Address)u_addr.get()) + i;
      Mem_space::Phys_addr pa(pmem_to_phys(Virt_addr::val(kern_va)));

      // must be valid physical address
      assert(pa != Mem_space::Phys_addr(~0UL));

      Mem_space::Status res =
        static_cast<Mem_space*>(this)->v_insert(pa, user_va, page_size,
            Mem_space::Attr(L4_fpage::Rights::URW()));

      switch (res)
        {
        case Mem_space::Insert_ok: break;
        case Mem_space::Insert_err_nomem:
          free_ku_mem_chunk(p, u_addr, size, Virt_size::val(i));
          return -L4_err::ENomem;

        case Mem_space::Insert_err_exists:
          free_ku_mem_chunk(p, u_addr, size, Virt_size::val(i));
          return -L4_err::EExists;

        default:
          printf("UTCB mapping failed: va=%p, ph=%p, res=%d\n",
              (void*)Virt_addr::val(user_va), (void*)Virt_addr::val(kern_va), res);
          kdb_ke("BUG in utcb allocation");
          free_ku_mem_chunk(p, u_addr, size, Virt_size::val(i));
          return 0;
        }
    }

  *k_addr = p;
  return 0;
}

#line 162 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"



int
Task::alloc_ku_mem(L4_fpage ku_area)
{
  if (ku_area.order() < Config::PAGE_SHIFT || ku_area.order() > 20)
    return -L4_err::EInval;

  Mword sz = 1UL << ku_area.order();

  Ku_mem *m = new (ram_quota()) Ku_mem();

  if (!m)
    return -L4_err::ENomem;

  User<void>::Ptr u_addr((void*)Virt_addr::val(ku_area.mem_address()));

  void *p = 0;
  if (int e = alloc_ku_mem_chunk(u_addr, sz, &p))
    {
      m->free(ram_quota());
      return e;
    }

  m->u_addr = u_addr;
  m->k_addr = p;
  m->size = sz;

  _ku_mem.add(m, mp_cas<cxx::S_list_item*>);

  return 0;
}

#line 203 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"


void
Task::free_ku_mem_chunk(void *k_addr, User<void>::Ptr u_addr, unsigned size,
                        unsigned mapped_size)
{

  Kmem_alloc * const alloc = Kmem_alloc::allocator();
  Mem_space::Page_order page_size(Config::PAGE_SHIFT);

  // the following works because the size is a power of two
  // and once we have size larger than a super page we have
  // always multiples of superpages
  if (size >= Config::SUPERPAGE_SIZE)
    page_size = Mem_space::Page_order(Config::SUPERPAGE_SHIFT);

  for (Virt_size i = Virt_size(0); i < Virt_size(mapped_size);
       i += Virt_size(1) << page_size)
    {
      Virt_addr user_va = Virt_addr((Address)u_addr.get()) + i;
      static_cast<Mem_space*>(this)->v_delete(user_va, page_size, L4_fpage::Rights::FULL());
    }

  alloc->q_unaligned_free(ram_quota(), size, k_addr);
}

#line 228 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"


void
Task::free_ku_mem()
{
  while (Ku_mem *m = _ku_mem.pop_front())
    free_ku_mem(m);
}

#line 236 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"


/** Allocate space for the UTCBs of all threads in this task.
 *  @ return true on success, false if not enough memory for the UTCBs
 */

bool
Task::initialize()
{
  if (!Mem_space::initialize())
    return false;

  // For UX, map the UTCB pointer page. For ia32, do nothing
  map_utcb_ptr_page();

  CNT_TASK_CREATE;

  return true;
}

#line 255 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"

/**
 * \brief Create a normal Task.
 * \pre \a parent must be valid and exist.
 */

Task::Task(Ram_quota *q, Caps c) : Space(q, c)
{
  ux_init();

  // increment reference counter from zero
  inc_ref(true);
}

#line 268 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"


Task::Task(Ram_quota *q)
: Space(q, Caps::mem() | Caps::io() | Caps::obj() | Caps::threads())
{
  ux_init();

  // increment reference counter from zero
  inc_ref(true);
}

#line 278 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"


Task::Task(Ram_quota *q, Mem_space::Dir_type* pdir, Caps c)
: Space(q, pdir, c)
{
  // increment reference counter from zero
  inc_ref(true);
}

#line 289 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"


Slab_cache*
Task::allocator()
{ return _task_allocator.slab(); }

#line 294 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"

//inline
void
Task::operator delete (void *ptr)
{
  Task *t = reinterpret_cast<Task*>(ptr);
  LOG_TRACE("Kobject delete", "del", current(), Log_destroy,
            l->id = t->dbg_id();
            l->obj = t;
            l->type = cxx::Typeid<Task>::get();
            l->ram = t->ram_quota()->current());

  Kmem_slab_t<Task>::q_free(t->ram_quota(), ptr);
}

#line 363 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"

/**
 * \brief Shutdown the task.
 *
 * Currently:
 * -# Unbind and delete all contexts bound to this task.
 * -# Unmap everything from all spaces.
 * -# Delete child tasks.
 */

void
Task::destroy(Kobject ***reap_list)
{
  Kobject::destroy(reap_list);

  fpage_unmap(this, L4_fpage::all_spaces(L4_fpage::Rights::FULL()), L4_map_mask::full(), reap_list);
}

#line 559 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"



void
Task::invoke(L4_obj_ref, L4_fpage::Rights rights, Syscall_frame *f, Utcb *utcb)
{
  if (EXPECT_FALSE(f->tag().proto() != L4_msg_tag::Label_task))
    {
      f->tag(commit_result(-L4_err::EBadproto));
      return;
    }

  switch (utcb->values[0])
    {
    case Map:
      f->tag(sys_map(rights, f, utcb));
      return;
    case Unmap:
      f->tag(sys_unmap(f, utcb));
      return;
    case Cap_info:
      f->tag(sys_cap_info(f, utcb));
      return;
    case Add_ku_mem:
      f->tag(sys_add_ku_mem(f, utcb));
      return;
    default:
      L4_msg_tag tag = f->tag();
      if (invoke_arch(tag, utcb))
        f->tag(tag);
      else
        f->tag(commit_result(-L4_err::ENosys));
      return;
    }
}

#line 637 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"


void
Task::Log_unmap::print(String_buffer *buf) const
{
  L4_fpage fp(fpage);
  buf->printf("task=[U:%lx] mask=%lx fpage=[%u/%u]%lx",
              id, mask, (unsigned)fp.order(), (unsigned)fp.type(), fpage);
}
