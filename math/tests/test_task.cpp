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

#include "test_task.h"

std::ostream& operator<< (std::ostream& os, lee::tests::test_task& t){
    using namespace std::chrono;
    
  os << t.name() << "...";
  
  bool success = true;
  auto start = std::chrono::monotonic_clock::now();
  
  try {
    success = t();  
  }
  catch(...) {
    success = false;
//    auto ex = std::current_exception();
    
   // os << ex.what();
  }
  
  auto end = std::chrono::monotonic_clock::now();
  
  os 
    //<< "(" << (end-start).time_since_epoch() << ") "
    << (success?"Passed":"Failed");
    
   return os;
  }
