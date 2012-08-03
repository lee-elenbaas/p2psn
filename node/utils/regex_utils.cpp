
#include "regex_utils.h"

using namespace p2psn::utils;

split_options operator&(split_options lhs, split_options rhs) {
	return static_cast<split_options>(static_cast<int>(lhs) & static_cast<int>(rhs));
}

split_options operator|(split_options lhs, split_options rhs) {
	return static_cast<split_options>(static_cast<int>(lhs) | static_cast<int>(rhs));
}

