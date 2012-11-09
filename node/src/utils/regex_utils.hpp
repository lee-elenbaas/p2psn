/**
 * cryptographic tools used by p2psn
 *
 * providing easier to user API over the cryptografic tools cppcms provides
 */
#ifndef __REGEX_UTILS_H
#define __REGEX_UTILS_H

#include <booster/regex.h>
#include <vector>
#include <sstream>
#include "log.hpp"
#include <iostream>

namespace p2psn {
	namespace utils {

		enum class split_options : int;

		split_options operator&(split_options lhs, split_options rhs) {
			return static_cast<split_options>(static_cast<int>(lhs) & static_cast<int>(rhs));
		}

		split_options operator|(split_options lhs, split_options rhs) {
			return static_cast<split_options>(static_cast<int>(lhs) | static_cast<int>(rhs));
		}

		enum class split_options {
			include_all = 0,
			avoid_filled_match = 1 << 0,
			avoid_empty_match = 1 << 2,
			avoid_filled_between_match = 1 << 3,
			avoid_empty_between_match = 1 << 4,

			avoid_matchs = avoid_empty_match | avoid_filled_match,
			avoid_between_matchs = avoid_filled_between_match | avoid_empty_between_match,
			avoid_emptys = avoid_empty_match | avoid_empty_between_match,
			not_set = 0
		};

		///
		/// Match an expression \a r against text \a s
		/// Return a list of strings between the matches
		///
		template<typename Regex>
		std::vector<std::string> regex_split(std::string const &s,Regex const &r,split_options options = split_options::include_all, int regex_flags = 0) {
			std::vector<std::string> split;

			std::vector<std::pair<int,int> > offsets;

			bool res = r.match(s.c_str(),s.c_str()+s.size(),offsets,regex_flags);
	
			if (!res || offsets.empty() || offsets[0].first == -1) {
				///
				/// no match = no split
				///
				split.push_back(s);
			}
			else { 
				int prev_index = 0;
				
				for(auto match : offsets) {
					if (prev_index == match.first) {
						if ((options & split_options::avoid_empty_between_match) == split_options::not_set)
							split.push_back("");
					}
					else {
						if ((options & split_options::avoid_filled_between_match) == split_options::not_set)
							split.push_back(s.substr(prev_index, match.first - prev_index));
					}

					if (match.first == match.second) {
						if ((options & split_options::avoid_empty_match) == split_options::not_set)
							split.push_back("");
					}
					else {
						if ((options & split_options::avoid_filled_match) == split_options::not_set)
							split.push_back(s.substr(match.second - match.first));
					}

					prev_index = match.second;
				}

				if (prev_index == static_cast<int>(s.size())) {
					if ((options & split_options::avoid_empty_between_match) == split_options::not_set)
						split.push_back("");
				}
				else {
					if ((options & split_options::avoid_filled_between_match) == split_options::not_set)
						split.push_back(s.substr(prev_index));
				}
			}
	
			return split;
		}

		template<typename Regex>
		std::string lee_regex_replace(std::string original, Regex regex, std::string replace) {
			std::cout << "in \"" << original << "\" replace \"" << regex << "\" with \"" << replace << "\"" << std::endl;
			auto splitted = regex_split(original, regex, split_options::avoid_matchs);

			std::cout << "splitted " << splitted << std::endl;
			std::ostringstream result;

			bool first = true;
			for(auto no_match : splitted) {
				if (!first)
					result << replace;
				else
					first = false;

				result << no_match;
			}

			return result.str();
		}

		template<typename Regex>
		inline std::string pattern_to_regex(const std::string& pattern) {
			std::cout << "skip" << std::endl;
			return pattern;
//			std::string reg = lee_regex_replace(pattern, Regex("\\."), "\\."); // replace all . in the pattern with \.
//			reg = lee_regex_replace(reg, Regex("\\?"), "."); // replace all pattern ? with regex .
//			reg = lee_regex_replace(reg, Regex("\\*"), ".*"); // replace all patten * with regex .*
//			return reg;
		}

	} // namespace utils
} // namespace p2psn

#endif // __REGEX_UTILS_H
