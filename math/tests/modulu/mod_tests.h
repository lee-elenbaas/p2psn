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


#ifndef MOD_TESTS_H
#define MOD_TESTS_H

#include "../test_task.h"

namespace lee {
namespace tests {
namespace math {
namespace modulu {

  struct mod_ctr_test : public lee::tests::test_task {
    std::string name();
    bool operator()();
  };

  struct mod_stream_test : public lee::tests::test_task {
    std::string name();
    bool operator()();
  };

  } /* namespace modulu */
} /* namespace math */
} /* namespace tests */
} /* namespace lee */

#endif // MOD_TESTS_H
