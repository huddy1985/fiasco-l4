// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef task_h
#define task_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"

#include "context.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
#include "kobject.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
#include "l4_types.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
#include "rcupdate.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
#include "space.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
#include "spin_lock.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
#include "unique_ptr.h"
#line 617 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"

#include "tb_entry.h"

//
// INTERFACE definition follows 
//

#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"

/**
 * \brief A task is a protection domain.
 *
 * A is derived from Space, which aggregates a set of address spaces.
 * Additionally to a space, a task provides initialization and
 * destruction functionality for a protection domain.
 * Task is also derived from Rcu_item to provide RCU shutdown of tasks.
 */
class Task :
  public cxx::Dyn_castable<Task, Kobject>,
  public Space
{
  friend class Jdb_space;

private:
  /// \brief Do host (platform) specific initialization.
  void ux_init();

public:
  enum Operation
  {
    Map         = 0,
    Unmap       = 1,
    Cap_info    = 2,
    Add_ku_mem  = 3,
    Ldt_set_x86 = 0x11,
  };

  virtual int resume_vcpu(Context *ctxt, Vcpu_state *vcpu, bool user_mode);

private:
  /// map the global utcb pointer page into this task
  void map_utcb_ptr_page();

#line 619 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
private:

private:
  struct Log_unmap : public Tb_entry
  {
    Mword id;
    Mword mask;
    Mword fpage;
    void print(String_buffer *buf) const;
  };


public:  
#line 97 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
  virtual bool
  put();
  
#line 165 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
  int
  alloc_ku_mem(L4_fpage ku_area);
  
#line 238 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
  /** Allocate space for the UTCBs of all threads in this task.
   *  @ return true on success, false if not enough memory for the UTCBs
   */
  
  bool
  initialize();
  
#line 256 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
  /**
   * \brief Create a normal Task.
   * \pre \a parent must be valid and exist.
   */
  
  explicit Task(Ram_quota *q, Caps c);
  
#line 270 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
  explicit Task(Ram_quota *q);
  
#line 295 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
  //inline
  void
  operator delete (void *ptr);
  
#line 310 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
  template<typename TASK_TYPE, bool MUST_SYNC_KERNEL = true,
                  int UTCB_AREA_MR = 0> static TASK_TYPE * FIASCO_FLATTEN
  create(Ram_quota *q,
               L4_msg_tag t, Utcb const *u,
               int *err);
  
#line 355 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
  template<typename TASK_TYPE, bool MUST_SYNC_KERNEL = false,
                  int UTCB_AREA_MR = 0> static Kobject_iface * FIASCO_FLATTEN
  generic_factory(Ram_quota *q, Space *,
                        L4_msg_tag t, Utcb const *u,
                        int *err);
  
#line 364 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
  /**
   * \brief Shutdown the task.
   *
   * Currently:
   * -# Unbind and delete all contexts bound to this task.
   * -# Unmap everything from all spaces.
   * -# Delete child tasks.
   */
  
  void
  destroy(Kobject ***reap_list);
  
#line 562 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
  void
  invoke(L4_obj_ref, L4_fpage::Rights rights, Syscall_frame *f, Utcb *utcb);
  
#line 611 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
  inline ~Task();

protected:  
#line 280 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
  Task(Ram_quota *q, Mem_space::Dir_type* pdir, Caps c);
  
#line 291 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
  static Slab_cache*
  allocator();

private:  
#line 102 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
  int
  alloc_ku_mem_chunk(User<void>::Ptr u_addr, unsigned size, void **k_addr);
  
#line 197 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
  inline void
  free_ku_mem(Ku_mem *m);
  
#line 205 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
  void
  free_ku_mem_chunk(void *k_addr, User<void>::Ptr u_addr, unsigned size,
                          unsigned mapped_size);
  
#line 230 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
  void
  free_ku_mem();
  
#line 382 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
  inline L4_msg_tag
  sys_map(L4_fpage::Rights rights, Syscall_frame *f, Utcb *utcb);
  
#line 446 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
  inline L4_msg_tag
  sys_unmap(Syscall_frame *f, Utcb *utcb);
  
#line 488 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
  inline L4_msg_tag
  sys_cap_valid(Syscall_frame *, Utcb *utcb);
  
#line 509 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
  inline L4_msg_tag
  sys_caps_equal(Syscall_frame *, Utcb *utcb);
  
#line 528 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
  inline L4_msg_tag
  sys_add_ku_mem(Syscall_frame *f, Utcb *utcb);
  
#line 547 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
  inline L4_msg_tag
  sys_cap_info(Syscall_frame *f, Utcb *utcb);
  
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/task-ia32-amd64.cpp"
  inline bool
  invoke_arch(L4_msg_tag, Utcb *);
};
#line 45 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"


