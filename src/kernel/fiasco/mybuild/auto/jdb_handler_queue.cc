// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_handler_queue.h"
#include "jdb_handler_queue_i.h"


#line 34 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/jdb_handler_queue.cpp"


void
Jdb_handler_queue::execute () const
{
  Jdb_handler *h = first;
  while(h)
    {
      h->execute();
      h = h->next;
    }
}
