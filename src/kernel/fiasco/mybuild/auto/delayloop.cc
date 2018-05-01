// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "delayloop.h"
#include "delayloop_i.h"

#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/delayloop.cpp"

unsigned Delay::count;

#line 22 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/delayloop.cpp"


unsigned
Delay::measure()
{
  Cpu_time t1;
  unsigned count = 0;

  Kip *k = Kip::k();
  Cpu_time t = k->clock;
  Timer::update_timer(t + 1000); // 1ms
  while (t == (t1 = k->clock))
    Proc::pause();
  Timer::update_timer(k->clock + 1000); // 1ms
  while (t1 == k->clock)
    {
      ++count;
      Proc::pause();
    }

  return count;
}

#line 44 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/delayloop.cpp"

void
Delay::init()
{
  count = measure();
  unsigned c2 = measure();
  if (c2 > count)
    count = c2;
}

#line 53 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/delayloop.cpp"

/**
 * Hint: ms is actually the timer granularity, which
 *       currently happens to be milliseconds
 */
void
Delay::delay(unsigned ms)
{
  Kip *k = Kip::k();
  while (ms--)
    {
      unsigned c = count;
      while (c--)
        {
	  (void)k->clock;
	  Proc::pause();
	}
    }
}
