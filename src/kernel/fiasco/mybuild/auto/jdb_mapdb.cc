// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_mapdb.h"
#include "jdb_mapdb_i.h"


#line 34 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
static const char*
size_str (Mword size);
#line 29 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"

char  Jdb_mapdb::subcmd;
#line 31 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"
Mword Jdb_mapdb::pagenum;
#line 386 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"

static Jdb_mapdb jdb_mapdb INIT_PRIORITY(JDB_MODULE_INIT_PRIO);
#line 420 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"



STATIC_INITIALIZE(Jdb_kobject_mapdb_hdl);
#line 470 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"

// --------------------------------------------------------------------------


#line 32 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"


static const char*
size_str (Mword size)
{
  static char scratchbuf[6];
  unsigned mult = 0;
  while (size >= 1024)
    {
      size >>= 10;
      mult++;
    }
  snprintf(scratchbuf, 6, "%hu%c", (unsigned short)size, "BKMGTPX"[mult]);
  return scratchbuf;
}

#line 47 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"


unsigned long long
Jdb_mapdb::val(Mdb_types::Pfn p, Mdb_types::Order base_size)
{
  return cxx::int_value<Mdb_types::Pfn>(p << base_size);
}

#line 54 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"



bool
Jdb_mapdb::show_tree(Treemap* pages, Mapping::Pcnt offset, Mdb_types::Order base_size,
                     unsigned &screenline, unsigned indent)
{
  typedef Treemap::Page Page;

  Page       page = pages->trunc_to_page(offset);
  Physframe*    f = pages->frame(page);
  Mapping_tree* t = f->tree.get();
  unsigned      i;
  int           c;

  if (! t)
    {
      printf(" no mapping tree registered for frame number 0x%lx\033[K\n",
             cxx::int_value<Mapping::Page>(page));
      screenline++;
      return true;
    }

  printf(" mapping tree for %s-page %012llx of task %lx - header at "
         L4_PTR_FMT "\033[K\n",
         size_str(1ULL << cxx::int_value<Mdb_types::Order>(pages->_page_shift + base_size)),
         val(pages->vaddr(t->mappings()), base_size),
         Kobject_dbg::pointer_to_id(t->mappings()[0].space()),
         (Address)t);
#ifdef NDEBUG
  // If NDEBUG is active, t->_empty_count is undefined
  printf(" header info: "
         "entries used: %u  free: --  total: %u  lock=%u\033[K\n",
         t->_count, t->number_of_entries(),
         f->lock.test());

  if (t->_count > t->number_of_entries())
    {
      printf("\033[K\n"
             "\033[K\n"
             "  seems to be a wrong tree ! ...exiting");
      // clear rest of page
      for (i=6; i<Jdb_screen::height(); i++)
        printf("\033[K\n");
      return false;
    }
#else
  printf(" header info: "
         "entries used: %u  free: %u  total: %u  lock=%d\033[K\n",
         t->_count, t->_empty_count, t->number_of_entries(),
         f->lock.test());

  if (unsigned (t->_count) + t->_empty_count > t->number_of_entries())
    {
      printf("\033[K\n"
             "\033[K\n"
             "  seems to be a wrong tree ! ...exiting");
      // clear rest of page
      for (i=6; i<Jdb_screen::height(); i++)
        printf("\033[K\n");
      return false;
    }
#endif

  Mapping* m = t->mappings();

  screenline += 2;

  unsigned empty = 0;
  for(i=0; i < t->_count + empty; i++, m++)
    {
      Kconsole::console()->getchar_chance();

      if (m->depth() == Mapping::Depth_submap)
        printf("%*u: %lx  subtree@" L4_PTR_FMT,
               indent + m->parent()->depth() > 10
                 ? 0 : (int)(indent + m->parent()->depth()),
               i+1, (Address) m->data(), (Mword) m->submap());
      else
        {
          printf("%*u: %lx  va=%012llx  task=%lx  depth=",
                 indent + m->depth() > 10 ? 0 : (int)(indent + m->depth()),
                 i+1, (Address) m->data(),
                 val(pages->vaddr(m), base_size),
                 Kobject_dbg::pointer_to_id(m->space()));

          if (m->depth() == Mapping::Depth_root)
            printf("root");
          else if (m->depth() == Mapping::Depth_empty)
            {
              printf("empty");
              ++empty;
            }
          else if (m->depth() == Mapping::Depth_end)
            printf("end");
          else
            printf("%lu", static_cast<unsigned long>(m->depth()));
        }

      puts("\033[K");
      screenline++;

      if (screenline >= (m->depth() == Mapping::Depth_submap
                         ? Jdb_screen::height() - 3
                         : Jdb_screen::height()))
        {
          printf(" any key for next page or <ESC>");
          Jdb::cursor(screenline, 33);
          c = Jdb_core::getchar();
          printf("\r\033[K");
          if (c == KEY_ESC)
            return false;
          screenline = 3;
          Jdb::cursor(3, 1);
        }

      if (m->depth() == Mapping::Depth_submap)
        {
          if (! Jdb_mapdb::show_tree(m->submap(),
                                     cxx::get_lsb(offset, pages->_page_shift),
                                     base_size,
                                     screenline, indent + m->parent()->depth()))
            return false;
        }
    }

  return true;
}

