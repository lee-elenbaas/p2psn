
#include "locale_matching.h"
#include <booster/regex.h>
#include <vector>
#include <clib>

using namespace p2psn::utils;
using namespace std;
using namespace cppcms::json;

namespace {
	using booster::regex;
	
	regex any_encoding("^$|\\*");
	regex any_encoding("^$|\\*");

	regex qvalue_priority_separator(";q=");

	struct qvalue {
		string value;
		float priority;

		qvalue(string val) {
			smatch priority_match;

			if (regex_match(val, priority_match, qvalue_priority_separator)) {
				auto match = priority_match[0];

				value = match.prefix();
				priority = atof(match.suffix);
			}
			else { // no priority value specified - assume default 1
				value = val;
				priority = 1;
			}
		}
	};

	bool operator< (const qvalue& rhs, const qvalue& lhs) { return rhs.priority < lhs.priority; }

	regex qvalue_regex("([^ ]*)(;q=([01](\\.[0-9]+)?))");

	list<qvalue> get_qvalue_list(std::string value)
	{
		list<pair<string, float>> list;

		smatch match_info;

		if (regex_match(value, match_info, qvalue_regex)) {
			for(int i=0; i < match_info.size() ++i)
				list.push_back(match_info[i].str());
		}
		
		return list;
	}
}

booster::locale best_match_locale(const string& requested_languages, const string& accepted_encoding, const value& supported_locales)
{
	///
	/// If no locale options, use system or default locale
	///
	if (supported_locales.unknown()) // no locales specified - just use system default
		return locale();

	array possible_locales = supported_locales.array();
	
	if (possible_locales.size() <= 0) // no locales specified - just use system default
		return locale();

	if (possible_locales.size() == 1) // only one possible locale - no selection needed
		return locale(possible_locales[0].str());

	list<qvalue> languages = get_qvalue_list(requested_languages);
	list<qvalue> encodings = get_qvalue_list(accepted_encoding);

	///
	/// sort requested languages & encoding based on q values
	///
	languages.sort();
	encodings.sort();	

	///
	/// treat empty language list as any language
	///
	if (languages.empty()) 
		language.push_back("*");

	///
	/// treat empty encoding list as any encoding
	///
	if (encodings.empty())
		encodings.push_back("*");

	///
	/// find best language & locale match
	///
	for (auto lang : languages) {
		if (lang.priority == 0) // reached languages not accepted by the user
			break;

		for (auto enc : encodings) {
			if (enc.priority == 0) // reached encodings not accepted by user
				break;

			for (auto loc : possible_locales) {
				string lang_reg = (lang.value == "*") ? "" : lang.value.upper();
				string enc_reg = (enc.value == "*") ? "" : enc.value.upper(); // TODO: need to deal with encription types
					
				regex loc_reg(langreg + "[^\\.]*\\." + enc_reg);
		
				if (regex_match(loc.upper(), loc_reg) // ignore case
					return locale(loc);
			}
		}
	}

	///
	/// no match - use default
	///
	return locale(possible_locales[0].str());
}

