#include "admin_menu_app.hpp"

#include <cppcms/url_dispatcher.h>
#include "../admin_users/admin_users_app.hpp"
#include "../admin_server/admin_server_app.hpp"

using namespace p2psn::node_admin;
using cppcms::json::value;
using std::string;

void admin_menu_app::main(std::string request_url)
{
    // TODO: add ip filtering here
    DEBUG("Admin from ip: "+request().remote_addr());
    
    if (session().is_set("user")) {
        base_app::main(request_url);
    }
    else {
        session().set("url_after_login", request().path_info());
        response_redirect(url("/node/login"));
    }
}

admin_menu_app::admin_menu_app(cppcms::service &srv) 
    : admin_base_app(srv) 
{
    attach(new admin_users_app(srv), "users", "/users{1}", "/users(/(.*))?", 1);

    attach(new admin_server_app(srv), "server", "/server{1}", "/server(/(.*))?", 1);

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

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

