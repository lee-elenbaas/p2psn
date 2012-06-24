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


#ifndef ARRAY_OPERATIONS_H
#define ARRAY_OPERATIONS_H

#include <array>

namespace lee {
  namespace utils {

    // Apply the given function object to every element in the array
    // const Function& f	- is the function object that should have an operator() defined for every type in the tuple, each should return a value
    // const std::array<_Element, sw> a	- The array to perform the operations on
    // returns an array of all the results of activating the function on the array elements
    template<typename Function, typename _Element, size_t w>
    constexpr
    auto apply_parallel(const Function& f, const std::array<_Elements, w>& a) -> std::array<decltype(f(get<0>(a))), w>
    {
      return apply_parallel<0, w, 0>(f, a, std::array<decltype(f(get<0>(a))), w>());
    }

    // Apply the given function object to every element in the array
	// 
    // const Function& f	- is the function object that should have an operator() defined for every type in the tuple, each should return a value
    // const std::array<_Element, sw> a	- The array to perform the operations on its elements.
	// const std::array<_Result, tw> r	- The array to store the results into.
	// size_t sb	- the index to start passing over the elements from
	// size_t se	- the index past the last element to go over
	// size_t tb	- the index to to place the result of the first element on in the result array
    // returns an array of all the results of activating the function on the array elements
    template<size_t sb, size_t se, size_t tb = 0, typename Function, typename _Element, size_t sw, typename _Result, size_t tw>
    constexpr
    std::array<_Result, tw> apply_parallel(const Function& f, const std::array<_Elements, sw>& s, std::array<_Result, tw>& r)
    {
      return std::make_pair(r[tb] = f(get<sb>(s)), apply_parallel<sb+1, se, tb+1>(f, s, r)).second;
    }
    template<size_t se, size_t tb, typename Function, typename _Element, size_t sw, typename _Result, size_t tw>
    constexpr
    std::array<_Result, tw> apply_parallel<se>(const Function& f, const std::array<_Elements, sw>& s, std::array<_Result, tw>& r)
    {
      return r;
    }

    // Apply the given function object to every element in the array
    // const Function& f - is the function object that should have an operator() defined for every type in the tuple, each should return a value
    // const std::array<_Element, sw> a	- The array to perform the operations on its elements.
    // returns an array of all the results of activating the function on the array elements
    template<typename Function, typename _Element, size_t w>
    auto apply_forward(const Function& f, const std::array<_Elements, w>& a) -> std::array<decltype(f(get<0>(a))), w>
    {
      return apply_forward(f, a, 0, w, 0, std::array<decltype(f(get<0>(a))), w>());
    }

    // Apply the given function object to every element in the array
    // const Function& f - is the function object that should have an operator() defined for every type in the tuple, each should return a value
    // const std::array<_Element, sw> a	- The array to perform the operations on its elements.
	// const std::array<_Result, tw> r	- The array to store the results into.
	// size_t sb	- the index to start passing over the elements from
	// size_t se	- the index past the last element to go over
	// size_t tb	- the index to to place the result of the first element on in the result array
    // returns an array of all the results of activating the function on the array elements
    template<typename Function, typename _Element, size_t sw, typename _Result, size_t tw>
    std::array<_Result, tw> apply_forward(const Function& f, const std::array<_Elements, sw>& a, size_t sb, size_t se, size_t, tb, std::array<_Result, tw>& r)
    {
	  for(;sb < se;++sb,++tb)
		r[tb]=f(a[sb]);
		
      return apply_forward(f, a, 0, w, 0, std::array<decltype(f(get<0>(a))), w>());
    }
	
  } /* namespace utils */
} /* namespace lee */

#endif // ARRAY_OPERATIONS_H
