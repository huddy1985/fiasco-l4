// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef string_buffer_h
#define string_buffer_h

//
// INTERFACE definition follows 
//

#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/string_buffer.cpp"

class String_buffer
{
public:
  String_buffer() : _buf(0), _len(0) {}
  String_buffer(char *buf, int len) : _buf(buf), _len(len) {}

  bool __attribute__((format(printf, 2, 3))) printf(char const *fmt, ...);
  int space() const { return _len; }
  char *remaining_buffer() const { return _buf; }
  void reset(char *buf, int len) { _buf = buf; _len = len; }
  bool append(char c)
  {
    if (_len <= 0)
      return false;

    --_len;
    *(_buf++) = c;
    return true;
  }

private:
  char *_buf;
  int _len;

public:  
#line 58 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/string_buffer.cpp"
  inline void
  fill(char c);
  
#line 66 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/string_buffer.cpp"
  inline void
  terminate();
};
#line 27 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/string_buffer.cpp"

template<unsigned LEN>
class String_buf : public String_buffer
{
public:
  String_buf() : String_buffer(_s, LEN) {}

  int length() const { return LEN - space(); }
  char *begin() { return _s; }
  char const *begin() const { return _s; }
  char const *end() const { return remaining_buffer(); }
  void reset() { String_buffer::reset(_s, LEN); }
  void clear() { reset(); terminate(); }
  char const *c_str()
  {
    terminate();
    return begin();
  }

private:
  char _s[LEN];
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 56 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/string_buffer.cpp"


inline void
String_buffer::fill(char c)
{
  for (; _len > 0; ++_buf, --_len)
    *_buf = c;
}

#line 64 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/string_buffer.cpp"


inline void
String_buffer::terminate()
{
  if (_len)
    *_buf = 0;
  else
    _buf[-1] = 0;
}

#endif // string_buffer_h
