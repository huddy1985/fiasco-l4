// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "push_console.h"
#include "push_console_i.h"


#line 18 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/push_console.cpp"


int
Push_console::getchar(bool /*blocking*/)
{
  if (_out != _in)
    {
      int c = _buffer[_out++];
      if (_out >= (int)sizeof(_buffer))
	_out = 0;

      return c == '_' ? KEY_RETURN : c;
    }

  return -1; // no keystroke available
}

#line 34 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/push_console.cpp"


int
Push_console::char_avail() const
{
  return _in != _out; // unknown
}

#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/push_console.cpp"


int
Push_console::write(char const * /*str*/, size_t len)
{
  return len;
}

#line 48 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/push_console.cpp"


void
Push_console::push(char c)
{
  int _ni = _in + 1;
  if (_ni >= (int)sizeof(_buffer))
    _ni = 0;

  if (_ni == _out) // buffer full
    return;

  _buffer[_in] = c;
  _in = _ni;
}
