#ifndef __P2PSN_PRIMITIVES_H
#define __P2PSN_PRIMITIVES_H

#include <string>

namespace p2psn {
	namespace entities {
		// Primitive types used for storing different types of information
		
		typedef std::string string; // Strings for display
		typedef int integer;
		typedef std::string buffer; // Untyped data
		typedef std::string uuid;
		typedef std::string json; // stringified json/ecmascript object
		typedef std::string identifier; // ecmascript valid identifier
		typedef std::string crypto_key; // RSA key

		typedef std::string uri; // untyped uri
		typedef uri email;
		typedef uri url;
		typedef uri channel; // online p2p channel // TODO: might be better off as a list of connected servers
		
	} // namespace entities
} // namespace p2psn

#endif // __P2PSN_PRIMITIVES_H
