// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef mux_console_h
#define mux_console_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/mux_console.cpp"

#include "types.h"
#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/mux_console.cpp"
#include "console.h"

//
// INTERFACE definition follows 
//

#line 5 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/mux_console.cpp"

/**
 * Console multiplexer.
 *
 * This implementation of the Console interface can be used to
 * multiplex among some input, output, and in-out consoles.
 */
class Mux_console : public Console
{
public:

  enum
  {
    SIZE = 8  ///< The maximum number of consoles to be multiplexed.
  };

  int  write(char const *str, size_t len);
  int  getchar(bool blocking = true);
  int  char_avail() const;

private:
  int     _next_getchar;
  int     _items;
  Console *_cons[SIZE];
  Unsigned64 _ignore_input_until;

public:  
#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/mux_console.cpp"
  Mux_console();
  
#line 57 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/mux_console.cpp"
  void
  set_ignore_input();
  
#line 64 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/mux_console.cpp"
  void
  set_ignore_input(Unsigned64 delta);
  
#line 151 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/mux_console.cpp"
  /**
   * deliver attributes of all subconsoles.
   */
  
  Mword
  get_attributes() const;
  
#line 168 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/mux_console.cpp"
  void
  getchar_chance();
  
#line 198 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/mux_console.cpp"
  /**
   * Register a console to be multiplexed.
   * @param cons the Console to add.
   * @param pos the position of the console, normally not needed.
   */
  
  virtual bool
  register_console(Console *c, int pos = 0);
  
#line 229 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/mux_console.cpp"
  /**
   * Unregister a console from the multiplexer.
   * @param cons the console to remove.
   */
  
  bool
  unregister_console(Console *c);
  
#line 250 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/mux_console.cpp"
  /**
   * Change the state of a group of consoles specified by
   *        attributes.
   * @param any_true   match if console has any of these attributes
   * @param all_false  match if console doesn't have any of these attributes
   */
  
  void
  change_state(Mword any_true, Mword all_false,
  			  Mword mask, Mword bits);
  
#line 277 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/mux_console.cpp"
  /**
   * Find a console with a specific attribute.
   * @param any_true match to console which has set any bit of this bitmask
   */
  
  Console*
  find_console(Mword any_true);
  
#line 292 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/mux_console.cpp"
  /**
   * Start exclusive mode for a specific console. Only the one
   *        console which matches to any_true is enabled for input and
   *        output. All other consoles are disabled.
   * @param any_true match to console which has set any bit of this bitmask
   */
  
  void
  start_exclusive(Mword any_true);
  
#line 308 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/mux_console.cpp"
  /**
   * End exclusive mode for a specific console.
   * @param any_true match to console which has set any bit of this bitmask
   */
  
  void
  end_exclusive(Mword any_true);
  
#line 326 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/mux_console.cpp"
  void
  list_consoles();

private:  
#line 71 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/mux_console.cpp"
  int
  check_input_ignore();
};

#endif // mux_console_h
