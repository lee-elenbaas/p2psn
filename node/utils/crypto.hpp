/**
 * cryptographic tools used by p2psn
 *
 * providing easier to user API over the cryptografic tools cppcms provides
 */
#ifndef __CRYPTO_H
#define __CRYPTO_H

#include <cppcms/crypto.h>
#include <string>

namespace p2psn {
	namespace utils {

		/**
		 * perform signature on the given strings
		 */		
		class signature {
		public:
			static std::string md5(const std::string&);
			static std::string sha1(const std::string&);
		private: // TODO: move generate to be templated - in order to support hmac usage as well
			static std::string generate(std::auto_ptr<cppcms::crypto::message_digest>, const std::string&);
		};

	} // namespace utils
} // namespace p2psn

#endif // __CRYPTO_H
