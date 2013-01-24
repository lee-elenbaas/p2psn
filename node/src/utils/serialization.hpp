/**
 * serialization tools base on the json serialization structure
 */
#ifndef __SERIALIZATION_HPP
#define __SERIALIZATION_HPP

#include <string>

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
		 * perform serialization of other types using json values
		 */
		template<typename T>
		struct serialization {
			static std::string serialize(const T& o) {
				cppcms::json::value v(o);
				
				if (v.is_undefined())
					SDEBUG("placing serialized value: undefined");
				else
					SDEBUG("placing serialized value");
				
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
