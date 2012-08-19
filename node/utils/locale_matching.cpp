
#include "locale_matching.hpp"

#include "regex_utils.hpp"
#include <list>
#include <cstdlib>

using namespace p2psn::utils;
using std::string;
using std::list;
using cppcms::json::value;
using std::locale;
using booster::smatch;

namespace {
	using booster::regex;
	
	const string qvalue_priority_separator_str = "\\w*;\\w*q\\w*=\\w*";
	regex qvalue_priority_separator(qvalue_priority_separator_str);

	struct qvalue {
		string value;
		float priority;

		qvalue(string val) {
			auto parts = regex_split(val, qvalue_priority_separator, split_options::avoid_matchs);

			if (parts.size() > 1) {
				value = parts[0];
				priority = atof(parts[1].c_str());
			}
			else { // no priority value specified - assume default 1
				value = val;
				priority = 1;
			}
		}
	};

	bool operator< (const qvalue& rhs, const qvalue& lhs) { return rhs.priority < lhs.priority; }

	regex qvalue_regex("([^ ]*)("+qvalue_priority_separator_str+"([01](\\.[0-9]+)?))");

	list<qvalue> get_qvalue_list(std::string value)
	{
		list<qvalue> list;

		smatch match_info;

		if (regex_match(value, match_info, qvalue_regex)) {
			for(unsigned i=0; i < match_info.size(); ++i)
				list.push_back(match_info[i].str());
		}
		
		return list;
	}
}

string p2psn::utils::best_match_locale(const string& requested_languages, const string& accepted_encoding, const value& supported_locales)
{
	///
	/// If no locale options, use system or default locale
	///
	if (supported_locales.is_undefined()) // no locales specified - just use system default
		return "";

	auto possible_locales = supported_locales.array();
	
	if (possible_locales.size() <= 0) // no locales specified - just use system default
		return "";

	if (possible_locales.size() == 1) // only one possible locale - no selection needed
		return possible_locales[0].str();

	auto languages = get_qvalue_list(requested_languages);
	auto encodings = get_qvalue_list(accepted_encoding);

	///
	/// sort requested languages & encoding based on q values
	///
	languages.sort();
	encodings.sort();	

	///
	/// treat empty language list as any language
	///
	if (languages.empty()) 
		languages.push_back(string("*"));

	///
	/// treat empty encoding list as any encoding
	///
	if (encodings.empty())
		encodings.push_back(string("*"));

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
				string lang_reg = (lang.value == "*") ? "" : lang.value;
				string enc_reg = (enc.value == "*") ? "" : enc.value; // TODO: need to deal with encription types

				// TODO: make matching case insensitive					

				regex loc_reg(lang_reg + "[^\\.]*\\." + enc_reg);
		
				if (regex_match(loc.str(), loc_reg)) // ignore case
					return loc.str();
			}
		}
	}

	///
	/// no match - use default
	///
	return possible_locales[0].str();
}

