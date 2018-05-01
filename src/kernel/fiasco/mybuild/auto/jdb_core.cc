// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_core.h"
#include "jdb_core_i.h"

#line 153 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"

bool Jdb_core::short_mode = true;
#line 155 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
int  Jdb_core::next_char  = -1;
#line 156 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
char Jdb_core::esc_prompt[32] = JDB_ANSI_COLOR(green);
#line 157 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
Jdb_core::Input_fmt *Jdb_core::_fmt_list[26]; 
#line 158 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
void (*Jdb_core::wait_for_input)();
#line 813 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"

static Go_m go_m INIT_PRIORITY(JDB_MODULE_INIT_PRIO);
#line 858 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


static Help_m help_m INIT_PRIORITY(JDB_MODULE_INIT_PRIO);
#line 975 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"

#define CAT(n, x...) static Jdb_category INIT_PRIORITY(JDB_CATEGORY_INIT_PRIO) n(x)
#line 977 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
CAT(a, "GENERAL",    "general debugger commands",      0);
#line 978 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
CAT(b, "INFO",       "information about kernel state", 1);
#line 979 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
CAT(c, "MONITORING", "monitoring kernel events",       2);
#line 980 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
CAT(d, "DEBUGGING",  "real debugging stuff",           3);
#line 981 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"
#undef CAT

#line 159 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


bool
Jdb_core::add_fmt_handler(char fmt, Input_fmt* hdlr)
{
  if (fmt < 'a' || (fmt - 'a') >= (int)(sizeof(_fmt_list)/sizeof(_fmt_list[0])))
    return false;

  if (_fmt_list[fmt - 'a'])
    return false;

  _fmt_list[fmt - 'a'] = hdlr;
  return true;
}

#line 173 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


void
Jdb_core::print_prompt()
{ prompt_start(); prompt(); prompt_end(); }

#line 178 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


void Jdb_core::update_prompt()
{
  Jdb_prompt_ext::update_all();
}

#line 184 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


void Jdb_core::prompt_start()
{
  putstr(esc_prompt);
}

#line 190 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


void Jdb_core::prompt_end()
{
  putstr(JDB_ANSI_END);
}

#line 196 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


void Jdb_core::prompt()
{
  Jdb_prompt_ext::do_all();
  if (short_mode)
    putstr("jdb: ");
  else
    putstr("jdb# ");
}

#line 206 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


int Jdb_core::prompt_len()
{
  return 5;
}

#line 212 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


int Jdb_core::print_len(const char *s)
{
  int l = 0;
  while (*s)
    {
      if (s[0] == '\033' && s[1] == '[')
        {
	  s += 2;
	  while (*s && *s != 'm')
	    s++;
	  if (*s)
	    s++; // skip 'm'
        }
      else
        {
	  l++;
          s++;
	}
    }
  return l;
}

#line 235 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


int
Jdb_core::get_ansi_color(char c)
{
  switch(c)
    {
    case 'N': case 'n': return 30;
    case 'R': case 'r': return 31;
    case 'G': case 'g': return 32;
    case 'Y': case 'y': return 33;
    case 'B': case 'b': return 34;
    case 'M': case 'm': return 35;
    case 'C': case 'c': return 36;
    case 'W': case 'w': return 37;
    default:  return 0;
    }
}

#line 253 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"



int Jdb_core::set_prompt_color(char x)
{
  unsigned pc = get_ansi_color(x);

  if (pc == 0)
    return 0;

  if (x >= 'A' && x <= 'Z')
    snprintf(esc_prompt, sizeof(esc_prompt) - 1, "\033[%u;%dm", pc, 1);
  else
    snprintf(esc_prompt, sizeof(esc_prompt) - 1, "\033[%um", pc);

  return 1;

}

#line 271 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


Jdb_core::Cmd Jdb_core::has_cmd(char const *cmd)
{
  for (Jdb_module::List::Const_iterator m = Jdb_module::modules.begin();
       m != Jdb_module::modules.end(); ++m)
    {
      Cmd c(*m);
      c.cmd = m->has_cmd(cmd, short_mode);
      if (c.cmd)
        return c;
    }

  return Cmd(0);
}

