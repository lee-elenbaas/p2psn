#include "admin_app.h"

#include <cppcms/url_dispatcher.h>
#include "../node_admin/admin_users_app.h"
//#include "../node_admin/admin_server_app.h"

using namespace p2psn::node_admin;
using cppcms::json::value;
using std::string;

admin_app::admin_app(cppcms::service &srv) 
    : admin_base_app(srv) 
{
    attach(new admin_users_app(srv), "users", "/users{1}", "/users(/(.*))?", 1);
//    attach(new admin_server_app(srv), "server", "/server{1}", "/server(/(.*))?", 1);

    dispatcher().assign("",&admin_app::admin,this);
    mapper().assign("");
}

void admin_app::admin()
{
    content::master c;

    init(c);
    c.title = "Admin";

    render("admin",c);
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

