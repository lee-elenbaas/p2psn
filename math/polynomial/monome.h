/******************************
 * A single monome with all its suppport operations
 *****************************/
#ifndef FULL_POLYNOMIAL_H
#define FULL_POLYNOMIAL_H

namespace lee {
	namespace math {
		namespace polynomial {
			
			template<typename Field>
			class traits;
			
			/***************
			 * Class for handling a single monome
			 **************/
			template<typename Field, typename FieldTraits = traits<Field>, typename Counter = int, Counter level>
			class monome;
			
			template<typename Field, typename FieldTraits>
			class sparse_polynomial;
			
			template<typename Field>
			class traits {
				public:
					Field zero() { return Field(0); }
					Field one() { return Field(1); }
				
					void add_into(Field& lhs, const Field& rhs) { lhs += rhs; }
					Field multiply(const Field& lhs, const Field& rhs) { return lhs*rhs; }

					template<typename Counter>
					Field power(const Field& base, Counter level) {
						Field result = one();
						
						for(;level > 0;--level)
							result *= base;
							
						return result;
					}
			};
			
			template<typename Field, typename FieldTraits, typename Counter, Counter level>
			class monome {
				private:
					Field _value;
				public:
					template<Counter olevel = level>
					typedef monome<Field, FieldTraits, Counter, olevel> Monome;

					explicit monome(Field value)
						:_value(value)
						{ }
					
					public Monome& operator+=(const Monome& other) {
						FieldTraits.add_into(_value, other._value);
						return *this;
					}
					
					template<Counter oLevel>
					friend Monome<level*olevel> operator*(const Monome& lhs, const Monome<oLevel>& rhs);
					
					Field operator(const Field& scalar) {
						return FieldTraits.power(scalar, level);
					}
			};			

			template<typename Field, typename FieldTraits, typename Counter, Counter lhsLevel, Counter rhsLevel>
			monome<Field, FieldTraits, Counter, lhsLevel*rhsLevel> operator*(const monome<Field, FieldTraits, Counter, lhsLevel>& lhs, const monome<Field, FieldTraits, Counter, rhsLevel>& rhs) {
				return monome<Field, FieldTraits, Counter, lhsLevel*rhsLevel>(FieldTraits.multiply(lhs._value, rhs._value));
			}
		}
	}
}

#endif
