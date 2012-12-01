/**
 * cryptographic tools used by p2psn
 *
 * providing easier to user API over the cryptografic tools cppcms provides
 */
#ifndef __CRYPTO_H
#define __CRYPTO_H

#include <cppcms/crypto.h>
#include <booster/backtrace.h>
#include <string>
#include <ostream>

namespace p2psn {
	namespace utils {

		typedef std::string (*hash_function_t)(const std::string&);

		enum class hash_algorithm : int {
			illegal = 0,
			md5,
			sha1
		};

		hash_algorithm parse_hash_algorithm(const string&);
		constexpr hash_algorithm parse_hash_algorithm(const char * const str) {
			return	  std::strcmp(str, "md5") == 0 ? hash_algorithm::md5
				: std::strcmp(str, "sha1") == 0 ? hash_algorithm::sha1
				: hash_algorithm::illegal;
		}

		std::ostream& operator<<(std::ostream&, hash_algorithm);
		std::istream& operator>>(std::istream&, hash_algorithm&);

		class bad_hash_algorithm : public booster::bad_cast {
		public:
			bad_hash_algorithm(); 
			bad_hash_algorithm(std::string const &s);
			bad_hash_algorithm(std::string const &s,hash_algorithm actual);

			virtual ~bad_hash_algorithm() throw();
			virtual const char* what() const throw();
		private:
			std::string msg_;
		 };

		/**
		 * perform signature on the given strings
		 */		
		class signature {
		public:
			static std::string md5(const std::string&);
			static std::string sha1(const std::string&);

			constexpr static hash_function_t hash_function(hash_algorithm algo) {
				return	  (algo == hash_algorithm::md5) ? &md5
					: (algo == hash_algorithm::sha1) ? &sha1
					: throw bad_hash_algorithm("unsupported hash algorithm", algo);
			}

			static std::string hash(hash_algorithm, const std::string&);
		private: // TODO: move generate to be templated - in order to support hmac usage as well
			static std::string generate(std::unique_ptr<cppcms::crypto::message_digest>, const std::string&);
		};

	} // namespace utils
} // namespace p2psn

#endif // __CRYPTO_H
