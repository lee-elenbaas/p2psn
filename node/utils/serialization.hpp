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

namespace p2psn {
	namespace utils {

		/**
		 * perform serialization on the given obejects
		 *
		 * The general version uses boost serialization library
		 */		
		template<typename T>
		struct serialization {
			std::string serialize(const T& value) {
				std::ostringstream output_stream;
				boost::archive::text_oarchive output_archive(output_stream);

				output_archive << value;

				return output_stream.str();
			}
			T deserialize(const std::string& str) {
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
