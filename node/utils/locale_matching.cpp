
#include "locale_matching.h"
#include <booster/regex.h>

using namespace p2psn::utils;
using std::string;
using namespace cppcms::json;

namespace {
	using booster::regex;
	
	regex language_reg("[^ ][^ ](_[^ ][^ ])?");
}

string best_match_locale(const string& requested_languages, const string& accepted_encoding, const array& supported_locales)
{
	requested_languages.split(" ");
}
