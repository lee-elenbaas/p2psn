#include "admin_app.h"

#include <cppcms/url_dispatcher.h>
#include <sstream>

using namespace p2psn::node_admin;
using cppcms::json::value;
using std::string;

admin_app::admin_app(cppcms::service &srv) 
    : base_app(srv) 
{
    dispatcher().assign("",&admin_app::admin,this);
    mapper().assign("");

    dispatcher().assign("/users",&admin_app::admin_users,this);
    mapper().assign("users","/users");

    dispatcher().assign("/server",&admin_app::admin_server,this);
    mapper().assign("server","/server");
}

void admin_app::admin()
{
    content::master c;

    init(c);
    c.title = "Admin";

    render("admin",c);
}

void admin_app::new_config(const value& nc)
{
    session().set("new_config", nc.save());
}

value admin_app::new_config()
{
    value nc;

    if (session().is_set("new_config")) // read new config from session after changes were made but not commited
    {
        std::istringstream nc_str(session().get("new_config"));
        
        nc_str >> nc;
    }
    else // duplicate current settings
    {
        nc = settings();
    }

    return nc;
}

void admin_app::admin_users()
{
    content::admin_users c;

    init(c);
    c.title = "Admin Users";
    c.state = content::admin_users_state::view;

    auto nc = new_config();

    for (auto user : nc["config_noded"]["admin"].array())
        c.existing_users.push_back({ user["user"].str(), user["password"].str() });

    if (request().request_method() == "POST") {
        
    }

    render("admin_users",c);
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
        base_app::main(request_url);
    }
    else {
        session()["url_after_login"] = request().path_info();
        response().set_redirect_header(url("/login"));
    }
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

