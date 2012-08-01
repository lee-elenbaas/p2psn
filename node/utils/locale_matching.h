/**
 * cryptographic tools used by p2psn
 *
 * providing easier to user API over the cryptografic tools cppcms provides
 */
#ifndef __LOCALE_MATCHING_H
#define __LOCALE_MATCHING_H

#include <string>
#include <booster/locale.h>
#include <cppcms/json.h>

namespace p2psn {
	namespace utils {

		std::string best_match_locale(const std::string& requested_languages, const std::string& accepted_encoding, const cppcms::json::array& supported_locales);

	} // namespace utils
} // namespace p2psn

#endif // __LOCALE_MATCHING_H
