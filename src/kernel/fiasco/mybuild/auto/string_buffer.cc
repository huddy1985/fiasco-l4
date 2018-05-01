// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "string_buffer.h"
#include "string_buffer_i.h"


#line 74 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/string_buffer.cpp"



bool
String_buffer::printf(char const *fmt, ...)
{
  if (_len <= 0)
    return false;

  va_list list;
  int l;
  va_start(list, fmt);
  l = vsnprintf(_buf, _len, fmt, list);
  va_end(list);
  if (l >= _len)
    {
      _buf += _len;
      _len = 0;
      return false;
    }

  _buf += l;
  _len -= l;
  return true;
}
