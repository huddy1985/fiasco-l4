// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "assertion.h"
#include "assertion_i.h"

#line 6 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/assertion.cpp"

// ------------------------------------------------------------------------


#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/assertion.cpp"

extern "C"
void
assert_fail(char const *expr_msg, char const *file, unsigned int line)
{
  // make sure that GZIP mode is off
  Kconsole::console()->end_exclusive(Console::GZIP);

  printf("\nAssertion failed at %s:%u: %s\n", file, line, expr_msg);

  Thread::system_abort();
}