#line 286 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


unsigned
Jdb_core::match_len(char const *a, char const *b, unsigned l)
{
  unsigned p = 0;
  while (*a && *b && p < l && *a == *b)
    {
      ++a; ++b; ++p;
    }
  return p;
}

#line 298 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


unsigned
Jdb_core::print_alternatives(char const *prefix)
{
  unsigned prefix_len = 0;
  char const *match = 0;
  typedef Jdb_module::List::Const_iterator Iter;
  for (Iter m = Jdb_module::modules.begin(); m != Jdb_module::modules.end(); ++m)
    {
      unsigned sc_max = m->num_cmds();
      Jdb_module::Cmd const *cmds = m->cmds();
      for (unsigned sc = 0; sc < sc_max; ++sc)
	{
	  if (!Jdb_module::match(cmds[sc].cmd, prefix, false))
	    continue;

	  if (!match)
	    {
	      match = cmds[sc].cmd;
	      prefix_len = strlen(match);
	    }
	  else
	    prefix_len = match_len(match, cmds[sc].cmd, prefix_len);
	  printf("%s %s\n", cmds[sc].cmd, cmds[sc].fmt);
	}
    }
  return prefix_len;
}

#line 327 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


Jdb_core::Cmd
Jdb_core::complete_cmd(char const *prefix, bool &multi_match)
{
  Cmd match(0,0);
  multi_match = false;
  typedef Jdb_module::List::Const_iterator Iter;
  for (Iter m = Jdb_module::modules.begin(); m != Jdb_module::modules.end(); ++m)
    {
      unsigned sc_max = m->num_cmds();
      Jdb_module::Cmd const *cmds = m->cmds();
      for (unsigned sc = 0; sc < sc_max; ++sc)
	{
	  if (!Jdb_module::match(cmds[sc].cmd, prefix, false))
	    continue;

	  if (match.cmd)
	    multi_match = true;
	  else
	    match = Cmd(*m, cmds + sc);
	}
    }

  return match;
}

#line 353 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


int Jdb_core::getchar()
{
  if (next_char != -1)
    {
      int c = next_char;
      next_char = -1;
      return c;
    }

  int c;

  while (1)
    {
      c = Kconsole::console()->getchar(false);
      if (c != -1)
        return c == KEY_SINGLE_ESC ? KEY_ESC : c;

      if (wait_for_input)
        wait_for_input();
      else
        Proc::pause();
    }
}

#line 378 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


int
Jdb_core::cmd_getchar(char const *&str)
{
  if (next_char != -1)
    {
      int c = next_char;
      next_char = -1;
      return c;
    }

  if (short_mode)
    return getchar();

  if (!str)
    return KEY_RETURN;

  if (!*str)
    return KEY_RETURN;

  return *(str++);
}

#line 406 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


