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

  // TODO :
  //   1. support construction from numerical strings - including decimal, binary, hex and octal strings
  //   1.1. introduce suffix used for construction such values
  //   2. convertion operator from unsigned bitset to larger signed bit set
  //   3. need to deal with overflow on long constructor in case of very small bitset
  //   4. introduce int status enum: overflow, underflow, invalid
  
  // perform the * and assign,ent operations using matrices:
  // 10110 * 10010 =	000000000 + = 110001100
  //			000101100
  //			000000000
  //			000000000
  //			101100000
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
  typedef std::bitset<w> bitfield;
  typedef typename bitfield::reference bitreference;
  
  // construction
  constexpr 
  ubitsetint() : _val(), _flags() { }
  constexpr 
  ubitsetint(unsigned long long v) : _val(v), _flags() { }
  
  // move operation
  constexpr 
  ubitsetint(ubitsetint<w>&& o) : _val(std::move(o._val)) { }

  // width conversions
  template<size_t ow>
  constexpr 
  ubitsetint(const ubitsetint<ow>& o) : _val(o._val) { static_assert(ow <= w, "Can only implicitly convert bitset integer to a longer width"); }
  template<size_t ow>
  explicit 
  operator ubitsetint<ow>() { return ubitsetint<ow>(to_binary_string().substring(ow>=w?0:w-ow)); }
  
  // string conversions
  constexpr 
  std::string to_binary_string () const { return _val.To_string(); }
  constexpr 
  explicit 
  ubitsetint<w>(const std::string& binary_string) : _val(binary_string) { };
  
  // arithmetic operations
  constexpr 
  ubitsetint<w>& operator+= (const ubitsetint<w>& o) {
    static_assert(w>=1, "bitset integer of size 0 or less does not support arithmetic operations");
    return (_overflow = _carry = add<w,w-1>(*this, o))?*this:*this;
  }
  template <size_t i>
  friend 
  bool add(ubitsetint<w>&, const ubitsetint<w>&);
  
  constexpr
  ubitsetint<w> operator-() const {
    return ((~*this)+1);
  }
  constexpr 
  ubitsetint<w>& operator-= (const ubitsetint<w>& o) {
    return (*this += -o);
  }
  
  constexpr
  ubitsetint<w>& operator*=(const ubitsetint<w>& o) {
      return (*this = (*this * o));
  }
  // bit operators
  constexpr
  ubitsetint<w> operator~ () const {
    return ubitsetint<w>(~_val, _carry, _overflow);
  }
  constexpr
  friend
  ubitsetint<w> operator&(const ubitsetint<w>& lhs, const ubitsetint<w>& rhs)
  // bit accessing
  constexpr
  bool bit(size_t i) const { return _var[i]; }
  template<size_t i>
  constexpr
  bool bit() const { return get<i>(_var); }
  
  // carry handling
  constexpr 
  bool carry() const { return _carry; }
  constexpr 
  bool overflow() const { return _overflow; }
  void reset_overflow() { _overflow = false; }
private:
  bitfield _val;
  bool _carry;
  bool _overflow;
  
  // operation set constructors
  constexpr
  ubitsetint(bitfield&& val, bool carry, bool overflow) : _val(val), _carry(carry), _overflow(overflow) { }
  constexpr
  ubitsetint(const bitfield& val, bool carry, bool overflow) : _val(val), _carry(carry), _overflow(overflow) { }
};

template<size_t w>
constexpr bool adder(typename ubitsetint<w>::bitreference b1, bool b2, bool b3) { return std::pair<bool,bool>( (b1 && b2) || (b1 && b3) || (b2 && b3), b1 = (b1 != b2 != b3)).first; }

template <size_t w, size_t i>
constexpr bool add(ubitsetint<w>& s, const ubitsetint<w>& o) { return adder(s._val[i], o._val[i], add<w, i-1>(s, o)); }
template <size_t w>
constexpr bool add<w, 0>(ubitsetint<w>& s, const ubitsetint<w>& o) { return adder(s._val[0], o._val[0], false); }

template<size_t w>
constexpr ubitsetint<w> operator+(const ubitsetint<w>& lhs, const ubitsetint<w>& rhs) { return ubitsetint<w>(lhs) += rhs; }

template<size_t w, size_t i>
constexpr ubitsetint<w> mul(ubitsetint<w>& res, const ubitsetint<w>& zero, const ubitsetint<w>& lhs, const ubitsetint<w>& rhs) { return ((res += rhs.bit<i>()?(lhs << i):zero) += mul<i-1>(res, zero, lhs, rhs); }
template<size_t w>
constexpr ubitsetint<w> mul<-1>(ubitsetint<w>& res, const ubitsetint<w>& zero, const ubitsetint<w>& lhs, const ubitsetint<w>& rhs) { return zero; }

template<size_t w>
constexpr ubitsetint<w> operator*(const ubitsetint<w>& lhs, const ubitsetint<w>& rhs) { return mul<w>(ubitsetint<w>(), ubitsetint<w>(), lhs,rhs); }

template<size_t w>
class bitsetint : private ubitsetint<w> {
public:
  // construction
  constexpr bitsetint() : ubitsetint() { }
  constexpr bitsetint(unsigned long v) : ubitsetint(v) { }

    // move operation
  constexpr bitsetint(bitsetint<w>&& o) : ubitsetint(o) { }

  // width conversions
  template<size_t ow>
  constexpr bitsetint(const bitsetint<ow>& o) : ubitsetint(o) { }
  template<size_t ow>
  explicit operator bitsetint<ow>() { return bitsetint<ow>(to_binary_string().substring(ow>=w?0:w-ow)); }
  
  // string conversions
  using ubitsetint::to_binary_string;
  constexpr explicit bitsetint<w>(const std::string& binary_string) : ubitsetint(binary_string) { };

  // arithmetic operations
  constexpr ubitsetint<w>& operator+= (const bitsetint<w>& o) {
	bool sameSign = (negative() == o.negative());
	ubitsetint<w>::operator+=(o);
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

template<size_t w>
constexpr ubitsetint<w> operator-(const ubitsetint<w>& lhs, const ubitsetint<w>& rhs) { return ubitsetint<w>(lhs) -= rhs; } 

} /* namespace bitsetint */
} /* namespace math */
} /* namespace lee */

#endif // BITWIDTHINT_H
