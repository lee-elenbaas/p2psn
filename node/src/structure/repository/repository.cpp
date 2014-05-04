#include "repository.hpp"

namespace p2psn {
	namespace repository {
		
		object_repository::object_repository() {
			// * Load list of objects to load from disk
			// * Load objects from disk
		}
		
		object_repository::~object_repository() {
			// * Generate new list of objects to load next time
			// * Save the list to the disk
		}
		
	} // namespace repository
} // namespace p2psn

#endif // __P2PSN_REPOSITORY_H
