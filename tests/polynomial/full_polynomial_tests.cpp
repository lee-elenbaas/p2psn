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

#include "full_polynomial_tests.h"
#include "../../polynomial/full_polynomial.h"
#include "../../polynomial/full_polynomial_stream_traits.h"

    std::string lee::tests::math::polynomial::full_polynomial_ctr_test::name() {
      return "full_polynomial#ctor";
    }

bool lee::tests::math::polynomial::full_polynomial_ctr_test::operator()() {
  using lee::math::polynomial::full_polynomial;
  
    full_polynomial<int> p1{1,0,4}; // initialization list
    full_polynomial<int> p2(5); // scalar
    full_polynomial<int> p3 = 7; // scalar
    full_polynomial<int> p4; // zero
    full_polynomial<int> p5 = p1; // copy
    
    return true;
}
