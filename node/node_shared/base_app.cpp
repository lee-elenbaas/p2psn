#include "base_app.h"

using namespace p2psn::node_admin;

base_app::base_app(cppcms::service &srv) 
    : cppcms::application(srv) 
{
}

void base_app::init(content::master& c) {
    if (session().is_set("user"))
	    c.user_name = session()["user"];
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

