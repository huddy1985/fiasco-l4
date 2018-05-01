// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_list.h"
#include "jdb_list_i.h"


#line 45 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"




Jdb_list::Jdb_list()
  : _start(0), _current(0)
{
  _filter_str[0] = 0;
}

#line 54 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"

// set _t_start element of list

void
Jdb_list::set_start(void *start)
{
  _start = start;
}

#line 86 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"

// _t_start -= 24 if possible

bool
Jdb_list::page_back()
{ return filtered_seek(-Jdb_screen::height()+3, &_start); }

#line 92 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"

// _t_start += 24 if possible

bool
Jdb_list::page_forw()
{
  int fwd = filtered_seek(Jdb_screen::height()-3, &_last);
  if (fwd)
    return filtered_seek(fwd, &_start);
  return false;
}

#line 111 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"

// _t_start = first element of list

bool
Jdb_list::goto_home()
{ return filtered_seek(-99999, &_start); }

#line 117 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"

// _t_start = last element of list

bool
Jdb_list::goto_end()
{ return filtered_seek(99999, &_start); }

#line 130 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"

// search index of search starting from _start

int
Jdb_list::lookup_in_visible_area(void *search)
{
  unsigned i;
  void *t;

  for (i = 0, t = _start; i < Jdb_screen::height() - 3; ++i)
    {
      if (t == search)
        return i;

      filtered_seek(1, &t);
    }

  return -1;
}

#line 149 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"

// get y'th element of thread list starting from _t_start

void *
Jdb_list::index(int y)
{
  void *t = _start;

  filtered_seek(y, &t);
  return t;
}

#line 160 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"


void
Jdb_list::handle_string_filter_input()
{
  Jdb::printf_statline("filter", 0, "%s=%s",
                       Jdb_regex::avail() ? "Regexp" : "Search",
                       _filter_str);

  Jdb::cursor(Jdb_screen::height(), 16 + strlen(_filter_str));
  if (!Jdb_input::get_string(_filter_str, sizeof(_filter_str)) ||
      !_filter_str[0])
    return;


  if (Jdb_regex::avail() && !Jdb_regex::start(_filter_str))
    {
      _filter_str[0] = 0;
      Jdb::printf_statline("search", 0, "Error in regexp");
      Jdb::getchar();
    }
}

#line 182 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"


Jdb_list::Line_buf *
Jdb_list::render_visible(void *i)
{
  static Line_buf buffer;
  buffer.clear();
  void *p = i;
  while ((p = parent(p)))
    buffer.append(' ');

  show_item(&buffer, i);
  if (_filter_str[0])
    {
      buffer.terminate();
      if (Jdb_regex::avail())
        {
          if (!Jdb_regex::find(buffer.begin(), 0, 0))
            i = 0;
        }
      else if (!strstr(buffer.begin(), _filter_str))
        i = 0;
    }

  if (i)
    return &buffer;

  return 0;
}

#line 211 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"


int
Jdb_list::print_limit(const char *s, int visible_len)
{
  if (!s || !visible_len)
    return 0;

  int s_len = 0, e = 0;
  while (*s && visible_len)
    {
      if (e == 0 && *s == '\033')
        e = 1;
      else if (e == 1 && *s == '[')
        e = 2;
      else if (e == 2)
        {
          if (isalpha(*s))
            e = 0;
        }
      else
        visible_len--;

      s_len++;
      s++;
    }

  return s_len;
}

#line 240 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"


void
Jdb_list::show_line(Jdb_list::Line_buf *b)
{
  Kconsole::console()->getchar_chance();

  // our modified printf ignores the length argument if used with
  // strings containing ESC-sequences
  int s_len_visible = print_limit(b->begin(), Jdb_screen::width());
  b->begin()[s_len_visible] = 0;
  printf("%s\033[K\n", b->begin());
}

#line 253 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"


void *
Jdb_list::get_visible(void *i)
{
  if (render_visible(i))
    return i;

  filtered_seek(1, &i);

  return i;
}

#line 265 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"


int
Jdb_list::filtered_seek(int cnt, void **item, Jdb_list::Line_buf **buf)
{
  if (cnt == 0)
    return 0;

  int c = 0;
  int d = cnt < 0 ? -1 : 1;
  for (;;)
    {
      int i;

      if ((i = seek(d, item)) == 0)
        return c;

      if (Line_buf *b = render_visible(*item))
        {
          if (buf)
            *buf = b;
          c += d;
          if (cnt == c)
            return c;
        }
    }
}

