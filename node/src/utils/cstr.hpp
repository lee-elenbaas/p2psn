/**
 * utility functions for c style strings
 */
#ifndef __CSTR_H
#define __CSTR_H

namespace p2psn {
	namespace utils {
		
		namespace {
			constexpr bool cstr_equals_chars(const char * const s1, const char * const s2) {
				return	(*s1 != *s2) ? false
					:	cstr_equals_chars(s1+1, s2+1);
			}
		}
		
		constexpr bool cstr_equals(const char * const s1, const char * const s2) {
			return	(s1 == nullptr && s2 == nullptr) ? true
				:	(s1 == nullptr) ? false
				:	(s2 == nullptr) ? false
				:	(s1 == s2) ? true
				:	cstr_equals_chars(s1, s2);
		}
	}
}

#endif // __CSTR_H
