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

#include "mod_tests.h"

#include <sstream>

#include "../../modulu/mod.h"
#include "../../modulu/mod_stream_traits.h"

std::string lee::tests::math::modulu::mod_ctr_test::name()
{
  return "mod#ctor";
}

bool lee::tests::math::modulu::mod_ctr_test::operator()()
{
  using lee::math::modulu::mod;
  
  mod<int,5> m1;
  mod<int,5> m2=5;
  mod<int,5> m3=m2;
  
  mod<long,5> m4 = 6;
  mod<long,5> m5 = m2;
  //mod<long,7> m6 = m4; // error compilation - as expected
  
  m1 = 8;
  m4 = 9;
  m4 = m1;
  m5 = 999999999999999l;
  m1 = m5;
  
  return true;
}

std::string lee::tests::math::modulu::mod_stream_test::name()
{
  return "mod#stream";
}

bool lee::tests::math::modulu::mod_stream_test::operator()()
{
  using namespace lee::math::modulu;
  
  mod<int,5> m1=3;
  mod<int,5> m2=4;
  mod<int,5> m3=-7;

  std::stringstream s;
  
  s << m1;
  
  if (s.str() != "3 (5)")
    return false;
  
  s.str() = "";
  
  s << mod_format::value_only << m2 << ' ' << m1;

  if (s.str() != "4 3")
    return false;
  
return true;
}
