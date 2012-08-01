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

		class enum split_options {
			include_all = 0,
			avoid_filled_match = 1 << 0,
			avoid_empty_match = 1 << 2,
			avoid_filled_between_match = 1 << 3,
			avoid_empty_between_match = 1 << 4
		};

		///
		/// Match an expression \a r against text \a s
		/// Return a list of strings between the matches
		///
		template<typename 
		std::vector<std::string> regex_split(std::string const &s,Regex const &r,split_options options = split_options::include_all, int flags = 0) {
			std::vector<std::string> split;

			std::vector<std::pair<int,int> > offsets;

			bool res = r.match(s.c_str(),s.c_str()+s.size(),offsets,regex_flags);
	
			if (!res || offsets.empty() || offsets[0].first == -1)
				///
				/// no match = no split
				///
				split.push_back(s);
			}
			else { 
				int prev_index = 0;
				
				for(auto match : offsets) {
					if (prev_index == match.first) {
						if ((options & split_options::avoid_empty_between_match) == 0)
							split.push_back("");
					}
					else {
						if ((options & split_options::avoid_empty_between_match) == 0)
							split.push_back(s.substr(prev_index, match.first - prev_index));
					}

					if (match.first == match.second) {
						if ((options & split_options::avoid_empty_match) == 0)
							split.push_back("");
					}
					else {
						if ((options & split_options::avoid_empty_match) == 0)
							split.push_back(s.substr(match.second - match.first));
					}

					prev_index = match.second;
				}

				if (prev_index == s.size()) {
					if ((options & split_options::avoid_empty_between_match) == 0)
						split.push_back("");
				}
				else {
					if ((options & split_options::avoid_empty_between_match) == 0)
						split.push_back(s.substr(prev_index));
				}
			}
	
			return split;
		}

	} // namespace utils
} // namespace p2psn

#endif // __REGEX_UTILS_H
