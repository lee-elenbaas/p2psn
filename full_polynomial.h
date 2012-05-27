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


#ifndef FULL_POLYNOMIAL_H
#define FULL_POLYNOMIAL_H

#include<vector>

namespace lee {
namespace math {
namespace polynomial {

template<typename F, typename V>
// F should have field semantics
// V should have character somantics
class full_polynomial {
public:
	typedef F Field_Type;
	typedef V Variable_Name_Type;

	constexpr auto get_variable() { return _variable; }
	void set_variable(V variable) { _variable=variable; }
	constexpr const std::vector<const F> get_coefficients() { return _coefficients; }
private:
	V _variable = 'x';
	std::vector<F> _coefficients = {};
};

} /* namespace polynomial */
} /* namespace math */
} /* namespace lee */

#endif // FULL_POLYNOMIAL_H
