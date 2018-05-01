// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "terminate.h"
#include "terminate_i.h"


#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/terminate.cpp"
/**
 * The exit handler as long as exit_question() is not installed.
 */

static void
raw_exit();
#line 29 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/terminate.cpp"


static void (*exit_question)(void) = &raw_exit;
#line 37 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/terminate.cpp"


extern "C" void FIASCO_NORETURN _exit(int);

#line 12 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/terminate.cpp"

/**
 * The exit handler as long as exit_question() is not installed.
 */

static void
raw_exit()
{
  // make sure that we don't acknowledge the exit question automatically
  Kconsole::console()->change_state(Console::PUSH, 0,
                                    ~Console::INENABLED, 0);
  puts("\nPress any key to reboot.");
  Kconsole::console()->getchar();
  puts("\033[1mRebooting.\033[m");
  //  Cpu::busy_wait_ns(10000000);
  platform_reset();
}

#line 32 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/terminate.cpp"

void set_exit_question(void (*eq)(void))
{
  exit_question = eq;
}

#line 40 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/terminate.cpp"

FIASCO_NORETURN
void
terminate (int exit_value)
{
  Helping_lock::threading_system_active = false;

  if (exit_question)
    exit_question();

  puts("\nShutting down...");

  _exit(exit_value);
}