#line 292 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"

// show complete page using show callback function

int
Jdb_list::page_show()
{
  void *t = _start;
  unsigned i = 0;

  if (Jdb_regex::avail() && _filter_str[0])
    assert(Jdb_regex::start(_filter_str));

  if (!t)
    return 0;

  Line_buf *b = render_visible(t);

  for (i = 0; i < Jdb_screen::height()-3; ++i)
    {
      if (!t)
        break;
      _last = t;

      if (b)
        show_line(b);

      if (!filtered_seek(1, &t, &b))
        return i;
    }

  return i - 1;
}

#line 401 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"



void
Jdb_list::show_header()
{
  Jdb::cursor();
  printf("%.*s\033[K\n", (int)Jdb_screen::width(), show_head());
}

#line 410 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_list.cpp"


void
Jdb_list::do_list()
{
  int y, y_max;
  void *t;

  if (!_start)
    _start = get_head();

  if (!_current)
    _current = _start;

  Jdb::clear_screen();
  show_header();

  if (!_start)
    {
      printf("[EMPTY]\n");
      return;
    }


  for (;;)
    {
      _start = get_visible(_start);
      // set y to position of t_current in current displayed list
      y = lookup_in_visible_area(_current);
      if (y == -1)
	{
	  _start = _current;
	  y = 0;
	}

      for (bool resync=false; !resync;)
	{
	  Jdb::cursor(2, 1);
	  y_max = page_show();

	  // clear rest of screen (if where less than 24 lines)
	  for (unsigned i = y_max; i < Jdb_screen::height()-3; ++i)
            putstr("\033[K\n");

          char const *d = "<Space>=mode <Tab>=link <CR>=select /=filter";
          if (_filter_str[0])
            Jdb::printf_statline("Objs", d,
                                 "%s (%s)", get_mode_str(), _filter_str);
          else
            Jdb::printf_statline("Objs", d, "%s", get_mode_str());

	  // key event loop
	  for (bool redraw=false; !redraw; )
	    {
	      Jdb::cursor(y+2, 1);
	      switch (int c=Jdb_core::getchar())
		{
		case KEY_CURSOR_UP:
		case 'k':
		  if (y > 0)
		    y--;
		  else
		    redraw = line_back();
		  break;
		case KEY_CURSOR_DOWN:
		case 'j':
		  if (y < y_max)
		    y++;
		  else
		    redraw = line_forw();
		  break;
		case KEY_PAGE_UP:
		case 'K':
		  if (!(redraw = page_back()))
		    y = 0;
		  break;
		case KEY_PAGE_DOWN:
		case 'J':
		  if (!(redraw = page_forw()))
		    y = y_max;
		  break;
		case KEY_CURSOR_HOME:
		case 'H':
		  redraw = goto_home();
		  y = 0;
		  break;
		case KEY_CURSOR_END:
		case 'L':
		  redraw = goto_end();
		  y = y_max;
		  break;
		case 's': // switch sort
		  _current = index(y);
		  next_sort();
		  redraw = true;
		  resync = true;
		  break;
		case ' ': // switch mode
                  _current = index(y);
		  next_mode();
		  _current = get_valid(_current);
                  _start   = get_valid(_start);
		  redraw = true;
		  resync = true;
		  break;
                case '/':
                  handle_string_filter_input();
                  _current = get_visible(_current);
                  redraw = true;
                  resync = true;
                  break;
		case KEY_TAB: // go to associated object
		  _current = index(y);
		  t = follow_link(_current);
		  if (t != _current)
		    {
		      _current = t;
		      redraw = true;
		      resync = true;
		    }
		  break;
		case KEY_RETURN:
		case KEY_RETURN_2:
		  _current = index(y);
		  if (!enter_item(_current))
		    return;
		  show_header();
		  redraw = 1;
		  break;
		case KEY_ESC:
		  Jdb::abort_command();
		  return;
		default:
		  _current = index(y);
		  if (!handle_key(_current, c) && Jdb::is_toplevel_cmd(c))
		    return;

		  show_header();
		  redraw = 1;
		  break;
		}
	    }
	}
    }
}
