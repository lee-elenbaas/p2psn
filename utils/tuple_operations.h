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


#ifndef TUPLE_OPERATIONS_H
#define TUPLE_OPERATIONS_H

#include <tuple>

namespace lee {
  namespace utils {

    // Apply the given function object to every element in the tuple
    // const Function& f - is the function object that should have an operator() defined for every type in the tuple, each should return a value
    // const std::tuple<...> t the tuple to perform the operations on
    // returns a tuple of all the results of activating the function on the tuple elements
    template<typename Function, typename _Head, typename... _Tail>
    constexpr
    auto apply_parallel(const Function& f, const std::tuple<_Head, _Tail>& t) -> decltype(std::tuple_cat(std::make_tuple(f(t.head())), apply_parallel(f, t.tail()))))
    {
      return std::tuple_cat(std::make_tuple(f(t.head())), apply_parallel(f, t.tail())));
    }
    template<typename Function>
    constexpr
    std::tuple<> apply_parallel(const Function&, const std::tuple<>& t)
    {
      return t;
    }

    // Apply a carry function to every element in the tuple in turn
    // const Function& f - is the function object to operate with. 
    //		It should have an operator() for every type in the tuple that accepts the element and the carry object from the previous operations
    //		It should return an std::pair with the first part the result of the function, and the second the carry to the next operation
    // const _Carry& c - is the initiall carry object, passed over to the function for the first element
    // returns a std::pair with the first element being the tuple of results, and the second part the carry of the last element
    temlate<typename Function, typename _Carry, typename _Head, typename... _Tail>
    constexpr
    auto apply_carry(const Function&, const _Carry&, const std::tuple<_Head, _Tail>&);

	namespace {
		temlate<typename Function, typename _Result, typename _Carry, typename... _Tail>
		constexpr
		auto _apply_carry_imp_2(const Function& f, _Result& res, const std::pair<std::tuple<_Tail>,_Carry>& t) -> decltype(std::make_pair(std::tuple_cat(std::make_tuple(res), t.first), t.second))
		{
		  return std::make_pair(std::tuple_cat(std::make_tuple(res), t.first), t.second);
		}
		
		temlate<typename Function, typename _Result, typename _Carry, typename... _Tail>
		constexpr
		auto _apply_carry_imp_1(const Function& f, std::pair<_result,_Carry>&& res, const std::tuple<_Tail>& t) -> decltype(_apply_carry_imp_2(f, res.first, apply_carry(f, res.second, r.tail())))
		{
		  return _apply_carry_imp_2(f, res.first, apply_carry(f, res.second, r.tail()));
		}
	}
	
    temlate<typename Function, typename _Carry, typename _Head, typename... _Tail>
    constexpr
    auto apply_carry(const Function& f, const _Carry& c, const std::tuple<_Head, _Tail>& t) -> decltype(_apply_carry_imp_1(f, f(t.head(), c), t.tail()))
    {
      return _apply_carry_imp_1(f, f(t.head(), c), t.tail());
    }
    temlate<typename Function, typename _Carry>
    constexpr
    std::pair<std::tuple<>,_Carry> apply_carry(const Function&, const _Carry& c, const std::tuple<>& t)
    {
      return std::make_pair(t,c);
    }
    
  } /* namespace utils */
} /* namespace lee */

#endif // TUPLE_OPERATIONS_H
