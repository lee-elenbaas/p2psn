#ifndef __P2PSN_REPOSITORY_H
#define __P2PSN_REPOSITORY_H

#include "../entities/object.hpp"
#include <map>

namespace p2psn {
	namespace repository {
		
		class object_repository {
			private:
				std::map<identifier, object> _objects;
				
				object retrieve(const object_id& id);
			public:
				object_repository();
				~object_repository();
				
				void store(object obj);
				
				template<class Type>
				Type retrieve(object_reference<Type> ref) {
					return dynamic_cast<Type>(retrieve(ref.id()));
				}
		};
		
	} // namespace repository
} // namespace p2psn

#endif // __P2PSN_REPOSITORY_H
