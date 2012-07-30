
#include "locale_matching.h"
#include <booster/regex.h>
#include <vector>

using namespace p2psn::utils;
using namespace std;
using namespace cppcms::json;

namespace {
	using booster::regex;
	
	regex any_encoding("^$|\\*");
	regex any_encoding("^$|\\*");

	regex qvalue("([^ ]*)(;q=([01](\\.[0-9]+)?))");

	list<pair<string, float>> get_qvalue_list(std::string value)
	{
		list<pair<string, float>> list;

		smatch match_info;

		if (regex_match(value, match_info, qvalue)) {
			
		}
		
		return list;
	}
}

string best_match_locale(const string& requested_languages, const string& accepted_encoding, const array& supported_locales)
{
	
	bool any_encoding = any_encoding.match(accepted_encoding);
	bool any_language = any_language.match(requested_languages);
}


