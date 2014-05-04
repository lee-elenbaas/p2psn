#include "object.hpp"

namespace p2psn {
	namespace entities {

		//////////////// object_id /////////////////////////////

		inline identifier object_id::normalized() {
			return source_uri + sid; // TODO: clean up the normalized string so it become a valid JS/Angular identifier
		}
		
		/////////////// object_view ///////////////////

		inline string object_view::directiveName() {
			return id.normalized();
		}
		
		inline json object_view::directiveObject() {
			return content;
		}
		
	} // namespace entities
} // namespace p2psn
