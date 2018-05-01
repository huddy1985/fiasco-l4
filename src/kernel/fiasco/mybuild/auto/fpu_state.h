// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef fpu_state_h
#define fpu_state_h

//
// INTERFACE definition follows 
//

#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/fpu_state.cpp"

class Fpu_state
{
public:
  void *state_buffer();
  void state_buffer(void *b);

  Fpu_state();
  ~Fpu_state();

private:
  friend class Fpu_alloc;

  void *_state_buffer;
};

//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 19 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/fpu_state.cpp"


inline Fpu_state::Fpu_state() : _state_buffer(0)
{}

#line 23 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/fpu_state.cpp"


inline Fpu_state::~Fpu_state()
{
}

#line 28 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/fpu_state.cpp"


inline void *Fpu_state::state_buffer()
{
  return _state_buffer;
}

#line 34 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/fpu_state.cpp"


inline void Fpu_state::state_buffer(void *b)
{
  _state_buffer = b;
}

#endif // fpu_state_h
