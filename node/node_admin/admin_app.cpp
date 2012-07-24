#include "admin_app.h"

#include <cppcms/url_dispatcher.h>

using namespace p2psn::node_app;

admin_app::admin_app(cppcms::service &srv) 
    : base_app(srv) 
{
    dispatcher().assign("",&admin_app::home,this);
    mapper().assign("");

    dispatcher().assign("/users",&admin_app::users,this);
    mapper().assign("users","/users");

    dispatcher().assign("/server",&admin_app::server,this);
    mapper().assign("server","/server");
}

void admin_app::home()
{
    content::master c;

    init(c);
    c.title = "Admin";

    render("admin",c);
}

void admin_app::users()
{
    content::master c;

    init(c);
    c.title = "Admin Users";

    render("admin",c);
}

void admin_app::server()
{
    content::master c;

    init(c);
    c.title = "Admin Server";

    render("admin",c);
}

void admin_app::main(std::string request_url)
{
    if (session().is_set("user")) {
        base_app::main(request_url);
    }
    else {
        session()["url_after_login"] = request_url;
        response().set_redirect_header(url("/login"));
    }
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

