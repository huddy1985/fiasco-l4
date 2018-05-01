// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_obj_space.h"
#include "jdb_obj_space_i.h"


#line 38 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"
static inline Jdb_obj_space::Mode
operator++ (Jdb_obj_space::Mode &m);
#line 209 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"

static Jdb_obj_space jdb_obj_space INIT_PRIORITY(JDB_MODULE_INIT_PRIO);

#line 36 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"


static inline Jdb_obj_space::Mode
operator++ (Jdb_obj_space::Mode &m)
{
  long _m = m;
  ++_m;
  if (_m >= Jdb_obj_space::End_mode)
    _m = 0;

  m = Jdb_obj_space::Mode(_m);

  return m;
}

#line 50 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"


Jdb_obj_space::Jdb_obj_space(Address base, int level)
: _base(base),
  _task(0),
  _mode(Name)
{
  (void)level;
  Jdb_kobject::module()->register_handler(this);
}

#line 60 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"


unsigned
Jdb_obj_space::col_width(unsigned column) const
{ return (column == 0) ? 6 : 16; }

#line 65 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"


unsigned long
Jdb_obj_space::cols() const
{ return Jdb_screen::cols(col_width(0), col_width(1)); }

#line 70 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"


unsigned long
Jdb_obj_space::rows() const
{ return Obj_space::Map_max_address / (cols() - 1); }

#line 75 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"


void
Jdb_obj_space::print_statline(unsigned long row, unsigned long col)
{
  static String_buf<128> buf;
  buf.clear();
  unsigned rights;

  Kobject_iface *o = item(index(row,col), &rights);
  if (!o)
    {
      Jdb::printf_statline("objs", "<Space>=mode", "%lx: -- INVALID --",
                           cxx::int_value<Cap_index>(index(row,col)));
      return;
    }

  Jdb_kobject::obj_description(&buf, true, o->dbg_info());
  Jdb::printf_statline("objs", "<Space>=mode",
                       "%lxr%x: %-*s",
                       cxx::int_value<Cap_index>(index(row,col)),
                       rights, buf.length(), buf.begin());
}

#line 98 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"


void
Jdb_obj_space::print_entry(Cap_index entry)
{
  unsigned rights;
  Kobject_iface *o = item(entry, &rights);

  if (!o)
    printf("       --       ");
  else
    {
      switch (_mode)
        {
        case Name:
          printf("%05lx%c%c%c %-*s",
                 o->dbg_info()->dbg_id(),
                 rights & 8 ? 'D' : '-',
                 rights & 2 ? 'S' : '-',
                 rights & 1 ? 'W' : '-',
                 7, Jdb_kobject::kobject_type(o));
          break;
        case Raw:
        default:
          printf("%16lx", Mword(o) | rights);
          break;
        }
    }
}

#line 127 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"


void
Jdb_obj_space::draw_entry(unsigned long row, unsigned long col)
{
  if (col == 0)
    printf("%06lx", cxx::int_value<Cap_index>(index(row, 1)));
  else
    print_entry(index(row, col));
}

#line 137 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"


Cap_index
Jdb_obj_space::index(unsigned long row, unsigned long col)
{
  Mword e = (col - 1) + (row * (cols() - 1));
  return Cap_index(_base + e);
}

#line 145 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"


bool
Jdb_obj_space::handle_user_keys(int c, Kobject_iface *o)
{
  if (!o)
    return false;

  bool handled = false;
  for (Jdb_kobject::Handler_iter h = Jdb_kobject::module()->global_handlers.begin();
       h != Jdb_kobject::module()->global_handlers.end(); ++h)
    handled |= h->handle_key(o, c);

  if (Jdb_kobject_handler *h = Jdb_kobject::module()->find_handler(o))
    handled |= h->handle_key(o, c);

  return handled;
}

#line 163 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"


unsigned
Jdb_obj_space::key_pressed(int c, unsigned long &row, unsigned long &col)
{
  switch (c)
    {
    default:
      {
        unsigned rights;
        if (handle_user_keys(c, item(index(row, col), &rights)))
          return Redraw;
        return Nothing;
      }

    case KEY_CURSOR_HOME: // return to previous or go home
      return Back;

    case ' ':
      ++_mode;
      return Redraw;
    }
}

#line 186 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"


bool
Jdb_obj_space::handle_key(Kobject_common *o, int code)
{
  if (code != 'o')
    return false;

  Space *t = cxx::dyn_cast<Task*>(o);
  if (!t)
    {
      Thread *th = cxx::dyn_cast<Thread *>(o);
      if (!th || !th->space())
        return false;

      t = th->space();
    }

  _task = t;
  show(0, 0);

  return true;
}

#line 211 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_obj_space.cpp"


Kobject_iface *
Jdb_obj_space::item(Cap_index entry, unsigned *rights)
{
  Obj_space::Entry *c = _task->jdb_lookup_cap(entry);

  if (!c)
    return 0;

  Kobject_iface *o = c->obj();
  *rights = cxx::int_value<Obj::Attr>(c->rights());

  return o;
}
