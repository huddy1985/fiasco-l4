// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_kobject_names.h"
#include "jdb_kobject_names_i.h"

#line 1 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
//-----------------------------------------------------------------------

#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"



enum
{
  Name_buffer_size = 8192,
  Name_entries = Name_buffer_size / sizeof(Jdb_kobject_name),
};
#line 49 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"


char const *const Jdb_kobject_name::static_type = "Jdb_kobject_names";
#line 52 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"
Jdb_kobject_name *Jdb_kobject_name::_names;
#line 63 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"

static Spin_lock<> allocator_lock;
#line 213 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"


STATIC_INITIALIZE(Jdb_kobject_name);

#line 53 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"



int
Jdb_kobject_name::max_len()
{ return sizeof(_name); }

#line 59 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"


Jdb_kobject_name::Jdb_kobject_name()
{ _name[0] = 0; }

#line 65 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"


void *
Jdb_kobject_name::operator new (size_t) throw()
{
  Jdb_kobject_name *n = _names;
  while (1)
    {
      void **o = reinterpret_cast<void**>(n);
      if (!*o)
	{
	  auto g = lock_guard(allocator_lock);
	  if (!*o)
	    {
	      *o = (void*)10;
	      return n;
	    }
	}

      ++n;

      if ((n - _names) >= Name_entries)
	return 0;
    }
}

#line 90 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"


void
Jdb_kobject_name::operator delete (void *p)
{
  auto g = lock_guard(allocator_lock);
  void **o = reinterpret_cast<void**>(p);
  *o = 0;
}

#line 99 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"


void
Jdb_kobject_name::name(char const *name, int size)
{
  int i = 0;
  if (size > max_len())
    size = max_len();
  for (; name[i] && i < size; ++i)
    _name[i] = name[i];

  for (; i < max_len(); ++i)
    _name[i] = 0;
}

#line 130 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"


void
Jdb_name_hdl::show_kobject_short(String_buffer *buf, Kobject_common *o)
{
  Jdb_kobject_name *ex
    = Jdb_kobject_extension::find_extension<Jdb_kobject_name>(o);

  if (ex)
    buf->printf(" {%-*.*s}", ex->max_len(), ex->max_len(), ex->name());
}

#line 141 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"


bool
Jdb_name_hdl::invoke(Kobject_common *o, Syscall_frame *f, Utcb *utcb)
{
  switch (utcb->values[0])
    {
    case Op_set_name:
        {
          bool enqueue = false;
          Jdb_kobject_name *ne;
          ne = Jdb_kobject_extension::find_extension<Jdb_kobject_name>(o);
          if (!ne)
            {
              ne = new Jdb_kobject_name();
              if (!ne)
                {
                  f->tag(Kobject_iface::commit_result(-L4_err::ENomem));
                  return true;
                }
              enqueue = true;
            }

          if (f->tag().words() > 0)
            ne->name(reinterpret_cast<char const *>(&utcb->values[1]),
                     (f->tag().words() - 1) * sizeof(Mword));
          if (enqueue)
            o->dbg_info()->_jdb_data.add(ne);
          f->tag(Kobject_iface::commit_result(0));
          return true;
        }
    case Op_get_name:
        {
          Kobject_dbg::Iterator o = Kobject_dbg::id_to_obj(utcb->values[1]);
          if (o == Kobject_dbg::end())
            {
              f->tag(Kobject_iface::commit_result(-L4_err::ENoent));
              return true;
            }
          Jdb_kobject_name *n = Jdb_kobject_extension::find_extension<Jdb_kobject_name>(Kobject::from_dbg(o));
          if (!n)
            {
              f->tag(Kobject_iface::commit_result(-L4_err::ENoent));
              return true;
            }

          unsigned l = min<unsigned>(n->max_len(), sizeof(utcb->values));
          char *dst = reinterpret_cast<char *>(utcb->values);
          strncpy(dst, n->name(), l);
          dst[l - 1] = 0;

          f->tag(Kobject_iface::commit_result(0, (l + sizeof(Mword) - 1) / sizeof(Mword)));
          return true;
        }
    }
  return false;
}

#line 198 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_kobject_names.cpp"

FIASCO_INIT
void
Jdb_kobject_name::init()
{
  _names = (Jdb_kobject_name*)Kmem_alloc::allocator()->unaligned_alloc(Name_buffer_size);
  if (!_names)
    panic("No memory for thread names");

  for (int i=0; i<Name_entries; i++)
    *reinterpret_cast<unsigned long*>(_names + i) = 0;

  static Jdb_name_hdl hdl;
  Jdb_kobject::module()->register_handler(&hdl);
}
