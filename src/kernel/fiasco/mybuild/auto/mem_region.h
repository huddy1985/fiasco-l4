// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef mem_region_h
#define mem_region_h

//
// INTERFACE definition follows 
//

#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/mem_region.cpp"

class Mem_region
{
public:
  unsigned long start, end;

  Mem_region() : start(0), end(0) {}

  Mem_region(unsigned long start, unsigned long end) : start(start), end(end) {}

  bool valid() const { return start < end; }

  bool operator < (Mem_region const &o) const
  { return end < o.start; }

  bool overlaps(Mem_region const &o) const
  { return !(o < *this || *this < o); }

  bool contains(Mem_region const &o) const
  { return start <= o.start && end >= o.end; }

  void merge(Mem_region const &r)
  {
    start = start < r.start ? start : r.start;
    end   = end > r.end     ? end   : r.end;
  }

  unsigned long size() const
  { return end - start + 1; }

};
#line 33 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/mem_region.cpp"


class Mem_region_map_base
{
public:
  virtual bool add(Mem_region const &r) = 0;
  virtual bool sub(Mem_region const &r) = 0;
};
#line 41 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/mem_region.cpp"

template< unsigned E >
class Mem_region_map : public Mem_region_map_base
{
public:
  enum { Entries = E };
  Mem_region_map() : _l(0) {}

private:
  unsigned _l;

  Mem_region _r[Entries];

public:  
#line 73 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/mem_region.cpp"
  inline bool
  add(Mem_region const &r);
  
#line 110 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/mem_region.cpp"
  inline bool
  sub(Mem_region const &r);
  
#line 148 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/mem_region.cpp"
  inline unsigned
  length() const;
  
#line 154 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/mem_region.cpp"
  inline Mem_region const &
  operator[] (unsigned idx) const;
  
#line 160 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/mem_region.cpp"
  inline Mem_region &
  operator[] (unsigned idx);

private:  
#line 61 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/mem_region.cpp"
  inline void
  del(unsigned start, unsigned end);
};
#line 54 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/mem_region.cpp"


//--------------------------------------------------------------------------


//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 58 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/mem_region.cpp"



template< unsigned E > inline void
Mem_region_map<E>::del(unsigned start, unsigned end)
{
  unsigned delta = end - start;
  for (unsigned p = start; p < end; ++p)
    _r[p] = _r[p + delta];

  _l -= delta;
}

#line 70 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/mem_region.cpp"



template< unsigned E > inline bool
Mem_region_map<E>::add(Mem_region const &r)
{
  if (!r.valid())
    return true;

  unsigned pos = 0;
  for (;pos < _l && _r[pos] < r; ++pos) ;
  if (_l > pos && !(r < _r[pos]))
    { // overlap -> merge
      _r[pos].merge(r);
      for (unsigned p = pos + 1; p < _l; ++p)
	{
	  if (!(_r[pos] < _r[p]))
	    _r[pos].merge(_r[p]);
	  else
	    {
	      del(pos + 1, p);
	      return true;
	    }
	}
      _l = pos + 1;
      return true;
    }

  if (_l >= Entries)
    return false;

  for (unsigned p = _l; p > pos; --p) _r[p] = _r[p-1];
  ++_l;
  _r[pos] = r;
  return true;
}

#line 106 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/mem_region.cpp"




template< unsigned E > inline bool
Mem_region_map<E>::sub(Mem_region const &r)
{
  if (!r.valid())
    return true;

  unsigned pos;
  for (pos = 0; pos < _l; ++pos)
    {
      if (_r[pos].overlaps(r))
	{
	  if (r.contains(_r[pos]))
	    {
	      del(pos, pos+1);
	      --pos; // ensure we do not skip the next element
	    }
	  else if (r.start <= _r[pos].start)
	    _r[pos].start = r.end + 1;
	  else if (r.end >= _r[pos].end)
	    _r[pos].end = r.start - 1;
	  else
	    {
	      if (_l >= Entries)
		return false;

	      for (unsigned p = _l; p > pos; --p) _r[p] = _r[p-1];
	      ++_l;
	      _r[pos+1].start = r.end + 1;
	      _r[pos+1].end = _r[pos].end;
	      _r[pos].end = r.start - 1;
	    }
	}
    }
  return true;
}

#line 145 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/mem_region.cpp"



template< unsigned E > inline unsigned
Mem_region_map<E>::length() const
{ return _l; }

#line 151 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/mem_region.cpp"



template< unsigned E > inline Mem_region const &
Mem_region_map<E>::operator[] (unsigned idx) const
{ return _r[idx]; }

#line 157 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/lib/libk/mem_region.cpp"



template< unsigned E > inline Mem_region &
Mem_region_map<E>::operator[] (unsigned idx)
{ return _r[idx]; }

#endif // mem_region_h
