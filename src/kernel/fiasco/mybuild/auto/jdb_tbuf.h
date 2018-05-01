// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_tbuf_h
#define jdb_tbuf_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

#include "globalconfig.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
#include "jdb_ktrace.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
#include "l4_types.h"
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
#include "std_macros.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
#include "tb_entry.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
#include "spin_lock.h"

//
// INTERFACE definition follows 
//

#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

class Context;
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
class Log_event;
#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
struct Tracebuffer_status;
#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

class Jdb_tbuf
{
public:
  static void (*direct_log_entry)(Tb_entry*, const char*);

  enum
  {
    Event  = 1,
    Result = 2
  };

  static unsigned char get_entry_status(Tb_log_table_entry const *e);
  static void set_entry_status(Tb_log_table_entry const *e,
                               unsigned char value);

protected:
  static Tb_entry_union *_tbuf_act;	// current entry
  static Tb_entry_union *_tbuf_max;
  static Mword		_entries;	// number of occupied entries
  static Mword		_max_entries;	// maximum number of entries
  static Mword          _filter_enabled;// !=0 if filter is active
  static Mword		_number;	// current event number
  static Mword		_count_mask1;
  static Mword		_count_mask2;
  static Address        _size;		// size of memory area for tbuffer
  static Tracebuffer_status *_status;
  static Tb_entry_union *_buffer;
  static Spin_lock<>    _lock;

public:  
#line 96 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  static inline Tracebuffer_status *status();
  
#line 98 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  static inline Address size();
  
#line 100 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Clear tracebuffer. */
  
  static void
  clear_tbuf();
  
#line 114 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Return pointer to new tracebuffer entry. */
  
  static Tb_entry*
  new_entry();
  
#line 144 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  template<typename T> static inline T*
  new_entry();
  
#line 151 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Commit tracebuffer entry. */
  
  static void
  commit_entry();
  
#line 174 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Return number of entries currently allocated in tracebuffer.
   * @return number of entries */
  
  static inline Mword
  unfiltered_entries();
  
#line 184 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  static Mword
  entries();
  
#line 199 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Return maximum number of entries in tracebuffer.
   * @return number of entries */
  
  static inline Mword
  max_entries();
  
#line 208 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Set maximum number of entries in tracebuffer. */
  
  static inline void
  max_entries (Mword num);
  
#line 216 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Check if event is valid.
   * @param idx position of event in tracebuffer
   * @return 0 if not valid, 1 if valid */
  
  static inline int
  event_valid(Mword idx);
  
#line 226 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Return pointer to tracebuffer event.
   * @param  position of event in tracebuffer:
   *         0 is last event, 1 the event before and so on
   * @return pointer to tracebuffer event
   *
   * event with idx == 0 is the last event queued in
   * event with idx == 1 is the event before */
  
  static Tb_entry*
  unfiltered_lookup(Mword idx);
  
#line 248 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Return pointer to tracebuffer event.
   * Don't count hidden events.
   * @param  position of event in tracebuffer:
   *         0 is last event, 1 the event before and so on
   * @return pointer to tracebuffer event
   *
   * event with idx == 0 is the last event queued in
   * event with idx == 1 is the event before */
  
  static Tb_entry*
  lookup(Mword look_idx);
  
#line 277 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  static Mword
  unfiltered_idx(Tb_entry const *e);
  
#line 289 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Tb_entry => tracebuffer index. */
  
  static Mword
  idx(Tb_entry const *e);
  
#line 314 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Event number => Tb_entry. */
  
  static inline Tb_entry*
  search(Mword nr);
  
#line 328 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Event number => tracebuffer index.
   * @param  nr  number of event
   * @return tracebuffer index of event which has the number nr or
   *         -1 if there is no event with this number or
   *         -2 if the event is currently hidden. */
  
  static Mword
  search_to_idx(Mword nr);
  
#line 362 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Return some information about log event.
   * @param idx number of event to determine the info
   * @retval number event number
   * @retval tsc event value of CPU cycles
   * @retval pmc event value of perf counter cycles
   * @return 0 if something wrong, 1 if everything ok */
  
