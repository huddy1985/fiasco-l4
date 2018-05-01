// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef mem_space_h
#define mem_space_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"

#include "auto_quota.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
#include "cpu_mask.h"
#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
#include "paging.h"		// for page attributes
#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
#include "mem_layout.h"
#line 7 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
#include "member_offs.h"
#line 8 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
#include "per_cpu_data.h"
#line 9 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
#include "ram_quota.h"
#line 10 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
#include "types.h"
#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
#include "mapdb_types.h"

//
// INTERFACE definition follows 
//

#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"

class Space;
#line 14 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"

/**
 * An address space.
 *
 * Insertion and lookup functions.
 */
class Mem_space
{
  MEMBER_OFFSET();

  // Space reverse lookup
  friend inline Mem_space* current_mem_space();

public:
  typedef int Status;
  static char const *const name;

  typedef Page::Attr Attr;
  typedef Pdir::Va Vaddr;
  typedef Pdir::Vs Vsize;

  typedef Addr::Addr<Config::PAGE_SHIFT> Phys_addr;
  typedef Addr::Diff<Config::PAGE_SHIFT> Phys_diff;
  typedef Addr::Order<Config::PAGE_SHIFT> Page_order;

  typedef void Reap_list;

  // for map_util
  typedef Page_number V_pfn;
  typedef Page_count V_pfc;
  typedef Addr::Order<0> V_order;

  // Each architecture must provide these members:
  void switchin_context(Mem_space *from);

  FIASCO_SPACE_VIRTUAL
  void tlb_flush(bool);

  /** Insert a page-table entry, or upgrade an existing entry with new
   *  attributes.
   *
   * @param phys Physical address (page-aligned).
   * @param virt Virtual address for which an entry should be created.
   * @param size Size of the page frame -- 4KB or 4MB.
   * @param page_attribs Attributes for the mapping (see
   *                     Mem_space::Page_attrib).
   * @return Insert_ok if a new mapping was created;
   *         Insert_warn_exists if the mapping already exists;
   *         Insert_warn_attrib_upgrade if the mapping already existed but
   *                                    attributes could be upgraded;
   *         Insert_err_nomem if the mapping could not be inserted because
   *                          the kernel is out of memory;
   *         Insert_err_exists if the mapping could not be inserted because
   *                           another mapping occupies the virtual-address
   *                           range
   * @pre phys and virt need to be size-aligned according to the size argument.
   */
  FIASCO_SPACE_VIRTUAL
  Status v_insert(Phys_addr phys, Vaddr virt, Page_order size,
                  Attr page_attribs);

  /** Look up a page-table entry.
   *
   * @param virt Virtual address for which we try the look up.
   * @param phys Meaningful only if we find something (and return true).
   *             If not 0, we fill in the physical address of the found page
   *             frame.
   * @param page_attribs Meaningful only if we find something (and return
   *             true). If not 0, we fill in the page attributes for the
   *             found page frame (see Mem_space::Page_attrib).
   * @param size If not 0, we fill in the size of the page-table slot.  If an
   *             entry was found (and we return true), this is the size
   *             of the page frame.  If no entry was found (and we
   *             return false), this is the size of the free slot.  In
   *             either case, it is either 4KB or 4MB.
   * @return True if an entry was found, false otherwise.
   */
  FIASCO_SPACE_VIRTUAL
  bool v_lookup(Vaddr virt, Phys_addr *phys = 0, Page_order *order = 0,
                Attr *page_attribs = 0);

  /** Delete page-table entries, or some of the entries' attributes.
   *
   * This function works for one or multiple mappings (in contrast to
   * v_insert!).
   *
   * @param virt Virtual address of the memory region that should be changed.
   * @param size Size of the memory region that should be changed.
   * @param page_attribs If nonzero, delete only the given page attributes.
   *                     Otherwise, delete the whole entries.
   * @return Combined (bit-ORed) page attributes that were removed.  In
   *         case of errors, ~Page_all_attribs is additionally bit-ORed in.
   */
  FIASCO_SPACE_VIRTUAL
  L4_fpage::Rights v_delete(Vaddr virt, Page_order size,
                            L4_fpage::Rights page_attribs);

  FIASCO_SPACE_VIRTUAL
  void v_set_access_flags(Vaddr virt, L4_fpage::Rights access_flags);

  /** Set this memory space as the current on this CPU. */
  void make_current();

  static Mem_space *kernel_space()
  { return _kernel_space; }

  static inline Mem_space *current_mem_space(Cpu_number cpu);


  virtual
  Page_number mem_space_map_max_address() const
  { return Page_number(Virt_addr(Mem_layout::User_max)) + Page_count(1); }

  Page_number map_max_address() const
  { return mem_space_map_max_address(); }

  static Phys_addr page_address(Phys_addr o, Page_order s)
  { return cxx::mask_lsb(o, s); }

