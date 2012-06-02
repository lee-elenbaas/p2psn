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


#ifndef MODULU_H
#define MODULU_H

#include <utility>

namespace lee {
namespace math {
namespace modulu {

  // Zn implementation
  // that can be on top of any integral type T that supports the following operations: + - % *
  // overflow of T will not occure for any operation if n<=sqrt(T::max_value)
  // without the * operation overflow will never occure if n<=T::max_value/2
  template<typename T, T n>
class mod
{
public:
  typedef T integer_type;
  
  // scalar construction
  constexpr mod() : val() {}
  constexpr mod(const T& v) : val(v) {}
  constexpr mod(T&& v) : val(v) {}
  
  // copy & move - from any explicitly convirtible field type - but that uses the same modulu limit
  template<typename OT, OT m>
  constexpr mod(const mod<OT,m>& o) : val((OT)o) { static_assert(n==m, "copy construction modulus from a different modulus"); } // copy constructor
  template<typename OT, OT m>
  constexpr mod(mod<OT, m>&& o) : val(std::move((OT)o)) { static_assert(n==m, "move construction of modulus from a different modulus"); } // move constructor
  
  mod<T,n>& operator=(mod<T,n>& o) { 
      val = o.val; 
      return *this; 
  };
  mod<T,n>& operator=(mod<T,n>&& o) { 
    val = std::move(o.val); 
    return *this; 
  }
  
  // explicit conversion back to the integer type
  explicit constexpr operator const T() { return val; }
    
  // modulu assignment operations
  constexpr mod<T,n>& operator+=(const mod<T,n>& o) {
    val = (val+o.val)%n;
    return *this;
  }
  constexpr mod<T,n>& operator-=(const mod<T,n>& o) {
    val = (n-o.val+val)%n;
    return *this;
  }
  constexpr mod<T,n>& operator*=(const mod<T,n>& o) {
    val = (val*o.val)%n;
    return *this;
  }
private:
  T val;
};

// modulu operations
template<typename T, T n>
constexpr mod<T,n> operator+(const mod<T,n>& lhs, const mod<T,n>& rhs) {
  auto res = lhs;
  return res+=rhs;
}

template<typename T, T n>
constexpr mod<T,n> operator-(const mod<T,n>& lhs, const mod<T,n>& rhs) {
  auto res = lhs;
  return res-=rhs;
}

template<typename T, T n>
constexpr mod<T,n> operator*(const mod<T,n>& lhs, const mod<T,n>& rhs) {
  auto res = lhs;
  return res*=rhs;
}

} /* namespace modulu */
} /* namespace math */
} /* namespace lee */

#endif // MODULU_H
