// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_report.h"
#include "jdb_report_i.h"

#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_report.cpp"

char Jdb_report::subcmd;
#line 23 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_report.cpp"

static Jdb_report jdb_report INIT_PRIORITY(JDB_MODULE_INIT_PRIO);

#line 25 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_report.cpp"


void
Jdb_report::show_objects()
{
  String_buf<256> buf;

  printf("System objects:\n");
  for (Kobject_dbg::Iterator l = Kobject_dbg::begin();
      l != Kobject_dbg::end(); ++l)
    {
      buf.reset();
      Jdb_kobject::obj_description(&buf, false, *l);
      printf("%.*s\n", buf.length(), buf.c_str());
    }
}

#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_report.cpp"

void
Jdb_report::delim(const char *text)
{
  puts(Jdb_screen::Line);
  if (text)
    puts(text);
}

#line 49 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_report.cpp"


Jdb_module::Action_code
Jdb_report::action(int cmd, void *&, char const *&, int &)
{
  if (cmd != 0)
    return NOTHING;

  unsigned orig_height = Jdb_screen::height();
  unsigned orig_width  = Jdb_screen::width();
  Jdb_screen::set_height(9999);
  Jdb_screen::set_width(999);

  Console *gzip = 0;
  if (subcmd == 'c' || subcmd == 'C')
    gzip = Kconsole::console()->find_console(Console::GZIP);

  if (gzip)
    Kconsole::console()->start_exclusive(Console::GZIP);

  delim("Objects:");
  show_objects();

  delim("Threads:");
  Jdb::execute_command_long("threadlist p");
  Jdb::execute_command_long("threadlist r");
  Jdb::execute_command_long("timeoutsdump");

  delim("Kmem:");
  Jdb::execute_command_long("k m");
  delim("Kernel info:");
  Jdb::execute_command_long("k c");
  Jdb::execute_command_long("k f");

  delim("Trace buffer:");
  Jdb::execute_command_long("tbufdumptext");

  delim("Console output:");
  Jdb::execute_command_long("consolebuffer 1000");

  delim("TCBs:");
  Jdb_screen::set_width(80);
  for (Kobject_dbg::Iterator l = Kobject_dbg::begin();
       l != Kobject_dbg::end(); ++l)
    {
      Thread *t = cxx::dyn_cast<Thread *>(Kobject::from_dbg(*l));
      if (t)
        {
          String_buf<22> b;
          b.printf("tcbdump %lx", t->dbg_id());
          delim();
          Jdb::execute_command_long(b.c_str());
        }
    }
  delim("Done");

  if (gzip)
    {
      Kconsole::console()->end_exclusive(Console::GZIP);
      printf("Decode output with: uudecode -o - logfile | zcat\n");
    }

  Jdb_screen::set_height(orig_height);
  Jdb_screen::set_width(orig_width);

  return NOTHING;
}

#line 116 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_report.cpp"


int
Jdb_report::num_cmds() const
{ return 1; }

#line 121 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_report.cpp"


Jdb_module::Cmd const *
Jdb_report::cmds() const
{
  static Cmd cs[] =
    {
      { 0, "Y", "report", "%C", "Y{c}|report <compressed>\tsystem report", &subcmd }
    };
  return cs;
}
