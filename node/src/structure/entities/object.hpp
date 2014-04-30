#ifndef __P2PSN_OBJECT_H
#define __P2PSN_OBJECT_H

#include <string>

namespace p2psn {
	namespace entities {
		
		class object_id;
		class object;
		class object_reference;
		
		typedef std::string object_id; // TODO perhaps a uuid will be better, or a combination of uuid with some more information
		
		class object {
			public:
				object_id id;
				int version;
				
				contact source; // The contact that created this object
				
				object_reference type; // reference the type object this object belongs too
				object_reference preferred_view; // reference to the preferred view used to render this object
				
				std::string content; // TODO: perhaps a buffer will be better for performance, but keeping this a string will make this more language portable
		};
		
		class object_reference {
			object_id id;
		};
	} // namespace entities
} // namespace p2psn

#endif // __P2PSN_OBJECT_H
