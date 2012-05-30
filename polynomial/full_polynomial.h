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

template<typename F>
// F should have field semantics: supports operators + * and has zero in the form F()
class full_polynomial {
public:
	typedef F Field_Type;

	// polynom construction
	constexpr full_polynomial() : _coefficients({}) {} // when c++11 will be working completely: full_polynomial({}) {}
	constexpr full_polynomial(const F& scalar) : _coefficients({scalar}) {} // when c++11 will be working completely: full_polynomial({scalar}) {}
	constexpr full_polynomial(std::initializer_list<F> coefficients) : _coefficients(coefficients) {}
	
	// destruction
	~full_polynomial() = default;
	
	// copy
	constexpr full_polynomial(const full_polynomial<F>& other) : _coefficients(other._coefficients) {}
	full_polynomial<F>& operator=(const full_polynomial<F>& other) { _coefficients = other._coefficients; return *this; }
	
	// move
	constexpr full_polynomial(full_polynomial<F>&& other) : _coefficients(std::move(other._coefficients)) {}
	full_polynomial<F>&& operator=(full_polynomial<F>&& other) { _coefficients = std::move(other._coefficients); return *this; }
	
	// accessor
	constexpr const std::vector<const F> get_coefficients() const { return _coefficients; }
	
	// Scalar assignment
	constexpr F operator()(const F& scalar) { return eval(scalar, 0); }
private:
	std::vector<F> _coefficients;
	
	constexpr F eval(const F& scalar, const int level) {
	  return (level >= _coefficients.size())?F():_coefficients[level]+scalar*eval(scalar, level+1);
	}
};

} /* namespace polynomial */
} /* namespace math */
} /* namespace lee */

#endif // FULL_POLYNOMIAL_H