int Jdb_core::exec_cmd(Cmd const cmd, char const *str, int push_next_char)
{
  char const* f = cmd.cmd->fmt;
  char const* f1;

  //char args[256];
  void *argbuf = (void*)cmd.cmd->argbuf;

  enum {
    NORMAL,
    UNSIGNED,
    MULTI,
  } num_mode;

  int num_base = 10;
  int num_pos = 0, num_digit = 0;
  int max_len = 0, max_digit = 0;
  int c, cv;
  char fm;

  next_char = push_next_char;

  do {

    char *next_arg = (char*)argbuf;
    char const *old_f = f;
    while(*f)
      {
	f1 = f;

	while(*f && *f!='%')
	  ++f;

        if (short_mode)
	  putnstr( f1, (f-f1) );

	if(*(f++))
	  {
	    int long_fmt = sizeof(long long int) == sizeof(void*);
	    bool negative = false;
	    long long int val = 0;
	    max_len = 0;

	  next_fmt:
	    if(*(f))
	      switch((fm=*(f++)))
		// Attention: Each case statement must finish with "continue"
		//            else it falls through to int_done!
		{
		case '0': case '1': case '2':
		case '3': case '4': case '5':
		case '6': case '7': case '8':
		case '9':
		  max_len = max_len * 10 + fm - '0';
		  goto next_fmt;
		case '%':
		  cmd_putchar('%');
		  continue;

		case 'l':
		  long_fmt++;
		  if(long_fmt > 2) 
		    long_fmt = 2;
		  goto next_fmt;

		case 'h':
		  long_fmt--;
		  if(long_fmt < -1)
		    long_fmt = -1;
		  goto next_fmt;

		case 'i':
		  num_base = 10;
		  num_mode = MULTI;
		  goto input_num;

		case 'p':
		  num_base = 16;
		  num_mode = UNSIGNED;
		  if(sizeof(short int)==sizeof(void*))
		    long_fmt = -1;
		  else if(sizeof(int)==sizeof(void*))
		    long_fmt = 0;
		  else if(sizeof(long int)==sizeof(void*))
		    long_fmt = 1;
		  else //if(sizeof(long long int)==sizeof(void*))
		    long_fmt = 2;
		  goto input_num;

		case 'o':
		  cmd_putchar('0');
		  num_mode = UNSIGNED;
		  num_base = 8;
		  goto input_num;

		case 'X':
		case 'x':
		  num_mode = UNSIGNED;
		  num_base = 16;
		  goto input_num;

		case 'd':
		  num_mode = NORMAL;
		  num_base = 10;
		  goto input_num;

		case 'u':
		  num_mode = UNSIGNED;
		  num_base = 10;
		  goto input_num;

		input_num:
		  num_pos = num_digit = 0;
		  max_digit = 0;
		  if (num_base == 16)
		    {
		      if (long_fmt == -1)
			max_digit = 2*sizeof(short int);
		      else if (long_fmt == 0)
			max_digit = 2*sizeof(int);
		      else if (long_fmt == 1)
			max_digit = 2*sizeof(long int);
		      else
			max_digit = 2*sizeof(long long int);
		    }
		  while((c = cmd_getchar(str)) != ' ' && c!=KEY_RETURN
                         && c != KEY_RETURN_2)
		    {
		      if(c==KEY_ESC)
			return 3;
		      
		      if(c==KEY_BACKSPACE && num_pos>0)
			{
			  putstr("\b \b");
			  if(num_pos == 1 && negative)
			    negative = false;
			  else if(num_pos==1 && num_mode==MULTI && num_base==8)
			    num_base = 10;
			  else if(num_pos==2 && num_mode==MULTI && num_base==16)
			    num_base = 8;
			  else
			    {
			      val = div32(val, num_base);
			      num_digit--;
			    }

			  num_pos--;
			  continue;
			}
		      else if(num_mode!=UNSIGNED && num_pos==0 && c=='-')
			{
			  num_pos++;
			  cmd_putchar(c);
			  negative = true;
			  continue;
			}
		      else if(num_mode==MULTI && num_pos==0 && c=='0')
			{
			  num_pos++;
			  cmd_putchar(c);
			  num_base = 8;
			  continue;
			}
		      else if(num_mode==MULTI && num_pos==1 && num_base==8 
			      && (c=='x' || c=='X'))
			{
			  num_pos++;
			  cmd_putchar(c);
			  num_base = 16;
			  continue;
			}
		      else if(num_pos==1 && (c=='x' || c=='X'))
			{
			  // ignore 0x to allow direct pasting of addresses
			  num_pos--;
			  num_digit--;
			  putstr("\b \b");
			  continue;
			}
		      else if(c>='0' && c<='9')
			{
			  cv = c-'0';
			}
		      else if((c|0x20)>='a' && (c|0x20)<='f')
			{
			  cv = (c|0x20) - 'a' + 10;
			}
		      else
			continue;

		      if(cv < num_base)
			{
			  num_pos++;
			  num_digit++;
			  cmd_putchar(c);
			  val = val * num_base + cv;
			  if ((max_len   != 0 && num_pos   >= max_len) ||
			      (max_digit != 0 && num_digit >= max_digit))
			    break;
			}
		    }
		  if (num_pos == 0)
		    return 3;
		  goto int_done;

		case 't': printf("%%t is not supported...\n");
		  continue;

		case 'C':
		case 'c':
		  {
		    int c = cmd_getchar(str);
		    if(c==KEY_ESC)
		      return 3;

		    if(fm == 'c' && isprint(c))
		      cmd_putchar(c);
		    if(next_arg)
		      *next_arg++ = c;
		  }
		  continue;

		case 's':
		case 'S':
		  if(!max_len)
		    continue;

		  num_pos = 0;
		  while((c = cmd_getchar(str)) != KEY_RETURN && c!=' '
                        && c != KEY_RETURN_2)
		    {
		      if(c==KEY_ESC)
			return 3;

		      if(c==KEY_BACKSPACE && num_pos)
			{
			  putstr("\b \b");
			  num_pos--;
			}
		      else if(isprint(c) && (num_pos+1 < max_len))
			{
			  cmd_putchar(c);
			  next_arg[num_pos++] = c;
			}

		      next_arg[num_pos] = '\0';

		      if (fm=='S')
			{
			  int oldlen = num_pos;
			  (**(Jdb_module::Gotkey**)(next_arg+max_len))
			    (next_arg, max_len, c);
			  int newlen = strlen(next_arg);
			  if (newlen > oldlen)
			    printf("%s", next_arg + oldlen);
			  else if (newlen < oldlen)
			    for (int i=newlen; i<oldlen; i++)
			      putstr("\b \b");
			  num_pos = newlen;
			}
		    }
		  next_arg[num_pos] = '\0';
		  next_arg[max_len-1] = 0;
		  next_arg += max_len;
		  continue;

		default:
		  if (fm > 'a'
		      && (fm - 'a') < (int)(sizeof(_fmt_list)/sizeof(_fmt_list[0]))
		      && _fmt_list[fm -'a'])
		    {
		      int size = sizeof(int);
		      switch(long_fmt)
			{
			default: break;
			case 1: size = sizeof(long int); break;
			case 2: size = sizeof(long long int);  break;
			case -1: size = sizeof(short int); break;
			}
		      int res = (_fmt_list[fm - 'a'])(fm, &size, str, next_arg);
		      if (res)
			return res;

		      next_arg += size;
		      continue;
		    }

		  puts(" unknown format! ");
		  return 3;
		}

	  int_done:
	    if(negative) val = -val;

	    if(next_arg)
	      switch(long_fmt)
		{
		default:
		    {
		      int *v = (int*)next_arg;
		      *v = val;
		      next_arg += sizeof(int);
		    }
		  break;
		case 1:
		    {
		      long int *v = (long int*)next_arg;
		      *v = val;
		      next_arg += sizeof(long int);
		    }
		  break;
		case 2:
		    {
		      long long int *v = (long long int*)next_arg;
		      *v = val;
		      next_arg += sizeof(long long int);
		    }
		  break;
		case -1:
		    {
		      short int *v = (short int*)next_arg;
		      *v = val;
		      next_arg += sizeof(short int);
		    }
		  break;
		}
	  }
	else
	  break;
      }

    f = old_f;

    switch (cmd.mod->action(cmd.cmd->id, argbuf, f, next_char))
      {
      case Jdb_module::EXTRA_INPUT:
	// more input expected
	next_char = -1;
	// fall through
      case Jdb_module::EXTRA_INPUT_WITH_NEXTCHAR:
	// more input expected, also consider previously entered key
	break;
      case Jdb_module::LEAVE:
	// leave kernel debugger
	return 0;
      case Jdb_module::GO_BACK:
	// user entered KEY_HOME
	return 2;
      case Jdb_module::NOTHING:
	// finished successfully
	return 1;
      default:
	// there was an error
	return 3;
      }
  } while(1);

}