  static V_pfn page_address(V_pfn a, Page_order o)
  { return cxx::mask_lsb(a, o); }

  static Phys_addr subpage_address(Phys_addr addr, V_pfc offset)
  { return addr | Phys_diff(offset); }

  struct Fit_size
  {
    typedef cxx::array<Page_order, Page_order, 65> Size_array;
    Size_array const &o;
    Page_order operator () (Page_order i) const { return o[i]; }

    explicit Fit_size(Size_array const &o) :o(o) {}
  };

  FIASCO_SPACE_VIRTUAL
  Fit_size mem_space_fitting_sizes() const __attribute__((pure));

  Fit_size fitting_sizes() const
  { return mem_space_fitting_sizes(); }

  static Mdb_types::Pfn to_pfn(Phys_addr p)
  { return Mdb_types::Pfn(cxx::int_value<Page_number>(p)); }

  static Mdb_types::Pfn to_pfn(V_pfn p)
  { return Mdb_types::Pfn(cxx::int_value<Page_number>(p)); }

  static Mdb_types::Pcnt to_pcnt(Page_order s)
  { return Mdb_types::Pcnt(1) << Mdb_types::Order(cxx::int_value<Page_order>(s) - Config::PAGE_SHIFT); }

  static V_pfn to_virt(Mdb_types::Pfn p)
  { return Page_number(cxx::int_value<Mdb_types::Pfn>(p)); }

  static Page_order to_order(Mdb_types::Order p)
  { return Page_order(cxx::int_value<Mdb_types::Order>(p) + Config::PAGE_SHIFT); }

  static V_pfc to_size(Page_order p)
  { return V_pfc(1) << p; }

  static V_pfc subpage_offset(V_pfn a, Page_order o)
  { return cxx::get_lsb(a, o); }

  Page_order largest_page_size() const
  { return mem_space_fitting_sizes()(Page_order(64)); }

  enum
  {
    Max_num_global_page_sizes = 5
  };

  static Page_order const *get_global_page_sizes(bool finalize = true)
  {
    if (finalize)
      _glbl_page_sizes_finished = true;
    return _glbl_page_sizes;
  }

private:
  Mem_space(const Mem_space &) = delete;

  Ram_quota *_quota;

  static Per_cpu<Mem_space *> _current;
  static Mem_space *_kernel_space;
  static Page_order _glbl_page_sizes[Max_num_global_page_sizes];
  static unsigned _num_glbl_page_sizes;
  static bool _glbl_page_sizes_finished;

#line 219 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
private:

public:
  enum { Need_xcpu_tlb_flush = false };

#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space-user.cpp"
private:

public:
  /**
   * Read integral type at any virtual address.
   * @param addr Virtual address in user or kernel address space.
   * @param user_space Location of virtual address (user or kernel space).
   * @return Integral value read from address.
   */
  template< typename T >
  T peek(T const *addr, bool user_space);

  /**
   * Read integral type at virtual address in user space.
   * @param addr Virtual address in user address space.
   * @return Integral value read from address.
   */
  template< typename T >
  T peek_user(T const *addr);

  /**
   * Set integral type at virtual address in user space to value.
   * @param addr Virtual address in user address space.
   * @param value New value to be set.
   */
  template< typename T >
  void poke_user(T *addr, T value);

#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
private:

public:
  typedef Pdir Dir_type;

  /** Return status of v_insert. */
  enum // Status
  {
    Insert_ok = 0,		///< Mapping was added successfully.
    Insert_warn_exists,		///< Mapping already existed
    Insert_warn_attrib_upgrade,	///< Mapping already existed, attribs upgrade
    Insert_err_nomem,		///< Couldn't alloc new page table
    Insert_err_exists		///< A mapping already exists at the target addr
  };

  /** Attribute masks for page mappings. */
  enum Page_attrib
  {
    Page_no_attribs = 0,
    /// Page is writable.
    Page_writable = Pt_entry::Writable,
    Page_cacheable = 0,
    /// Page is noncacheable.
    Page_noncacheable = Pt_entry::Noncacheable | Pt_entry::Write_through,
    /// it's a user page.
    Page_user_accessible = Pt_entry::User,
    /// Page has been referenced
    Page_referenced = Pt_entry::Referenced,
    /// Page is dirty
    Page_dirty = Pt_entry::Dirty,
    Page_references = Page_referenced | Page_dirty,
    /// A mask which contains all mask bits
    Page_all_attribs = Page_writable | Page_noncacheable |
                       Page_user_accessible | Page_referenced | Page_dirty,
  };

  // Mapping utilities

  enum				// Definitions for map_util
  {
    Need_insert_tlb_flush = 0,
    Map_page_size = Config::PAGE_SIZE,
    Page_shift = Config::PAGE_SHIFT,
    Whole_space = MWORD_BITS,
    Identity_map = 0,
  };