//---------------------------------------------------------------------------

#line 632 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"

// ---------------------------------------------------------------------------

#line 637 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"

//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 49 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"

#include "atomic.h"
#line 51 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
#include "config.h"
#line 52 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
#include "entry_frame.h"
#line 53 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
#include "globals.h"
#line 54 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
#include "kdb_ke.h"
#line 55 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
#include "kmem.h"
#line 56 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
#include "kmem_slab.h"
#line 57 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
#include "kobject_rpc.h"
#line 58 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
#include "l4_types.h"
#line 59 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
#include "logdefs.h"
#line 60 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
#include "map_util.h"
#line 61 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
#include "mem_layout.h"
#line 62 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
#include "ram_quota.h"
#line 63 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
#include "thread_state.h"
#line 64 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
#include "paging.h"
#line 635 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"

#include "string_buffer.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 609 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"


inline Task::~Task()
{ free_ku_mem(); }

#line 606 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"

inline void Task::map_utcb_ptr_page() {}

#line 608 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"
inline void Task::ux_init() {}

//
// IMPLEMENTATION of function templates
//


#line 308 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"

 
template<typename TASK_TYPE, bool MUST_SYNC_KERNEL,
                int UTCB_AREA_MR> TASK_TYPE * FIASCO_FLATTEN
Task::create(Ram_quota *q,
             L4_msg_tag t, Utcb const *u,
             int *err)
{
  static_assert(UTCB_AREA_MR == 0 || UTCB_AREA_MR >= 2,
                "invalid value for UTCB_AREA_MR");
  if (UTCB_AREA_MR >= 2 && EXPECT_FALSE(t.words() <= UTCB_AREA_MR))
    {
      *err = L4_err::EInval;
      return 0;
    }

  typedef Kmem_slab_t<TASK_TYPE> Alloc;
  *err = L4_err::ENomem;
  cxx::unique_ptr<TASK_TYPE> v(Alloc::q_new(q, q));

  if (EXPECT_FALSE(!v))
    return 0;

  if (EXPECT_FALSE(!v->initialize()))
    return 0;

  if (MUST_SYNC_KERNEL && (v->sync_kernel() < 0))
    return 0;

  if (UTCB_AREA_MR >= 2)
    {
      L4_fpage utcb_area(access_once(&u->values[UTCB_AREA_MR]));
      if (utcb_area.is_valid())
        {
          int e = v->alloc_ku_mem(utcb_area);
          if (e < 0)
            {
              *err = -e;
              return 0;
            }
        }
    }

  return v.release();
}

#line 353 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/task.cpp"

 
template<typename TASK_TYPE, bool MUST_SYNC_KERNEL,
                int UTCB_AREA_MR> Kobject_iface * FIASCO_FLATTEN
Task::generic_factory(Ram_quota *q, Space *,
                      L4_msg_tag t, Utcb const *u,
                      int *err)
{
  return create<TASK_TYPE, MUST_SYNC_KERNEL, UTCB_AREA_MR>(q, t, u, err);
}

#endif // task_h
