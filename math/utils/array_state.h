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


#ifndef ARRAY_STATE_H
#define ARRAY_STATE_H

#include <array>

template<typename T, size_t w>
class array_state
{
public:
  typedef T value_type;
  constexpr const size_t width = w;
  typedef std::array<T, w> state_type;
 
  ~array_state() = default;
 
  template<typename F>
  array_state<T,w>& parallel_operation(F f) {
    return parallel_operation<T, w, F, 0>(*this, f);
  }
  template<typename F, size_t i>
  friend
  array_state<T,w>& parallel_operation(array_state<T,w>&, F f);
protected:
  state_type _state;
};

template<typename T, size_t w, typename F, size_t i>
array_state<T,w>& parallel_operation(array_state<T,w>& o, F f) {
  return (std::make_pair(o.state = f(get<i>(o._state), parallel_operation<T, w, F, i+1>(o, f))).second;
}

#endif // ARRAY_STATE_H
