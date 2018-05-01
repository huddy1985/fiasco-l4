// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_input_task.h"
#include "jdb_input_task_i.h"

#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input_task.cpp"

char     Jdb_input_task_addr::first_char;
#line 43 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input_task.cpp"
char     Jdb_input_task_addr::first_char_have_task;
#line 44 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input_task.cpp"
Kobject *Jdb_input_task_addr::_task;
#line 45 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input_task.cpp"
Space   *Jdb_input_task_addr::_space;
#line 46 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input_task.cpp"
Address  Jdb_input_task_addr::_addr;
#line 47 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input_task.cpp"
Jdb_input_task_addr::Symbol Jdb_input_task_addr::symbol;

#line 48 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input_task.cpp"



void
Jdb_input_task_addr::gotkey_complete_symbol(char *&str, int maxlen, int c)
{ (void)str; (void)maxlen;
  if (c == KEY_TAB)
    printf("XXX\n"); //Jdb_symbol::complete_symbol(str, maxlen, task);
}

#line 57 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input_task.cpp"


Task *
Jdb_input_task_addr::task()
{ return cxx::dyn_cast<Task *>(_task); }

#line 62 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input_task.cpp"


Space *
Jdb_input_task_addr::space()
{ return _space; }

#line 67 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input_task.cpp"


Address
Jdb_input_task_addr::addr()
{ return _addr; }

#line 72 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_input_task.cpp"


Jdb_module::Action_code
Jdb_input_task_addr::action(void *&args, char const *&fmt, int &next_char)
{
  if (args == &first_char)
    {
      // initialize
      // so _task is only valid if it is explicitly set
      _task         = 0;
      _space        = Jdb::get_current_space();
      _addr         = (Address)-1;
      symbol.str[0] = '\0';
      symbol.gotkey = gotkey_complete_symbol;
    }

  if (args == &first_char_have_task)
    first_char = first_char_have_task;

  if (args == &first_char && first_char == 't')
    {
      args = &_task;
      fmt  = strcmp(fmt, " addr=%C") ? " task=%q" : " \b\b\b\b\b\btask=%q";
      return Jdb_module::EXTRA_INPUT;
    }
  else if (args == &_task)
    {
      _space = cxx::dyn_cast<Task *>(_task);

      if (_task && !space())
	{
	  _task = 0;
	  puts(" invalid task");
	  return Jdb_module::ERROR;
	}

      args = &first_char_have_task;
      fmt  = " addr=%C";
      return Jdb_module::EXTRA_INPUT;
    }
  else if (first_char == 'p')
    {
      _task = 0;
      _space = 0;
      putstr(" [phys-mem]");

      args = &first_char_have_task;
      fmt  = " addr=%C";
      return Jdb_module::EXTRA_INPUT;
    }
  else if (args == &first_char || args == &first_char_have_task)
    {
      if (first_char == 's')
	{
	  args = &symbol;
	  fmt  = strcmp(fmt, " addr=%C") ? " symbol=%32S"
					 : " \b\b\b\b\b\bsymbol=%32S";
	  return Jdb_module::EXTRA_INPUT;
	}
      else if (isxdigit(first_char))
	{
	  next_char = first_char;
	  args = &_addr;
	  fmt  = L4_ADDR_INPUT_FMT;
	  return Jdb_module::EXTRA_INPUT_WITH_NEXTCHAR;
	}
      else if (first_char != KEY_RETURN && first_char != KEY_RETURN_2
               && first_char != ' ')
	{
	  fmt = "%C";
	  return Jdb_module::EXTRA_INPUT;
	}
    }
  else if (args == &symbol)
    {
#if 0
      // XXX: Fix symbols
      Address sym_addr;
      bool instr = strlen(symbol.str)>=sizeof(symbol.str)-1;
      if ((sym_addr = Jdb_symbol::match_symbol_to_addr(symbol.str,
						       instr, task)))
	_addr = sym_addr;
      else
	{
	  _addr = (Address)-1;
	  puts(" not found");
	  return Jdb_module::ERROR;
	}
#endif
    }

  return Jdb_module::NOTHING;
}