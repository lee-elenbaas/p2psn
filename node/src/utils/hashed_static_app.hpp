#ifndef __P2PSN_HASHED_STATIC_APP_H
#define __P2PSN_HASHED_STATIC_APP_H

#include "../node/shared/base_app.hpp"
#include "../node/guest/guest_content.hpp"

// TODO: make this a real utility app - and remove the inheritance dependancy by providing some other way to tap into the security process

namespace p2psn {
	namespace node_admin {

		/**
		 * CppCMS app for serving hash based static files, a different instance of this function should be used for every file type
		 */
		class hashed_static_app : public base_app {
		public:
		/**
		 * Construct the app on the given cppcms service
		 */
		hashed_static_app(cppcms::service&, const std::string&);

		/**
		 * handle all incoming requests by performing the hash and accessing the files correctly
		 */	
		virtual void main(std::string);

		private:
		std::string folder_;
		std::string extension_;
		std::string mime_;
		};

	} // namespace node_admin
} // namespace p2psn

#endif // __P2PSN_HASHED_STATIC_APP_H

