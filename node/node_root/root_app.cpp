#include "admin_app.h"

#include <cppcms/url_dispatcher.h>
#include "../node_guest/main_app.h"

using namespace p2psn::node_admin;
using std::string;

root_app::root_app(cppcms::service &srv) 
	: base_app(srv) 
{
	attach(new main_app(srv), "en_US", "/en_US{1}", "/en_US(/(.*))?", 1);
	attach(new main_app(srv), "he_IL", "/he_IL{1}", "/he_IL(/(.*))?", 1);

	dispatcher().assign("^(.*)$",&root_app::redirect,this);  

	mapper().root("/node");
}

void root_app::redirect() 
{
	response().set_redirect_header("/en_US" + request().script_name());
//	response().set_redirect_header("/en_US" + request().path_info());
}

// vim: tabstop=4 shiftwidth=4 softtabstop=4

