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
				
				// TODO: need to check that new object is indeed a new version of the old object
				// TODO: throw exception if object is not a different version of the same object, or if it is not a newer version
			}
			
			_objects[id] = obj;
		}
		
		inline object object_repository::retrieve(const object_id& id) {
			return _objects[id.normalized()];
		}
		
	} // namespace repository
} // namespace p2psn

#endif // __P2PSN_REPOSITORY_H