  void	page_map	(Address phys, Address virt,
                         Address size, Attr);

  void	page_unmap	(Address virt, Address size);

  void	page_protect	(Address virt, Address size,
                         unsigned page_attribs);

protected:
  // DATA
  Dir_type *_dir;

public:  
#line 280 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
  static void
  add_page_size(Page_order o);
  
#line 296 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
  inline Ram_quota *
  ram_quota() const;
  
#line 301 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
  /// Avoid deallocation of page table upon Mem_space destruction.
  
  void
  reset_dirty ();
  
#line 308 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
  inline Mem_space::Dir_type*
  dir ();
  
#line 313 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
  inline const Mem_space::Dir_type*
  dir() const;
  
#line 318 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
  virtual bool
  v_fabricate(Vaddr address, Phys_addr *phys, Page_order *order,
                         Attr *attribs = 0);
  
#line 327 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
  virtual bool
  is_sigma0() const;
  
#line 348 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
  static inline void
  enable_tlb(Cpu_number);
  
#line 353 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
  static inline void
  disable_tlb(Cpu_number);
  
#line 358 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
  static inline Cpu_mask
  active_tlb();
  
#line 79 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  explicit inline Mem_space(Ram_quota *q);
  
#line 96 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  Mem_space(Ram_quota *q, Dir_type* pdir);
  
#line 104 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  static inline bool
  is_full_flush(L4_fpage::Rights rights);
  
#line 111 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  static inline bool
  has_superpages();
  
#line 135 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  inline bool
  set_attributes(Virt_addr virt, Attr page_attribs);
  
#line 227 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  /**
   * Simple page-table lookup.
   *
   * @param virt Virtual address.  This address does not need to be page-aligned.
   * @return Physical address corresponding to a.
   */
  
  inline Address
  virt_to_phys(Address virt) const;
  
#line 240 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  /**
   * Simple page-table lookup.
   *
   * @param virt Virtual address.  This address does not need to be page-aligned.
   * @return Physical address corresponding to a.
   */
  
  inline Address
  pmem_to_phys(Address virt) const;
  
#line 253 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  /**
   * Simple page-table lookup.
   *
   * This method is similar to Space_context's virt_to_phys().
   * The difference is that this version handles Sigma0's
   * address space with a special case:  For Sigma0, we do not
   * actually consult the page table -- it is meaningless because we
   * create new mappings for Sigma0 transparently; instead, we return the
   * logically-correct result of physical address == virtual address.
   *
   * @param a Virtual address.  This address does not need to be page-aligned.
   * @return Physical address corresponding to a.
   */
  
  virtual inline Address
  virt_to_phys_s0(void *a) const;
  
#line 342 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  /**
   * \brief Free all memory allocated for this Mem_space.
   * \pre Runs after the destructor!
   */
  
  ~Mem_space();
  
#line 374 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  inline Address
  phys_dir();
  
#line 527 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  static inline Page_number
  canonize(Page_number v);
  
#line 532 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  static void
  init_page_sizes();

protected:  
#line 254 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"
  static void
  add_global_page_size(Page_order o);
  
#line 82 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  inline bool
  initialize();
  
#line 149 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  inline void
  destroy();
  
#line 435 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  inline int
  sync_kernel();

private:  
#line 322 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
  /**
   * Destructor.  Deletes the address space and unregisters it from
   * Space_index.
   */
  
  void
  dir_shutdown();
};
#line 225 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"


//---------------------------------------------------------------------------

#line 35 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space-user.cpp"

//----------------------------------------------------------------------------

#line 63 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"

//----------------------------------------------------------------------------


//
// IMPLEMENTATION includes follow (for use by inline functions/templates)
//

#line 71 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
#include "mem_layout.h"
#line 363 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
#include "mem_unit.h"
#line 366 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
#include "logdefs.h"
#line 367 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
#include "paging.h"
#line 371 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"
#include "kmem.h"
#line 523 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"

#include "cpu.h"

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 294 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"


inline Ram_quota *
Mem_space::ram_quota() const
{ return _quota; }

#line 306 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"


inline Mem_space::Dir_type*
Mem_space::dir ()
{ return _dir; }

#line 311 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"


inline const Mem_space::Dir_type*
Mem_space::dir() const
{ return _dir; }

#line 346 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"


inline void
Mem_space::enable_tlb(Cpu_number)
{}

#line 351 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"


inline void
Mem_space::disable_tlb(Cpu_number)
{}

#line 356 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space.cpp"


inline Cpu_mask
Mem_space::active_tlb()
{
  Cpu_mask c;
  c.set(Cpu_number::boot_cpu());
  return c;
}

#line 74 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"





inline Mem_space::Mem_space(Ram_quota *q) : _quota(q), _dir(0) {}

