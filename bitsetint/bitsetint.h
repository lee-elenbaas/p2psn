/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef BITSETINT_H
#define BITSETINT_H

#include <bitset>

namespace lee {
namespace math {
namespace bitsetint {

// signed integer of the given bitwidth
template<size_t w>
class bitsetint;
// unsigned integer of the given bitwidth
template<size_t w>
class ubitsetint;

template <size_t w, size_t i>
constexpr bool add(ubitsetint<w>&, const ubitsetint<w>&);
template <size_t w, size_t i>
constexpr bool sub(ubitsetint<w>&, const ubitsetint<w>&);

template<size_t w>
class ubitsetint
{
public:
  // construction
  constexpr ubitsetint() : _val() { }
  constexpr ubitsetint(unsigned long v) : _val(v) { }
  //constexpr ubitsetint(std::string v) : _val(v) { } // need to convert base10 to binary, or use conversions
  
  constexpr ubitsetint(ubitsetint<w>&& o) : _val(std::move(o._val)) { }

  // width conversions
  template<size_t ow>
  constexpr ubitsetint(const ubitsetint<ow>& o) : _val(o._val) { static_assert(ow <= w, "Can only implicitly convert bitset integer to a longer width"); }
  template<size_t ow>
  explicit operator ubitsetint<ow>() { return ubitsetint<ow>(_val.to_string().substring(ow>=w?0:w-ow)); }
  
  // arithmetic operations
  constexpr ubitsetint<w>& operator+= (const ubitsetint<w>& o) {
    static_assert(w>=1, "bitset integer of size 0 or less does not support arithmetic operations(+)");
    return (add<w,w>(*this, o))?*this:*this;
  }
  template <size_t i>
  friend bool add(ubitsetint<w>&, const ubitsetint<w>&);
  
  constexpr ubitsetint<w>& operator-= (const ubitsetint<w>& o) {
    static_assert(w>=1, "bitset integer of size 0 or less does not support arithmetic operations(-)");
    return (sub<w,w>(*this, o))?*this:*this;
  }
  template <size_t i>
  friend bool sub(ubitsetint<w>&, const ubitsetint<w>&);
  
  // bit accessing
  constexpr public bool bit const(size_t i) { return _var[i]; }
  
  // carry handling
  constexpr public bool carry const() { return _var[w]; }
  public void reset_carry() { _var[w] = false; }
private:
  typedef std::bitset<w+1> bitfield;
  typedef typename bitfield::reference bitreference;
  
  bitfield _val; // bitset is set to w+1 for carry placeholder
};

template<size_t w>
constexpr ubitsetint<w> operator+(const ubitsetint<w>& lhs, const ubitsetint<w>& rhs) { return ubitsetint<w>(lhs) += rhs; }

template<size_t w>
constexpr ubitsetint<w> operator-(const ubitsetint<w>& lhs, const ubitsetint<w>& rhs) { return ubitsetint<w>(lhs) -= rhs; } 

template<size_t w>
constexpr bool adder(typename ubitsetint<w>::bitreference b1, bool b2, bool b3) { return std::pair<bool,bool>( (b1 && b2) || (b1 && b3) || (b2 && b3), b1 = (b1 != b2 != b3)).first; }
template<size_t w>
constexpr bool suber(typename ubitsetint<w>::bitreference b1, bool b2, bool b3) { return std::pair<bool,bool>( (!b1 && b2) || (!b1 && b3) || (b2 && b3), b1 = (1==(((b1?1:0)+(b2?1:0)+(b3?1:0))%2))).first; }

template <size_t w, size_t i>
constexpr bool add(ubitsetint<w>& s, const ubitsetint<w>& o) { return adder(s._val[i], o._val[i], add<w, i-1>(s, o)); }
template <size_t w>
constexpr bool add<w, 0>(ubitsetint<w>& s, const ubitsetint<w>& o) { return adder(s._val[0], o._val[0], false); }

template <size_t w, size_t i>
constexpr bool sub(ubitsetint<w>& s, const ubitsetint<w>& o) { return suber(s._val[i], o._val[i], sub<w, i-1>(o)); }
template <size_t w>
constexpr bool sub<w, 0>(ubitsetint<w>& s, const ubitsetint<w>& o) { return suber(s._val[0], o._val[0], false); }

template<size_t w>
class bitsetint : private ubitsetint<w> {
public:
  // TODO: convertion operator from unsigned bitset to larger signed bit set
  // arithmetic operations
  constexpr ubitsetint<w>& operator+= (const bitsetint<w>& o) {
	bool sameSign = (negative() == o.negative());
	ubutsetint<w>::operator+=(o);
	_overflow = _overflow || o._overflow || (sameSign && carry()); // overflow if one of them is overflow already, or if they are of the same sign but have a carry after the operation
    return *this;
  }
  
  // bit accessing
  using ubutsetint<w>::bit;  
  // sign
  constexpr public bool negative const() { return bit(w-1); }
  // carry handling - same as in ubitsetint
  using ubitsetint<w>::carry;
  // overflow handling
  constexpr public bool overflow const() { return _overflow; }
  public void reset_overflow() { _overflow = false; }
private:
	bool _overflow;
}

} /* namespace bitsetint */
} /* namespace math */
} /* namespace lee */

#endif // BITWIDTHINT_H
