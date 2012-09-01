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

			template<typename U>
			static std::string serialize(const U& o) {
				cppcms::json::value v;
				
				v.set_value(o);

				return serialize(v);
			}

			static cppcms::json::value deserialize(const std::string& s) {
				cppcms::json::value v;

				v.load(std::istringstream(s), true);

				return v;
			}

			template<typename U>
			static U deserialize(const std::string& s) {
				cppcms::json::value v = deserialize(s);

				return v.get_value<U>();
			}
		};

		/**
		 * perform serialization on the given obejects
		 *
		 * The general version uses boost serialization library
		 */		
		template<typename T>
		struct serialization {
			static std::string serialize(const T& value) {
				std::ostringstream output_stream;
				boost::archive::text_oarchive output_archive(output_stream);

				output_archive << value;

				return output_stream.str();
			}
			static T deserialize(const std::string& str) {
				T value;

				std::istringstream input_stream(str);
				boost::archive::text_iarchive input_archive(input_stream);
		
				input_archive >> value;

				return value;
			}
		};

	} // namespace utils
} // namespace p2psn

#endif // __SERIALIZATION_HPP