#line 766 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


int
Jdb_core::new_line( unsigned &line )
{
  if (line++ > Jdb_screen::height()-3)
    {
      putstr("--- CR: line, SPACE: page, ESC: abort ---");
      int a = getchar();
      putstr("\r\033[K");

      switch (a)
	{
	case KEY_ESC:
	case 'q':
	case '^':
	  cmd_putchar('\n');
	  return 0;
	case KEY_RETURN:
	case KEY_RETURN_2:
	  line--;
	  return 1;
	default:
	  line=0;
	  return 1;
	}
    }
  return 1;
}

#line 815 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


Go_m::Go_m()
  : Jdb_module("GENERAL")
{}

#line 820 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


Jdb_module::Action_code Go_m::action( int, void *&, char const *&, int & )
{
  return LEAVE;
}

#line 826 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


int Go_m::num_cmds() const
{ 
  return 1;
}

#line 832 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


Jdb_module::Cmd const * Go_m::cmds() const
{
  static Cmd cs[] =
    { 
	{ 0, "g", "go", "",
	   "g\tleave kernel debugger\n"
	   "Return\tshow debug message", 0 },
    };

  return cs;
}

#line 861 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"



Jdb_module::Action_code Help_m::action( int, void *&, char const *&, int & )
{
  size_t const tab_width = 27;

  if(Jdb_category::categories.begin() == Jdb_category::categories.end())
    {
      printf("No debugger commands seem to have been registered\n");
      return NOTHING;
    }

  unsigned line = 0;

  puts("");
  for (Jdb_category::List::Const_iterator c = Jdb_category::categories.begin();
       c != Jdb_category::categories.end(); ++c)
    {
      bool first = true;
      for (Jdb_module::List::Const_iterator m = Jdb_module::modules.begin();
           m != Jdb_module::modules.end(); ++m)
	{
          if (m->category() != *c)
            continue;

	  if(first)
	    {
	      if(!Jdb_core::new_line(line))
		return NOTHING;
	      printf("\033[1m[%s]\033[0m %s", c->name(), c->description());
	      putchar('\n');
	      if(!Jdb_core::new_line(line))
		return NOTHING;
	      first = false;
	    }
	  unsigned ncmds = m->num_cmds();
	  Jdb_module::Cmd const *cmds = m->cmds();
	  for(unsigned x = 0; x < ncmds; x++)
	    {
	      char const *descr = cmds[x].descr;
	      if (!descr)
		continue;
	      size_t pos = strcspn(descr, "\n\t");
	      size_t xpos = 2;
	      putstr("  ");
	      while( pos  < strlen(descr))
		{
		  putnstr(descr, pos);
		  xpos += pos;
		  switch(descr[pos])
		    {
		    case '\n':
		      putchar('\n');
		      if(!Jdb_core::new_line(line))
			return NOTHING;
		      putstr("  ");
		      xpos = 2;
		      break;
		    case '\t':
		      if(xpos<tab_width)
			{
			  putnstr("                            ",
				  tab_width-xpos);
			  xpos = tab_width;
			}
		      else
			{
			  putchar(' ');
			  xpos++;
			}
		      break;
		    default:
		      break;
		    }
		  descr = descr + pos + 1;
		  pos = strcspn(descr, "\n\t");
		}

	      putstr(descr);
	      putchar('\n');
	      if(!Jdb_core::new_line(line))
		return NOTHING;
	    }
	}
    }

  putchar('\n');

  return NOTHING;
}

#line 952 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


int Help_m::num_cmds() const
{ 
  return 2;
}

#line 958 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


Jdb_module::Cmd const * Help_m::cmds() const
{
  static Cmd cs[] =
    {
	{ 0, "h", "help", "", "h\tShow this help screen.", 0 },
	{ 0, "?", 0, "", 0, 0 },
    };

  return cs;
}

#line 970 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_core.cpp"


Help_m::Help_m()
  : Jdb_module("GENERAL")
{}
