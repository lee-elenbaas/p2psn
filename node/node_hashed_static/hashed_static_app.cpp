#include "../node_statics/hashed_static_app.hpp"

#include <fstream>

using namespace p2psn::node_admin;
using namespace std;
using namespace cppcms::json;

hashed_static_app::hashed_static_app(cppcms::service &srv, const std::string&) 
	: base_app(srv) 
{
    mapper().assign("");
}

void hashed_static_app::main(string url) {
	DEBUG("css requested: "+url);

	ifstream f("run/css/node.css");

	if (!f) {
		DEBUG("file not found");
		response().status(404);
	}
	else {
		DEBUG("dumping file");
		response().content_type("text/css");
		response().out() << f.rdbuf();
	}
}

