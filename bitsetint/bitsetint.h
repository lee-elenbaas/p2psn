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
class bitsetint
{
public:
  constexpr bitsetint() : _val() { }
  constexpr bitsetint(unsigned long v) : _val(v) { }
  //constexpr bitsetint(std::string v) : _val(v) { } // need to convert base10 to binary, or use conversions
  
  constexpr bitsetint(const bitsetint<w>& o) : _val(o._val) { }
  constexpr bitsetint(bitsetint<w>&& o) : _val(std::move(o._val)) { }

  template<size_t ow>
  constexpr bitsetint(const bitsetint<ow>& o) : _val(o._val.to_string()) { static_assert(ow <= w, "Can only implicitly convert bitsetint to longer width"); }
  
  template<size_t ow>
  explicit operator bitsetint<ow>() { return bitsetint<ow>(_val.to_string().substring(ow>=w?0:w-ow)); }
  
  bitsetint<w>& operator += (const bitsetint<w>& o) {
    std::bitset<3> adder;
    
    for(int i=0;i<w; ++i){
      adder[0] = _val[i];
      adder[1] = o._val[i];
      
      _val[i] = (adder.count() != 2); // bit result
      adder[2] = (adder.count() >= 2); // carry
    }
    
    _val[w] = adder[2];
    
    return *this;
  }
  
  bitsetint<w>& operator -= (const bitsetint<w>& o) {
    std::bitset<3> subber;
    
    for(int i=0;i<w; ++i){
      subber[0] = _val[i];
      subber[1] = o._val[i];
      
      _val[i] = (subber.count() != 2); // bit result
      subber[2] = ((subber[0] && subber.all()) || (!subber[0] && subber.any())); // carry
    }
    
    _val[w] = subber[2];
    
    return *this;
  }
private:
  std::bitset<w+1> _val; // bitset is set to w+1 for carry placeholder
};

template<size_t w>
bitsetint<w> operator+(const bitsetint<w>& lhs, const bitsetint<w>& rhs) {
  auto res = lhs;
  return res += rhs;
}

template<size_t w>
bitsetint<w> operator-(const bitsetint<w>& lhs, const bitsetint<w>& rhs) {
  auto res = lhs;
  return res -= rhs;
}

} /* namespace bitsetint */
} /* namespace math */
} /* namespace lee */

#endif // BITWIDTHINT_H
