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

#ifndef MOD_STREAM_TRAITS_H
#define MOD_STREAM_TRAITS_H

#include <ostream>
#include "mod.h"

namespace lee {
namespace math {
namespace modulu {

  class mod_stream_traits;
  class unsupported_mod_stream_traits_exception;
  
enum class mod_format : long {
  value_only,
  modulu_only_short,
  modulu_only_long,
  modulu_only_clean,
  value_and_modulu_short,
  value_and_modulu_long
};

std::ostream& operator<< (std::ostream&, mod_format);
 
class mod_stream_traits {
  mod_stream_traits(mod_format f) : _format(f) { }
  
  friend inline std::ostream& operator<< (std::ostream&, mod_format);

  template<typename T, T n>
  friend std::ostream& operator<< (std::ostream& os, const mod<T, n>& m) {
    mod_stream_traits f = os.iword(_xalloc);
    
    switch (f._format) {
      case mod_format::modulu_only_clean:
	return os << n;
      case mod_format::modulu_only_short:
	return os << '(' << n << ')';
      case mod_format::modulu_only_long:
	return os << "(mod " << n << ')';
      case mod_format::value_only:
	return os << (T)m;
      case mod_format::value_and_modulu_short:
	return os << (T)m << " (" << n << ')';
      case mod_format::value_and_modulu_long:
	return os << (T)m << " (mod" << n << ')';
      default:
	throw unsupported_mod_stream_traits_exception(f);
    }
  }
private:
  mod_stream_traits(long v) : _format(v?(mod_format)v:mod_format::value_and_modulu_short) { }
  
  mod_format _format;
  static const int _xalloc;
};

class unsupported_mod_stream_traits_exception : public std::exception {
public:
  unsupported_mod_stream_traits_exception(const mod_stream_traits& s) : traits(s) { }

  const mod_stream_traits traits;
};

} /* namespace modulu */
} /* namespace math */
} /* namespace lee */

#endif // MOD_STREAM_TRAITS_H
