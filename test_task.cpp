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

#include "test_task.h"

  std::ostream& lee::tests::operator<< (std::ostream& os, test_task& tst) {
    using namespace std::chrono;
    
  os << tst.name << "...";
  
  bool success = true;
  auto start = std::chrono::monotonic_clock::now();
  auto end = start;
  
  try {
     tst.tst();  
  }
  catch(...) {
    os << std::current_exception();
  }

  std::chrono::milliseconds duration = end-start;
  os << '(' << duration << ") " << (success?"Passed":"Failed") << std::endl;
  }
