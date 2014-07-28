#include "object.hpp"

namespace p2psn {
	namespace entities {

		//////////////// object_id /////////////////////////////

		inline const identifier object_id::normalized() const {
			return source_uri + sid; // TODO: clean up the normalized string so it become a valid JS/Angular identifier
		}

		/////////////// object ///////////////////
		
		inline const buffer& object::content() const {
			return _content;
		}
		
		inline const integer& object::version() const {
			return _version;
		}

		inline const crypto_signature& object::signature() const {
			return _signatue;
		}
		
		/////////////// object_view ///////////////////

		inline const string object_view::directiveName() const {
			return id().normalized();
		}
		
		inline const json object_view::directiveObject() const {
			return _content;
		}
		
	} // namespace entities
} // namespace p2psn
