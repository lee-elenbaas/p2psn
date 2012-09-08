/**
 * base 64 encoding
 * taken from: http://www.cplusplus.com/forum/beginner/51572/
 */
#ifndef _BASE64_H_
#define _BASE64_H_
#include <string>

namespace p2psn {
	namespace utils {

		std::string base64_encode(char const* bytes_to_encode, unsigned int len) {
			return base64_encode(reinterpret_cast<unsigned char const*>(bytes_to_encode), len);
		}

		std::string base64_decode(std::string const& s);

		namespace {
			std::string base64_encode_imp(unsigned char const* , unsigned int len);
		}

	} // namespace utils
} // namespace p2psn

#endif // __BASE64_H
