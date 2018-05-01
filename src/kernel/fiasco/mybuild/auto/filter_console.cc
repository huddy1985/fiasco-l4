// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "filter_console.h"
#include "filter_console_i.h"


#line 36 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/filter_console.cpp"


int Filter_console::char_avail() const
{
  if (!(_o->state() & INENABLED))
    return -1;

  if (pos)
    return 1;

  return _o->char_avail();
}

#line 56 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/filter_console.cpp"



int
Filter_console::write(char const *str, size_t len)
{
  if (!(_o->state() & OUTENABLED))
    return len;

  char const *start = str;
  char const *stop  = str;

  static char seq[18];
  char const *const home = "\033[H";
  char const *const cel  = "\033[K";

  for (; stop < str + len; ++stop)
    {
      switch (*stop)
        {
        case 1:
          if (stop - start)
            _o->write(start, stop - start);
          start = stop + 1;
          _o->write(home, 3);
          break;
        case 5:
          if (stop - start)
            _o->write(start, stop - start);
          start = stop + 1;
          _o->write(cel, 3);
          break;
        case 6:
          if (stop - start)
            _o->write(start, stop - start);
          if (stop + 2 < str + len)
            {
              snprintf(seq, sizeof(seq), "\033[%d;%dH",
                       stop[1] + 1, stop[2] + 1);
              _o->write(seq, strlen(seq));
            }
          stop += 2;
          start = stop + 1;
          break;
      }
    }

  if (stop-start)
    _o->write(start, stop-start);

  return len;
}

#line 121 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/filter_console.cpp"


int
Filter_console::getchar(bool b)
{
  if (!(_o->state() & INENABLED))
    return -1;

  unsigned loop_count = 100;
  int ch;

get_char:
  if (state == UNKNOWN_ESC && pos)
    {
      ch = ibuf[0];
      memmove(ibuf, ibuf + 1, --pos);
    }
  else
    ch = _o->getchar(b);

  if (!pos)
    state = NORMAL;

  if (ch == -1)
    {
      if (state == NORMAL)
        return -1;
      else if (!b && loop_count--)
        goto get_char;
      else
        return -1;
    }

  switch (state)
    {
    case UNKNOWN_ESC:
      return ch;

    case NORMAL:
      if (ch == 27)
        {
          ibuf[pos++] = 27;
          int nc = getchar_timeout(csi_timeout);
          if (nc == -1)
            {
              pos = 0;
              return KEY_SINGLE_ESC;
            }
          else
            {
              if (pos < sizeof(ibuf))
                ibuf[pos++] = nc;
              if (nc == '[' || nc == 'O')
                {
                  arg = 0;
                  memset(args, 0, sizeof(args));
                  state = GOT_CSI;
                  break;
                }
              else
                {
                  state = UNKNOWN_ESC;
                  goto get_char;
                }
            }
        }
      return ch;

    case GOT_CSI:
      if (isdigit(ch))
        {
          if (pos < sizeof(ibuf))
            ibuf[pos++] = ch;

          if (arg < (sizeof(args) / sizeof(int)))
            args[arg] = args[arg] * 10 + (ch - '0');
        }
      else if (ch == ';')
        {
          if (pos < sizeof(ibuf))
            ibuf[pos++] = ch;

          arg++;
        }
      else
        {
          state = NORMAL;
          if (pos < sizeof(ibuf))
            ibuf[pos++] = ch;

          switch(ch)
            {
            case 'A': pos = 0; return KEY_CURSOR_UP;
            case 'B': pos = 0; return KEY_CURSOR_DOWN;
            case 'C': pos = 0; return KEY_CURSOR_RIGHT;
            case 'D': pos = 0; return KEY_CURSOR_LEFT;
            case 'H': pos = 0; return KEY_CURSOR_HOME;
            case 'F': pos = 0; return KEY_CURSOR_END;
            case '~':
              pos = 0;
              switch (args[0])
                {
                case  7:
                case  1: return KEY_CURSOR_HOME;
                case  2: return KEY_INSERT;
                case  3: return KEY_DELETE;
                case  8:
                case  4: return KEY_CURSOR_END;
                case  5: return KEY_PAGE_UP;
                case  6: return KEY_PAGE_DOWN;
                case 11: return KEY_F1;

                default:
                  arg = 0;
                  if (b)
                    goto get_char;
                  else if (loop_count)
                    {
                      --loop_count;
                      goto get_char;
                    }
                  else
                    return -1;
                }
            case 'P': return KEY_F1;
            default:
              state = UNKNOWN_ESC;
              break;
            }
        }
      break;
    }

  if (b)
    goto get_char;
  else if (loop_count)
    {
      loop_count--;
      goto get_char;
    }

  return -1;
}

#line 264 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/filter_console.cpp"



Mword
Filter_console::get_attributes() const
{
  return _o->get_attributes();
}
