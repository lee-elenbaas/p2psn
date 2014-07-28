#include "repository.hpp"

namespace p2psn {
	namespace repository {
		
		object_repository::object_repository() {
			// TODO:
			// * Load list of objects to load from disk
			// * Load objects from disk
		}
		
		object_repository::~object_repository() {
			// TODO:
			// * Generate new list of objects to load next time
			// * Save the list to the disk
		}
		
		void object_repository::store(object obj) {
			auto id = obj.id().normalized();
			
			auto pos = _objects.find(id);
			
			if (pos != _objects.end()) {
				auto current = *pos;

				if (current.id() != obj.id())
					throw id_conflict_error("Attempt to store a different object with a clashing id");
					
				if (current.version() == obj.version()) {
					if (current.signature() == obj.signature())
						return;
						
					throw version_conflict_error("Same version of the same object with different content");
				}
				
				if (current.version() > obj.version())
					throw store_older_version_error("A newer version of the object already exists in the storage");
					// TODO: need to figure out how to fite injection of false version numbers
			}
			
			_objects[id] = obj;
		}
		
		inline object object_repository::retrieve(const object_id& id) {
			return _objects[id.normalized()];
		}
		
	} // namespace repository
} // namespace p2psn

#endif // __P2PSN_REPOSITORY_H
