#include "admin_server_app.hpp"

#include <cppcms/url_dispatcher.h>

using namespace p2psn::node_admin;
using cppcms::json::value;
using std::string;

admin_server_app::admin_server_app(cppcms::service &srv) 
    : admin_base_app(srv) 
{
    dispatcher().assign("",&admin_server_app::server,this);
    mapper().assign("");
}

void admin_server_app::server()
{
    content::master c;

    init(c);
    c.title = "Server Admin";

    render("admin_server",c);
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

