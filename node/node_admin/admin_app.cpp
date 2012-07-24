#include "admin_app.h"

#include <cppcms/url_dispatcher.h>
#include "../node_api/node_api.h"

using namespace p2psn::node_app;

admin_app::admin_app(cppcms::service &srv) 
    : cppcms::application(srv) 
{
    dispatcher().assign("",&admin_app::home,this);
    mapper().assign("");

    dispatcher().assign("/users",&admin_app::admin_users,this);
    mapper().assign("users","/users");

    dispatcher().assign("/server",&admin_app::admin_server,this);
    mapper().assign("server","/server");
}

void admin_app::home()
{
    content::master c;

    init(c);
    c.title = "Admin";

    render("admin",c);
}

void admin_app::admin_users()
{
    content::master c;

    init(c);
    c.title = "Admin Users";

    render("admin",c);
}

void admin_app::admin_server()
{
    content::master c;

    init(c);
    c.title = "Admin Server";

    render("admin",c);
}

void admin_app::main(std::string request_url)
{
    if (session().is_set("user")) {
        cppcms::application::main(request_url);
    }
    else {
        session()["url_after_login"] = request_url;
        response().set_redirect_header(url("/login"));
    }
}

void admin_app::init(content::master& c) {
    if (session().is_set("user"))
	    c.user_name = session()["user"];
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

