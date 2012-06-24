/*
    Peer 2 Peer Social Network - Infrastracture for big brother free social network.
    Copyright (C) 2012  Lee Elenbaas - lee [dot] elenbaas [at] gmail [dot] com

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


#include "full_polynomial_stream_traits.h"

namespace lee {
namespace math {
namespace polynomial {

  const int polynomial_variable::_xalloc = std::ios_base::xalloc();
  
  std::ostream& operator<<(std::ostream& os, const polynomial_variable& variable) {
    os.iword(polynomial_variable::_xalloc) = variable._variable;
    
    return os;
  }

  polynomial_variable::polynomial_variable(char variable) : _variable(variable?variable:DEFAULT_VARIABLE) {}
  
  template<typename F>
  std::ostream& operator<<(std::ostream& os, const full_polynomial<F>& polynomial) {
    if (!os.good())
      return os;
    
    polynomial_variable variable(os.iword(polynomial_variable::_xalloc));
    char power='^';
    char multiply='*';
    
    bool generatedSomeOutput = false;
    int level = 0;
    
    for(F coefficient : polynomial.get_coeficients()) {
      if (coefficient) {
	if (generatedSomeOutput)
	  os << std::showpos;
      
	os<<coefficient;
      
	if (level) {
	  if (multiply)
	    os << multiply;
	
	  os << variable._variable;
	
	  if (level > 1)
	    os << power << level;
	}
	
	generatedSomeOutput = true;
      }
      
      ++level;
    }
    
    if (!generatedSomeOutput)
      os << F();
  }
  
  } /* namespace polynomial */
} /* namespace math */
} /* namespace lee */
