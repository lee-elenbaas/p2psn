#include "hashed_static_app.hpp"

#include <fstream>
#include "crypto.hpp"

using namespace p2psn::node_admin;
using namespace std;
using namespace cppcms::json;

hashed_static_app::hashed_static_app(cppcms::service &srv, const std::string& settings_path) 
	: base_app(srv) 
{
	mapper().assign("");

	folder_ = settings().get<string>(settings_path+".folder");
	extension_ = settings().get<string>(settings_path+".extension");
	mime_ = settings().get<string>(settings_path+".mime");
}

void hashed_static_app::main(string url) {
	DEBUG("css requested: "+url);

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

