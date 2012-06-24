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

// TODO: convert the work to use a tuple of n F's

#ifndef FULL_POLYNOMIAL_H
#define FULL_POLYNOMIAL_H

#include<vector>

namespace lee {
namespace math {
namespace polynomial {

template<typename F, size_t l>
class polynomial {
public:
	// polynom construction
	constexpr polynomial() : _coefficients({}) {} // when c++11 will be working completely: full_polynomial({}) {}
	constexpr polynomial(std::initializer_list<F> coefficients) : _coefficients(coefficients) {}
	
	// destruction
	~polynomial() = default;
	
	// copy
	constexpr polynomial(const polynomial<F, l>& other) : _coefficients(other._coefficients) {}
	polynomial<F, l>& operator=(const polynomial<F, l>& other) { _coefficients = other._coefficients; return *this; }
	
	// move
	constexpr polynomial(polynomial<F, l>&& other) : _coefficients(std::move(other._coefficients)) {}
	polynomial<F, l>&& operator=(polynomial<F, l>&& other) { _coefficients = std::move(other._coefficients); return *this; }
	
	// accessor
	constexpr const std::array<const F, l> get_coefficients() const { return _coefficients; }
	
	// Scalar assignment
	constexpr F operator() const (const F& scalar) { return eval_scalar<F, l, 0>(*this, scalar); }
	template<size_t i>
	friend constexpr F eval_scalar(const polynomial<F, l>& F, const F& scalar);
private:
	std::array<F, l> _coefficients;
}

template<typename F, size_t l1, size_t l2>
constexpr auto operator+(const polynomial<F, l1>& lhs, const polynomial<F, l2>& rhs) -> polynomial<F, std::max(l1, l2)> {
	return polynomial<F, std::max(l1, l2)> (lhs._coefficients+rhs._coefficients);
}

template<typename F, size_t l, size_t i>
F eval_scalar(const polynomial<F, l>& p, const F& scalar) {
	return std::get<l>(p._coefficients)+scalar*eval_scalar<F,l,i+1>(f,scalar); // calculation using the representation: ax^2+bx+c=c+x(b+x(a+x*0))
}
template<typename F, size_t l>
F eval_scalar<F,l,l+1>() { return F(); }

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
