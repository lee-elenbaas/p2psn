/**
 * cryptographic tools used by p2psn
 *
 * providing easier to user API over the cryptografic tools cppcms provides
 */
#ifndef __REGEX_UTILS_H
#define __REGEX_UTILS_H

#include <booster/regex.h>
#include <vector>

namespace p2psn {
	namespace utils {

		///
		/// Match an expression \a r against text \a s
		/// Return a list of strings between the matches
		///
		template<typename 
		std::vector<std::string> regex_split(std::string const &s,Regex const &r,int flags = 0) {
			std::vector<std::string> split;
			smatch match;

			if (regex_match(s, match, r, flags)) {
			}
			else { // no match = no split
				split.add
			}

		}

	} // namespace utils
} // namespace p2psn

#endif // __REGEX_UTILS_H
