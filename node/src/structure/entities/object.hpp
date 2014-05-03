#ifndef __P2PSN_OBJECT_H
#define __P2PSN_OBJECT_H

#include <string>

namespace p2psn {
	namespace entities {
		// id for finding an object in the repository and for identifing it across the p2psn network
		class object_id; 
		
		// base class for all objects
		class object; 
		
		// reference from one object to another
		template<Type>
		class object_reference;
		
		// special types
		class object_type;
		class object_view;
		
		/////////////////////////////////////////////
		
		class object_id {
			public:
				std::string source_uri;
				sts::string sid; // TODO: perhaps a uuid will be better as type
				
				std::string normalized() {
					return source_uri + sid; // TODO: clean up the normalized string so it become a valid JS/Angular identifier
				}
		};
		
		class object : {
			public:
				object_id id;
				int version;
				
				object_reference<contact> source; // The contact that created this object
				
				object_reference<object_type> type; // the type object belongs too
				object_reference<object_view> preferred_view; // the preferred view used to render this object in this p2psn profile (TODO: perhaps this information should sit somewhere inside the profile)
				
				std::string content; // TODO: perhaps a buffer will be better for performance, but keeping this a string will make this more language portable
		};
		
		namespace {
			class object_reference_imp { // TODO: perhaps this should become the base class for object as well
				public:
					object_id id;
			}
		}
		
		template<Type>
		class object_reference : public object_reference_imp {
		};
		
		class object_type : public object {
			public:
				object_reference<object_view> recomended_view; // the recommended view for objects of this type
		};
		
		class object_view : public object {
			public: // TODO: this will contain API for getting the angular directive used for the display, and how to deliver the view object to that directive (or perhaps this will be commmon between all directives)
				directiveName() {
					return id.normalized();
				}
		};
	} // namespace entities
} // namespace p2psn

#endif // __P2PSN_OBJECT_H
