#include "hashed_static_app.hpp"

#include <fstream>
#include "crypto.hpp"

using namespace p2psn::node_admin;
using namespace std;
using namespace cppcms::json;

whitelist_static_app::whitelist_static_app(cppcms::service &srv, const cppcms::json::value& whitelist) 
	: base_app(srv), whitelist_(whitelist)
{
	mapper().assign("");
}

void hashed_static_app::main(string url) {
	DEBUG("static requested: "+url);

	DEBUG("md5 hash: " + utils::signature::md5(url));
	DEBUG("sha1 hash: " + utils::signature::sha1(url));
	string hash = "node";

	ifstream f(folder_+hash+extension_);

	if (!f) {
		DEBUG("file not found");
		response().status(404);
	}
	else {
		DEBUG("dumping file");
		response().content_type(mime_);
		response().out() << f.rdbuf();
	}
}

