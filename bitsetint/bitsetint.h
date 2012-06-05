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

template<size_t w>
class bitsetint;

template <size_t w, size_t i>
constexpr bool add(bitsetint<w>&, const bitsetint<w>&);
template <size_t w, size_t i>
constexpr bool sub(bitsetint<w>&, const bitsetint<w>&);

template<size_t w>
class bitsetint
{
public:
  constexpr bitsetint() : _val() { }
  constexpr bitsetint(unsigned long v) : _val(v) { }
  //constexpr bitsetint(std::string v) : _val(v) { } // need to convert base10 to binary, or use conversions
  
  constexpr bitsetint(bitsetint<w>&& o) : _val(std::move(o._val)) { }

  template<size_t ow>
  constexpr bitsetint(const bitsetint<ow>& o) : _val(o._val) { static_assert(ow <= w, "Can only implicitly convert bitsetint to longer width"); }
  
  template<size_t ow>
  explicit operator bitsetint<ow>() { return bitsetint<ow>(_val.to_string().substring(ow>=w?0:w-ow)); }
  
  constexpr bitsetint<w>& operator+= (const bitsetint<w>& o) {
    static_assert(w>=1, "bitsetint of size 0 or less does not support arithmetic operations(+)");
    return (add<w,w>(*this, o))?*this:*this;
  }
  template <size_t i>
  friend bool add(bitsetint<w>&, const bitsetint<w>&);
  
  constexpr bitsetint<w>& operator-= (const bitsetint<w>& o) {
    static_assert(w>=1, "bitsetint of size 0 or less does not support arithmetic operations(-)");
    return (sub<w,w>(*this, o))?*this:*this;
  }
  template <size_t i>
  friend bool sub(bitsetint<w>&, const bitsetint<w>&);
private:
  typedef std::bitset<w+1> bitfield;
  typedef typename bitfield::reference bitreference;
  
  bitfield _val; // bitset is set to w+1 for carry placeholder
};

template<size_t w>
constexpr bitsetint<w> operator+(const bitsetint<w>& lhs, const bitsetint<w>& rhs) { return bitsetint<w>(lhs) += rhs; }

template<size_t w>
constexpr bitsetint<w> operator-(const bitsetint<w>& lhs, const bitsetint<w>& rhs) { return bitsetint<w>(lhs) -= rhs; } 

template<size_t w>
constexpr bool adder(typename bitsetint<w>::bitreference b1, bool b2, bool b3) { return std::pair<bool,bool>( (b1 && b2) || (b1 && b3) || (b2 && b3), b1 = (b1 != b2 != b3)).first; }
template<size_t w>
constexpr bool suber(typename bitsetint<w>::bitreference b1, bool b2, bool b3) { return std::pair<bool,bool>( (!b1 && b2) || (!b1 && b3) || (b2 && b3), b1 = (1==(((b1?1:0)+(b2?1:0)+(b3?1:0))%2))).first; }

template <size_t w, size_t i>
constexpr bool add(bitsetint<w>& s, const bitsetint<w>& o) { return adder(s._val[i], o._val[i], add<w, i-1>(s, o)); }
template <size_t w>
constexpr bool add<w, 0>(bitsetint<w>& s, const bitsetint<w>& o) { return adder(s._val[0], o._val[0], false); }

template <size_t w, size_t i>
constexpr bool sub(bitsetint<w>& s, const bitsetint<w>& o) { return suber(s._val[i], o._val[i], sub<w, i-1>(o)); }
template <size_t w>
constexpr bool sub<w, 0>(bitsetint<w>& s, const bitsetint<w>& o) { return suber(s._val[0], o._val[0], false); }

} /* namespace bitsetint */
} /* namespace math */
} /* namespace lee */

#endif // BITWIDTHINT_H