#line 182 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"


Address
Jdb_mapdb::end_address (Mapdb* mapdb)
{
  return cxx::int_value<Mdb_types::Pfn>(mapdb->_treemap->end_addr());
}

#line 189 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"


void
Jdb_mapdb::show(Mapping::Pfn page, char which_mapdb)
{
  unsigned     j;
  int          c;

  Jdb::clear_screen();
  typedef Mdb_types::Order Order;

  for (;;)
    {
      Mapdb* mapdb;
      const char* type;
      Mapping::Pcnt super_inc;
      Mdb_types::Order super_shift;
      Order base_size = Order(0);

      switch (which_mapdb)
        {
        case 'm':
          type = "Phys frame";
          mapdb = mapdb_mem.get();
          base_size = Order(Config::PAGE_SHIFT);
          super_shift = Mdb_types::Order(Config::SUPERPAGE_SHIFT - Config::PAGE_SHIFT);
          break;
#ifdef CONFIG_PF_PC
        case 'i':
          type = "I/O port";
          mapdb = mapdb_io.get();
          base_size = Order(0);
          super_shift = Mdb_types::Order(8);
          break;
#endif
        default:
          return;
        }

      super_inc = Mapping::Pcnt(1) << super_shift;

      if (! mapdb->valid_address(page))
        page = Mapping::Pfn(0);

      Jdb::cursor();
      printf("%s %012llx\033[K\n\033[K\n", type, val(page, base_size));

      j = 3;

      if (! Jdb_mapdb::show_tree(mapdb->_treemap, page - Mapping::Pfn(0), base_size, j))
        return;

      for (; j<Jdb_screen::height(); j++)
        puts("\033[K");

      static char prompt[] = "mapdb[m]";
      prompt[6] = which_mapdb;

      Jdb::printf_statline(prompt,
                           "n=next p=previous N=nextsuper P=prevsuper", "_");

      for (bool redraw=false; !redraw; )
        {
          Jdb::cursor(Jdb_screen::height(), 10);
          switch (c = Jdb_core::getchar())
            {
            case 'n':
            case KEY_CURSOR_DOWN:
              if (! mapdb->valid_address(++page))
                page = Mapping::Pfn(0);
              redraw = true;
              break;
            case 'p':
            case KEY_CURSOR_UP:
              if (! mapdb->valid_address(--page))
                page = Mapping::Pfn(end_address(mapdb) - 1);
              redraw = true;
              break;
            case 'N':
            case KEY_PAGE_DOWN:
              page = cxx::mask_lsb(page + super_inc, super_shift);
              if (! mapdb->valid_address(page))
                page = Mapping::Pfn(0);
              redraw = true;
              break;
            case 'P':
            case KEY_PAGE_UP:
              page = cxx::mask_lsb(page - super_inc, super_shift);
              if (! mapdb->valid_address(page))
                page = Mapping::Pfn(end_address(mapdb) - 1);
              redraw = true;
              break;
            case ' ':
              if (which_mapdb == 'm')
#ifdef CONFIG_PF_PC
                which_mapdb = 'i';
              else if (which_mapdb == 'i')
#endif
                which_mapdb = 'm';
              redraw = true;
              break;
            case KEY_ESC:
              Jdb::abort_command();
              return;
            default:
              if (Jdb::is_toplevel_cmd(c))
                return;
            }
        }
    }
}

#line 300 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"


