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


#include "tuple_operations_test.h"
#include <string>
#include "../../utils/tuple_operations.h"

    std::string lee::tests::utils::tuple_operations_test::name() {
      return "tuple_operations#tests";
    }

    namespace {
  using std::string;
  
struct type_name {
  string operator() (int) { return "int"; }
  string operator() (float) { return "float"; }
  string operator() (string) { return "string"; }
};
    }
    
bool lee::tests::utils::tuple_operations_test::operator()() {
  using namespace lee::utils;
  using namespace std;
  
  auto t1 = make_tuple(1,1.5,"hellp");
  auto t1r = apply_parallel(type_name(), t1);
  
  if (get<0>(t1r) != "int")
    return false;
  if (get<1>(t1r) != "float")
    return false;
  if (get<2>(t1r) != "string")
    return false;
  
  return true;
}
