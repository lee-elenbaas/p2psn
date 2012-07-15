#include "admin_app.h"

#include <cppcms/url_dispatcher.h>

using namespace p2psn::node_admin;

void admin_app::init(content::master& c) {
    if (session().is_set("user"))
	    c.user_name = session()["user"];
}

admin_app::admin_app(cppcms::service &srv) :
    cppcms::application(srv) 
{
    dispatcher().assign("",&admin_app::menu,this);
    mapper().assign("");

    mapper().root("/admin");
}

void admin_app::menu()
{
    content::page c;

    c.title = "Admin Menu";
    init(c);

    render("menu",c);
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
