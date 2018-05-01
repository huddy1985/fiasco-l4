// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_attach_irq.h"
#include "jdb_attach_irq_i.h"


#line 157 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
static bool
filter_irqs(Kobject_common const *o);
#line 33 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"

char     Jdb_attach_irq::subcmd;
#line 35 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"
static Jdb_attach_irq jdb_attach_irq INIT_PRIORITY(JDB_MODULE_INIT_PRIO);
#line 160 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"

static Jdb_kobject_list::Mode INIT_PRIORITY(JDB_MODULE_INIT_PRIO) tnt("[IRQs]", filter_irqs);
#line 162 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"

static Jdb_kobject_irq jdb_kobject_irq INIT_PRIORITY(JDB_MODULE_INIT_PRIO);

#line 36 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"


Jdb_attach_irq::Jdb_attach_irq()
  : Jdb_module("INFO")
{}

#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"


Jdb_module::Action_code
Jdb_attach_irq::action( int cmd, void *&args, char const *&, int & )
{
  if (cmd)
    return NOTHING;

  if ((char*)args == &subcmd)
    {
      switch (subcmd)
        {
        case 'l': // list
            {
              Irq_base *r;
              putchar('\n');
	      unsigned n = Irq_mgr::mgr->nr_irqs();
              for (unsigned i = 0; i < n; ++i)
                {
                  r = static_cast<Irq*>(Irq_mgr::mgr->irq(i));
                  if (!r)
                    continue;
                  printf("IRQ %02x/%02u\n", i, i);
                }
              return NOTHING;
            }
        }
    }
  return NOTHING;
}

#line 71 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"


int
Jdb_attach_irq::num_cmds() const
{
  return 1;
}

#line 78 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"


Jdb_module::Cmd const *
Jdb_attach_irq::cmds() const
{
  static Cmd cs[] =
    {   { 0, "R", "irq", " [l]ist/[a]ttach: %c",
	   "R{l}\tlist IRQ threads", &subcmd }
    };

  return cs;
}

#line 108 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"



bool
Jdb_kobject_irq::handle_key(Kobject_common *o, int key)
{
  (void)o; (void)key;
  return false;
}

#line 117 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"




Kobject_common *
Jdb_kobject_irq::follow_link(Kobject_common *o)
{
  Irq_sender *t = cxx::dyn_cast<Irq_sender*>(o);
  Kobject_common *k = t ? Kobject::from_dbg(Kobject_dbg::pointer_to_obj(t->owner())) : 0;
  return k ? k : o;
}

#line 128 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"


bool
Jdb_kobject_irq::show_kobject(Kobject_common *, int)
{ return true; }

#line 133 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"


void
Jdb_kobject_irq::show_kobject_short(String_buffer *buf, Kobject_common *o)
{
  Irq *i = cxx::dyn_cast<Irq*>(o);
  Kobject_common *w = follow_link(o);

  buf->printf(" I=%3lx %s F=%x",
              i->pin(), i->chip()->chip_type(),
              (unsigned)i->flags());

  if (Irq_sender *t = cxx::dyn_cast<Irq_sender*>(i))
    buf->printf(" L=%lx T=%lx Q=%d",
                i->obj_id(),
                w != o ?  w->dbg_info()->dbg_id() : 0,
                t ? t->queued() : -1);

  if (Semaphore *t = cxx::dyn_cast<Semaphore*>(i))
    buf->printf(" Q=%ld",
                t->_queued);
}

#line 155 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_attach_irq.cpp"


static bool
filter_irqs(Kobject_common const *o)
{ return cxx::dyn_cast<Irq const *>(o); }
