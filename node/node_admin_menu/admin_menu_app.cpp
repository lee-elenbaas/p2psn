#include "admin_menu_app.hpp"

#include <cppcms/url_dispatcher.h>
#include "../node_admin_users/admin_users_app.hpp"
//#include "../node_admin_server/admin_server_app.hpp"

using namespace p2psn::node_admin;
using cppcms::json::value;
using std::string;

admin_menu_app::admin_menu_app(cppcms::service &srv) 
    : admin_base_app(srv) 
{
    attach(new admin_users_app(srv), "users", "/users{1}", "/users(/(.*))?", 1);

//    attach(new admin_server_app(srv), "server", "/server{1}", "/server(/(.*))?", 1);
    dispatcher().assign("/server",&admin_menu_app::server,this);
    mapper().assign("server", "/server");

    dispatcher().assign("",&admin_menu_app::admin_menu,this);
    mapper().assign("");
}

void admin_menu_app::admin_menu()
{
    content::master c;

    init(c);
    c.title = "Admin";

    render("admin_menu",c);
}

void admin_menu_app::server()
{
    content::master c;

    init(c);
    c.title = "Server Admin";

    render("admin_server",c);
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

