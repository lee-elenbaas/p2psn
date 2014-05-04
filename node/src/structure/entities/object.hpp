#ifndef __P2PSN_OBJECT_H
#define __P2PSN_OBJECT_H

#include "primitives.hpp"

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
		
		//////////////// object_id /////////////////////////////

		class object_id {
			private:
				uri source_uri; // TODO: perhaps forcing this to be email will be cleaner in the long run
				uuid sid;
			public:
				identifier normalized();
		};
		
		//////////////// object /////////////////////////////

		class object {
			private:
				object_id id;
				integer version;
				
				object_reference<contact> source; // The contact that created this object
				
				object_reference<object_type> type; // the type object belongs too
				object_reference<object_view> preferred_view; // the preferred view used to render this object in this p2psn profile (TODO: perhaps this information should sit somewhere inside the profile)
				
			protected:
				buffer content; // TODO: perhaps a buffer will be better for performance, but keeping this a string will make this more language portable
		};
		
		//////////////// object_reference //////////////////
		
		namespace {
			class object_reference_imp { // TODO: perhaps this should become the base class for object as well
				private:
					object_id id;
			}
		}
		
		template<Type>
		class object_reference : public object_reference_imp {
		};
		
		//////////////// object_type ////////////////
		
		class object_type : public object {
			private:
				object_reference<object_view> recomended_view; // the recommended view for objects of this type
		};
		
		/////////////// object_view ///////////////////
		
		class object_view : public object {
			public:
				string directiveName();
				json directiveObject();
		};
		
	} // namespace entities
} // namespace p2psn

#endif // __P2PSN_OBJECT_H
