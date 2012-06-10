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

// TODO: convert the work to use a tuple of n F's

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
	constexpr F operator()(const F& scalar) { return eval_scalar(scalar, 0); }

	// math operations
	constexpr full_polynomial<F>& operator+=(const full_polynomial<F>& o) { return add_poly(o, 0); }
	full_polynomial<F>& operator-=(const full_polynomial<F>& o) {
		for (int i=min(_coefficients.size(), o._coefficients.size();i>=0;--i)
			_coefficients[i] -= o._coefficients[i];
		for (int i=_coefficients.size();i<o._coefficients.size();++i)
			_coefficients.push_back(o._coefficients[i]);
	}
private:
	std::vector<F> _coefficients;
	
	constexpr F eval_scalar(const F& scalar, const int level) {
	  return (level >= _coefficients.size())?F():_coefficients[level]+scalar*eval_scalar(scalar, level+1);
	}
	constexpr full_polynomial<F>& add_poly(const full_polynomial<F>& o, const int level) {
	  return (level >= o._coefficients.size())? *this : std::pair<full_polynomial<F>&, F>(_coeficients[level] += o._coefficients[i], add_poly(o, level+1)).second;
	}
};

full_polynomial<F> operator+(const full_polynomial<F>& lhs, const full_polynomial<F>& rhs) { return full_polynomial<F>(lhs)+=rhs; }
full_polynomial<F> operator-(const full_polynomial<F>& lhs, const full_polynomial<F>& rhs) { return full_polynomial<F>(lhs)+=rhs; }

} /* namespace polynomial */
} /* namespace math */
} /* namespace lee */

#endif // FULL_POLYNOMIAL_H
