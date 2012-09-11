/**
 * cryptographic tools used by p2psn
 *
 * providing easier to user API over the cryptografic tools cppcms provides
 */
#ifndef __SERIALIZATION_HPP
#define __SERIALIZATION_HPP

#include <string>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <sstream>
#include <cppcms/json.h>

namespace p2psn {
	namespace utils {

		template<typename T>
		struct serialization;

		/**
		 * perform serialization of json values
		 */
		template<>
		struct serialization<cppcms::json::value> {
			static std::string serialize(const cppcms::json::value& v) {
				return v.save();
			}
			static cppcms::json::value deserialize(const std::string& s) {
				cppcms::json::value v;
				std::istringstream is(s);

				v.load(is, true);

				return v;
			}
		};

		/**
		 * perform serialization of using json values
		 */
		template<typename T>
		struct serialization {
			static std::string serialize(const T& o) {
				cppcms::json::value v;
				
				v.set_value(o);

				return serialization<cppcms::json::value>::serialize(v);
			}

			static T deserialize(const std::string& s) {
				cppcms::json::value v = serialization<cppcms::json::value>::deserialize(s);

				return v.get_value<T>();
			}
		};

	} // namespace utils
} // namespace p2psn

#endif // __SERIALIZATION_HPP
