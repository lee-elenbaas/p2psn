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


#ifndef FULL_POLINOMIAL_STREAM_TRAITS_H
#define FULL_POLINOMIAL_STREAM_TRAITS_H

#include <ostream>
#include "full_polynomial.h"

namespace lee {
namespace math {
namespace polynomial {

  class polynomial_variable
{
public:
  explicit polynomial_variable(char variable);
  static const char DEFAULT_VARIABLE='x';
  
  friend std::ostream& operator<<  (std::ostream& os, const polynomial_variable & variable);
  
  template<typename F>
  friend std::ostream& operator<<(std::ostream& os, const full_polynomial<F>& polynomial);
private: 
  static const int _xalloc;
  char _variable;
};

} /* namespace polynomial */
} /* namespace math */
} /* namespace lee */

#endif // FULL_POLINOMIAL_STREAM_TRAITS_H