#line 102 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


inline bool
Mem_space::is_full_flush(L4_fpage::Rights rights)
{
  return (bool)(rights & L4_fpage::Rights::R());
}

#line 109 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


inline bool
Mem_space::has_superpages()
{
  return Cpu::have_superpages();
}

#line 133 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


inline bool
Mem_space::set_attributes(Virt_addr virt, Attr page_attribs)
{
  auto i = _dir->walk(virt);

  if (!i.is_valid())
    return false;

  i.set_attribs(page_attribs);
  return true;
}

#line 226 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"

/**
 * Simple page-table lookup.
 *
 * @param virt Virtual address.  This address does not need to be page-aligned.
 * @return Physical address corresponding to a.
 */

inline Address
Mem_space::virt_to_phys(Address virt) const
{
  return dir()->virt_to_phys(virt);
}

#line 239 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"

/**
 * Simple page-table lookup.
 *
 * @param virt Virtual address.  This address does not need to be page-aligned.
 * @return Physical address corresponding to a.
 */

inline Address
Mem_space::pmem_to_phys(Address virt) const
{
  return Mem_layout::pmem_to_phys(virt);
}

#line 252 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"

/**
 * Simple page-table lookup.
 *
 * This method is similar to Space_context's virt_to_phys().
 * The difference is that this version handles Sigma0's
 * address space with a special case:  For Sigma0, we do not
 * actually consult the page table -- it is meaningless because we
 * create new mappings for Sigma0 transparently; instead, we return the
 * logically-correct result of physical address == virtual address.
 *
 * @param a Virtual address.  This address does not need to be page-aligned.
 * @return Physical address corresponding to a.
 */

inline Address
Mem_space::virt_to_phys_s0(void *a) const
{
  return dir()->virt_to_phys((Address)a);
}

#line 372 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


inline Address
Mem_space::phys_dir()
{
  return Mem_layout::pmem_to_phys(_dir);
}

#line 525 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


inline Page_number
Mem_space::canonize(Page_number v)
{ return v; }

#line 80 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


inline bool
Mem_space::initialize()
{
  void *b;
  if (EXPECT_FALSE(!(b = Kmem_alloc::allocator()
	  ->q_alloc(_quota, Config::PAGE_SHIFT))))
    return false;

  _dir = static_cast<Dir_type*>(b);
  _dir->clear(false);	// initialize to zero
  return true; // success
}

#line 146 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"



inline void
Mem_space::destroy()
{}

#line 433 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


inline int
Mem_space::sync_kernel()
{
  return _dir->sync(Virt_addr(Mem_layout::User_max + 1), Kmem::dir(),
                    Virt_addr(Mem_layout::User_max + 1),
                    Virt_size(-(Mem_layout::User_max + 1)), Pdir::Super_level,
                    false,
                    Kmem_alloc::q_allocator(_quota));
}

#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space-user.cpp"



template< typename T > inline T
Mem_space::peek(T const *addr, bool user_space)
{
  return user_space ? peek_user(addr) : *addr;
}

#line 52 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space-user.cpp"



template< typename T > inline T
Mem_space::peek_user(T const *addr)
{
  return *addr;
}

#line 60 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/mem_space-user.cpp"



template< typename T > inline void
Mem_space::poke_user(T *addr, T value)
{
  *addr = value;
}

#line 116 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"



inline void
Mem_space::tlb_flush(bool)
{
  if (_current.current() == this)
    Mem_unit::tlb_flush();
}

#line 125 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"



inline Mem_space *
Mem_space::current_mem_space(Cpu_number cpu) /// XXX: do not fix, deprecated, remove!
{
  return _current.cpu(cpu);
}

#line 379 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"

/*
 * The following functions are all no-ops on native ia32.
 * Pages appear in an address space when the corresponding PTE is made
 * ... unlike Fiasco-UX which needs these special tricks
 */


inline void
Mem_space::page_map(Address, Address, Address, Attr)
{}

#line 390 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


inline void
Mem_space::page_protect(Address, Address, unsigned)
{}

#line 395 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


inline void
Mem_space::page_unmap(Address, Address)
{}

#line 400 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


inline void
Mem_space::switchin_context(Mem_space *from)
{
  // FIXME: this optimization breaks SMP task deletion, an idle thread
  // may run on an already deleted page table
#if 0
  // never switch to kernel space (context of the idle thread)
  if (dir() == Kmem::dir())
    return;
#endif

  if (from != this)
    {
      CNT_ADDR_SPACE_SWITCH;
      make_current();
    }
}

#line 422 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/mem_space-ia32.cpp"


inline void
Mem_space::make_current()
{
  Cpu::set_pdbr((Mem_layout::pmem_to_phys(_dir)));
  _current.cpu(current_cpu()) = this;
}

#endif // mem_space_h