  static int
  event(Mword idx, Mword *number, Unsigned32 *kclock,
  		Unsigned64 *tsc, Unsigned32 *pmc1, Unsigned32 *pmc2);
  
#line 390 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Get difference CPU cycles between event idx and event idx+1 on the same CPU.
   * @param idx position of first event in tracebuffer
   * @retval difference in CPU cycles
   * @return 0 if something wrong, 1 if everything ok */
  
  static int
  diff_tsc(Mword idx, Signed64 *delta);
  
#line 416 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  /** Get difference perfcnt cycles between event idx and event idx+1.
   * @param idx position of first event in tracebuffer
   * @param nr  number of perfcounter (0=first, 1=second)
   * @retval difference in perfcnt cycles
   * @return 0 if something wrong, 1 if everything ok */
  
  static int
  diff_pmc(Mword idx, Mword nr, Signed32 *delta);
  
#line 441 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  static inline void
  enable_filter();
  
#line 448 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  static inline void
  disable_filter();

protected:  
#line 97 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
  static inline Tb_entry_union *buffer();
};
#line 43 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

#ifdef CONFIG_JDB_LOGGING
#line 45 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"


#define END_LOG_EVENT						\
	}							\
    } while (0)
#line 50 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

#else // ! CONFIG_JDB_LOGGING
#line 52 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

#define BEGIN_LOG_EVENT(name, sc, fmt)				\
  if (0)							\
    { char __do_log__ = 0; (void)__do_log__;
#line 56 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

#define END_LOG_EVENT						\
    }
#line 59 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

#endif // ! CONFIG_JDB_LOGGING
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/32/jdb_tbuf-ia32.cpp"

#define BEGIN_LOG_EVENT(name, sc, fmt)				\
  do								\
    {								\
      Unsigned8 __do_log__;					\
      asm volatile ("1:   movb $0,%0			\n\t"	\
		    ".pushsection \".debug.jdb.log_table\"	\n\t"	\
		    "3:  .long 2f			\n\t"	\
		    "    .long 1b + 1			\n\t"	\
		    "    .long %a[xfmt]			\n\t"	\
		    ".section \".rodata.log.str\"	\n\t"	\
		    "2:  .asciz "#name"			\n\t"	\
		    "    .asciz "#sc"			\n\t"	\
		    ".popsection			\n\t"	\
		    : "=b"(__do_log__)                          \
                    : [xfmt] "i" (&Tb_entry_formatter_t<fmt>::singleton));  \
      if (EXPECT_FALSE( __do_log__ ))				\
	{

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 95 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

inline Tracebuffer_status *Jdb_tbuf::status() { return _status; }

#line 98 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
inline Address Jdb_tbuf::size() { return _size; }

#line 142 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

 
template<typename T> inline T*
Jdb_tbuf::new_entry()
{
  static_assert(sizeof(T) <= sizeof(Tb_entry_union), "tb entry T too big");
  return static_cast<T*>(new_entry());
}

#line 173 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

/** Return number of entries currently allocated in tracebuffer.
 * @return number of entries */

inline Mword
Jdb_tbuf::unfiltered_entries()
{
  return _entries;
}

#line 198 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

/** Return maximum number of entries in tracebuffer.
 * @return number of entries */

inline Mword
Jdb_tbuf::max_entries()
{
  return _max_entries;
}

#line 207 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

/** Set maximum number of entries in tracebuffer. */

inline void
Jdb_tbuf::max_entries (Mword num)
{
  _max_entries = num;
}

#line 215 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

/** Check if event is valid.
 * @param idx position of event in tracebuffer
 * @return 0 if not valid, 1 if valid */

inline int
Jdb_tbuf::event_valid(Mword idx)
{
  return idx < _entries;
}

#line 313 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"

/** Event number => Tb_entry. */

inline Tb_entry*
Jdb_tbuf::search(Mword nr)
{
  Tb_entry *e;

  for (Mword idx = 0; (e = unfiltered_lookup(idx)); idx++)
    if (e->number() == nr)
      return e;

  return 0;
}

#line 439 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"


inline void
Jdb_tbuf::enable_filter()
{
  _filter_enabled = 1;
}

#line 446 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"


inline void
Jdb_tbuf::disable_filter()
{
  _filter_enabled = 0;
}

#line 97 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_tbuf.cpp"
inline Tb_entry_union *Jdb_tbuf::buffer() { return _buffer; }

#endif // jdb_tbuf_h
