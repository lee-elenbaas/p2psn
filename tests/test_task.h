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


#ifndef TEST_TASK_H
#define TEST_TASK_H

#include <string>
#include <ostream>
#include <chrono>
#include <functional>

namespace lee {
namespace tests {

class test_task
{
public:
  friend std::ostream& operator<< (std::ostream&, test_task&);
private:
  std::string name;
  std::unary_function<void,void> tst;
};

} /* namespace tests */
} /* namespace lee */

#endif // TEST_TASK_H