Jdb_module::Action_code
Jdb_mapdb::action(int cmd, void *&args, char const *&fmt, int &next_char)
{
  static char which_mapdb = 'm';

  if (cmd == 1)
    {
      dump_all_cap_trees();
      return NOTHING;
    }

  if (cmd != 0)
    return NOTHING;

  if (args == (void*) &subcmd)
    {
      switch (subcmd)
        {
        default:
          return NOTHING;

        case '\r':
        case ' ':
          goto doit;

        case '0' ... '9':
        case 'a' ... 'f':
        case 'A' ... 'F':
          which_mapdb = 'm';
          fmt = " frame: " L4_FRAME_INPUT_FMT;
          args = &pagenum;
          next_char = subcmd;
          return EXTRA_INPUT_WITH_NEXTCHAR;

        case 'm':
          fmt = " frame: " L4_FRAME_INPUT_FMT;
          break;

#ifdef CONFIG_PF_PC
        case 'i':
          fmt = " port: " L4_FRAME_INPUT_FMT;
          break;
#endif
        }

      which_mapdb = subcmd;
      args = &pagenum;
      return EXTRA_INPUT;
    }

  else if (args != (void*) &pagenum)
    return NOTHING;

 doit:
  show(Mapping::Pfn(pagenum), which_mapdb);
  return NOTHING;
}

#line 359 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"


Jdb_module::Cmd const *
Jdb_mapdb::cmds() const
{
  static Cmd cs[] =
    {
        { 0, "m", "mapdb", "%c",
          "m[i]<addr>\tshow [I/O] mapping database starting at address",
          &subcmd },
        { 1, "", "dumpmapdbobjs", "",
          "dumpmapdbobjs\tDump complete object mapping database", 0 },
    };
  return cs;
}

#line 374 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"


int
Jdb_mapdb::num_cmds() const
{
  return 2;
}

#line 381 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"


Jdb_mapdb::Jdb_mapdb()
  : Jdb_module("INFO")
{}

#line 398 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"

FIASCO_INIT
void
Jdb_kobject_mapdb_hdl::init()
{
  static Jdb_kobject_mapdb_hdl hdl;
  Jdb_kobject::module()->register_handler(&hdl);
}

#line 406 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"


bool
Jdb_kobject_mapdb_hdl::handle_key(Kobject_common *o, int keycode)
{
  if (keycode == 'm')
    {
      Jdb_mapdb::show_simple_tree(o);
      Jdb::getchar();
      return true;
    }
  else
    return false;
}

#line 475 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"


bool
Jdb_mapdb::show_simple_tree(Kobject_common *f, unsigned indent)
{
  (void)indent;
  (void)f;

  unsigned      screenline = 0;
  int           c;

  puts(Jdb_screen::Line);
  if (!f || f->map_root()->_root.empty())
    {
      printf(" no mapping tree registered for frame number 0x%lx\033[K\n",
             (unsigned long) f);
      screenline++;
      puts(Jdb_screen::Line);
      return true;
    }

  printf(" mapping tree for object D:%lx (%p) ref_cnt=%ld\033[K\n",
         f->dbg_info()->dbg_id(), f, f->map_root()->_cnt);

  screenline += 2;

  for (Obj::Mapping::List::Iterator m = f->map_root()->_root.begin();
       m != f->map_root()->_root.end(); ++m)
    {
      Kconsole::console()->getchar_chance();

      Obj::Entry *e = static_cast<Obj::Entry*>(*m);
      Dbg_page_info *pi = Dbg_page_info::table()[Virt_addr(e)];

      Mword space_id = ~0UL;
      Address cap_idx = ((Address)e % Config::PAGE_SIZE) / sizeof(Obj::Entry);

      String_buf<16> task_descr;
      if (pi)
        {
          Kobject_dbg *o =  static_cast<Task*>(pi->info<Obj::Cap_page_dbg_info>()->s)->dbg_info();
          space_id = o->dbg_id();
          Jdb_kobject_name *n = Jdb_kobject_extension::find_extension<Jdb_kobject_name>(Kobject::from_dbg(o));
          if (n)
            task_descr.printf("(%.*s)", n->max_len(), n->name());
          cap_idx += pi->info<Obj::Cap_page_dbg_info>()->offset;
        }

      printf("  " L4_PTR_FMT "[C:%lx]: space=D:%lx%.*s rights=%x flags=%lx obj=%p",
             (Address)*m, cap_idx, space_id, task_descr.length(), task_descr.begin(),
             (unsigned)cxx::int_value<Obj::Attr>(e->rights()), e->_flags,
             e->obj());

      puts("\033[K");
      screenline++;

      if (screenline >= Jdb_screen::height())
        {
          printf(" any key for next page or <ESC>");
          Jdb::cursor(screenline, 33);
          c = Jdb_core::getchar();
          printf("\r\033[K");
          if (c == KEY_ESC)
            return false;
          screenline = 3;
          Jdb::cursor(3, 1);
        }
    }

  puts(Jdb_screen::Line);
  return true;
}

#line 547 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_mapdb.cpp"


void
Jdb_mapdb::dump_all_cap_trees()
{
  printf("========= OBJECT DUMP BEGIN ===================\n");
  printf("========= OBJECT DUMP END ===================\n");
}
