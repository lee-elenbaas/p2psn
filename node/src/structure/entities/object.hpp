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
		template<class Type>
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
				const identifier normalized() const;
		};
		
		//////////////// object /////////////////////////////
		
		namespace {
			class _object_with_id { // TODO: perhaps this should become the base class for object as well
				private:
					object_id _id;
				public:
					_object_with_id(const object_id& id) : _id(id) {} // TODO: fill in other forms of _id construction
					
					const object_id& id() const {
						return _id;
					}
			}
		}

		class object : public _object_with_id {
			private:
				integer _version;
				
				object_reference<contact> _source; // The contact that created this object
				
				object_reference<object_type> _type; // the type object belongs too
				object_reference<object_view> _preferred_view; // the preferred view used to render this object in this p2psn profile (TODO: perhaps this information should sit somewhere inside the profile)
				
			protected:
				buffer _content; // TODO: perhaps a buffer will be better for performance, but keeping this a string will make this more language portable
			public:
				object(const object_id& id) : object_with_id_imp(id) {}
		};
		
		//////////////// object_reference //////////////////
		
		template<Type>
		class object_reference : public _object_with_id {
			private:
				static_assert(std::is_base_of<object, Type>::value, "object_reference must reference object types");
			public:
				object_reference(const object_id& id) : _object_with_id(id) {}
		};
		
		//////////////// object_type ////////////////
		
		class object_type : public object {
			private:
				object_reference<object_view> _recomended_view; // the recommended view for objects of this type
		};
		
		/////////////// object_view ///////////////////
		
		class object_view : public object {
			public:
				const string directiveName() const;
				const json directiveObject() const;
		};
		
	} // namespace entities
} // namespace p2psn

#endif // __P2PSN_OBJECT_H
