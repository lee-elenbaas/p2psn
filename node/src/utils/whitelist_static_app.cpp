/**
 * cppcms app for serving static files based on a whitelist
 */
#include "whitelist_static_app.hpp"
#include <cppcms/url_mapper.h>
#include <cppcms/http_response.h>
#include <fstream>
#include "log.hpp"

using namespace p2psn;
using namespace std;
using namespace cppcms::json;
using namespace p2psn::utils;
namespace fs = boost::filesystem;

namespace p2psn {
	namespace utils {

		// since in gcc 4.7 construction delegation does not work - provide a work around
//		whitelist_static_app::whitelist_static_app(cppcms::service &srv, const string& folder, const value& whitelist, hash_algorithm algo) 
//			: whitelist_static_app(srv, folder, signature::hash_function(algo)) {}
		whitelist_static_app::whitelist_static_app(cppcms::service &srv, const fs::path& folder, const value& whitelist, hash_algorithm algo) 
			: application(srv), whitelist_(whitelist), hash_function_(signature::hash_function(algo)), folder_(folder)
		{
			mapper().assign("");
		}

		whitelist_static_app::whitelist_static_app(cppcms::service &srv, const fs::path& folder, const value& whitelist, const hash_function_t hash_function) 
			: application(srv), whitelist_(whitelist), hash_function_(hash_function), folder_(folder)
		{
			mapper().assign("");
		}

		void whitelist_static_app::main(string url) {
			DEBUG("static requested: ["+url+"]");

			string hash = hash_function_(url);
			DEBUG("static hash: ["+hash+"]");
			value file_info = whitelist_.find(hash);

			if (file_info.is_undefined()) {
				DEBUG("Requested url not in white list");
				response().make_error_response(cppcms::http::response::not_found);
				return;
			}
			
			auto file_path = folder_ / file_info.get<string>("path");
			DEBUG("Static path: ["+file_path.string()+"]");
			ifstream f(file_path.string());

			if (!f) {
				DEBUG("File not found in the folder");
				response().make_error_response(cppcms::http::response::not_found);
				return;
			}

			// TODO: support file download using headers based on file size

			DEBUG("dumping file");
			response().content_type(file_info.get<string>("mime"));
			response().out() << f.rdbuf();
		}

	} // namespace node_admin
} // namespace p2psn

