// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_thread_list_i_h
#define jdb_thread_list_i_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

#include <climits>
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
#include <cstring>
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
#include <cstdio>
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

#include "jdb.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
#include "jdb_core.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
#include "jdb_module.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
#include "jdb_screen.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
#include "jdb_thread.h"
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
#include "jdb_kobject_names.h"
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
#include "kernel_console.h"
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
#include "keycodes.h"
#line 15 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
#include "minmax.h"
#line 16 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
#include "simpleio.h"
#line 17 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
#include "task.h"
#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
#include "thread.h"
#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
#include "thread_state.h"
#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
#include "static_init.h"
#line 249 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

template<typename T> struct Jdb_thread_list_policy;
#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

class Jdb_thread_list : public Jdb_module
{
public:
  Jdb_thread_list() FIASCO_INIT;
private:
  static char subcmd;
  static char long_output;
  static Cpu_number cpu;

private:
  static int _mode;
  static int _count;
  static char _pr;
  static Thread *_t_head, *_t_start;

  friend class _foo;

  enum { LIST_UNSORTED, LIST_SORT_PRIO, LIST_SORT_TID, LIST_SORT_SPACE,
         LIST_SORT_END };


public:  
#line 61 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  static void
  init(char pr, Thread *t_head);
  
#line 68 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  // return string describing current sorting mode of list
  
  static inline const char*
  get_mode_str(void);
  
#line 79 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  // switch to next sorting mode
  
  static void
  switch_mode(void);
  
#line 88 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  // set _t_start element of list
  
  static void
  set_start(Thread *t_start);
  
#line 98 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  // _t_start-- if possible
  
  static int
  line_back(void);
  
#line 106 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  // _t_start++ if possible
  
  static int
  line_forw(void);
  
#line 117 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  // _t_start -= 24 if possible
  
  static int
  page_back(void);
  
#line 125 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  // _t_start += 24 if possible
  
  static int
  page_forw(void);
  
#line 136 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  // _t_start = first element of list
  
  static int
  goto_home(void);
  
#line 144 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  // _t_start = last element of list
  
  static int
  goto_end(void);
  
#line 155 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  // search index of t_search starting from _t_start
  
  static int
  lookup(Thread *t_search);
  
#line 173 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  // get y'th element of thread list starting from _t_start
  
  static Thread*
  index(int y);
  
#line 531 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  // show complete page using show callback function
  
  static int
  page_show(void (*show)(Thread *t));
  
#line 542 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  // show complete list using show callback function
  
  static int
  complete_show(void (*show)(Thread *t));
  
#line 559 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  Jdb_module::Action_code
  action(int cmd, void *&argbuf, char const *&fmt, int &);
  
#line 855 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  Jdb_module::Cmd const *
  cmds() const;
  
#line 868 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  int
  num_cmds() const;

private:  
#line 184 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  // helper function for iter() -- use priority as sorting key
  
  static long
  get_prio(Thread *t);
  
#line 192 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  // helper function for iter() -- use thread id as sorting key
  
  static long
  get_tid(Thread *t);
  
#line 200 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  // helper function for iter() -- use space as sorting key
  
  static long
  get_space_dbgid(Thread *t);
  
#line 254 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  template<typename RQP> static inline Sched_context *
  sc_fp_iter_prev(Sched_context *t);
  
#line 274 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  template<typename RQP> static inline Sched_context *
  sc_fp_iter_next(Sched_context *t);
  
#line 317 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  static inline Sched_context *
  sc_iter_prev(Sched_context *t);
  
#line 322 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  static inline Sched_context *
  sc_iter_next(Sched_context *t);
  
#line 380 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  static inline Thread*
  iter_prev(Thread *t);
  
#line 401 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  static inline Thread*
  iter_next(Thread *t);
  
#line 420 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  // walk though list <count> times
  // abort walking if no more elements
  // do iter if iter != 0
  
  static bool
  iter(int count, Thread **t_start,
  		      void (*iter)(Thread *t)=0);
  
#line 609 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  static inline void
  print_thread_name(Kobject_common const * o, int len);
  
#line 623 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  static void
  list_threads_show_thread(Thread *t);
  
#line 721 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  static void
  show_header();
  
#line 729 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"
  static void
  list_threads(Thread *t_start, char pr);
};
#line 294 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"

template<>
struct Jdb_thread_list_policy<Ready_queue_fp<Sched_context> >
{
  typedef Ready_queue_fp<Sched_context> Rq;

  static unsigned prio(Sched_context *t)
  { return t->prio(); }

  static Sched_context *prio_next(Sched_context::Ready_queue &rq, unsigned prio)
  { return rq.prio_next[prio].front(); }

  static unsigned prio_highest(Sched_context::Ready_queue &rq)
  { return rq.prio_highest; }

  static Sched_context *prev(Sched_context *t)
  { return *--Rq::List::iter(t); }

  static Sched_context *next(Sched_context *t)
  { return *++Rq::List::iter(t); }
};

//
// IMPLEMENTATION of inline functions follows
//


#line 607 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"


inline void
Jdb_thread_list::print_thread_name(Kobject_common const * o, int len)
{
  Jdb_kobject_name *nx = Jdb_kobject_extension::find_extension<Jdb_kobject_name>(o);

  if (nx)
    {
      len = min((int)nx->max_len(), len);
      printf("%-*.*s", len, len, nx->name());
    }
  else
    printf("%-*.*s", len, len, "-----");
}

//
// IMPLEMENTATION of function templates
//


#line 251 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"



template<typename RQP> inline Sched_context *
Jdb_thread_list::sc_fp_iter_prev(Sched_context *t)
{
  unsigned prio = RQP::prio(t);
  Sched_context::Ready_queue &rq = Sched_context::rq.cpu(cpu);

  if (t != RQP::prio_next(rq, prio))
    return RQP::prev(t);

  for (;;)
    {
      if (++prio > RQP::prio_highest(rq))
	prio = 0;
      if (RQP::prio_next(rq, prio))
	return RQP::prev(RQP::prio_next(rq, prio));
    }
}

#line 271 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_thread_list.cpp"



template<typename RQP> inline Sched_context *
Jdb_thread_list::sc_fp_iter_next(Sched_context *t)
{
  unsigned prio = RQP::prio(t);
  Sched_context::Ready_queue &rq = Sched_context::rq.cpu(cpu);

  if (RQP::next(t) != RQP::prio_next(rq, prio))
    return RQP::next(t);

  for (;;)
    {
      if (--prio > RQP::prio_highest(rq)) // prio is unsigned
	prio = RQP::prio_highest(rq);
      if (RQP::prio_next(rq, prio))
	return RQP::prio_next(rq, prio);
    }
}

#endif // jdb_thread_list_i_h
