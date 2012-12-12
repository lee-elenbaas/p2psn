/**
 * cppcms app for serving static files based on a whitelist
 */
#ifndef __P2PSN_WHITELIST_STATIC_APP_H
#define __P2PSN_WHITELIST_STATIC_APP_H

#include "../node/shared/base_app.hpp"
#include "../node/guest/guest_content.hpp"
#include "../utils/crypto.hpp"
#include <boost/filesystem.hpp>

namespace p2psn {
	namespace node_admin {

		/**
		 * CppCMS app for serving hash based static files, a different instance of this function should be used for every file type
		 */
		class whitelist_static_app : public base_app {
		public:
		/**
		 * Construct the app on the given cppcms service
		 */
		whitelist_static_app(cppcms::service&, const boost::filesystem::path&, const cppcms::json::value&, p2psn::utils::hash_algorithm = p2psn::utils::hash_algorithm::md5);
		/**
		 * Construct the app on the given cppcms service
		 */
		whitelist_static_app(cppcms::service&, const boost::filesystem::path&, const cppcms::json::value&, const p2psn::utils::hash_function_t);

		/**
		 * handle all incoming requests by performing the hash and accessing the files correctly
		 */	
		virtual void main(std::string);

		private:
		/**
		 * The whitelist value used by this app for specifing what files to serve and how
		 */
		const cppcms::json::value& whitelist_;
		
		/**
		 * The hash function used for matching the requests
		 */
		const p2psn::utils::hash_function_t hash_function_;

		/**
		 * The base folder to get the files from
		 */
		const boost::filesystem::path folder_;
		};

	} // namespace node_admin
} // namespace p2psn

#endif // __P2PSN_HASHED_STATIC_APP_H

