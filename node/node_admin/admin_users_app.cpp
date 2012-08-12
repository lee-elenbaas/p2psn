#include "admin_users_app.h"

#include <cppcms/url_dispatcher.h>
#include <sstream>

using namespace p2psn::node_admin;
using cppcms::json::value;
using std::string;

admin_users_app::admin_users_app(cppcms::service &srv) 
    : admin_base_app(srv) 
{
    dispatcher().assign("",&admin_users_app::list_users,this);
    mapper().assign("");

    dispatcher().assign("/new",&admin_users_app::add_user,this);
    mapper().assign("new","/new");

    dispatcher().assign("/edit",&admin_users_app::edit_user,this);
    mapper().assign("edit","/edit");

    dispatcher().assign("/delete",&admin_users_app::delete_user,this);
    mapper().assign("delete","/delete");

    dispatcher().assign("/restore",&admin_users_app::restore_user,this);
    mapper().assign("restore","/restore");
}

void admin_users_app::admin_users_show(content::admin_users& c) {
    init(c);
    c.title = "Admin Users";

    render("admin_users",c);
}

void admin_users_app::list_users()
{
    content::admin_users c;

    c.list_state = content::admin_users_list_state::view;

    admin_users_show(c);
}

void admin_users_app::add_user()
{
    content::admin_users c;

    c.list_state = content::admin_users_list_state::view;

    if (request().request_method() == "POST") {
        
    }

    admin_users_show(c);
}

void admin_users_app::edit_user()
{
    content::admin_users c;

    c.list_state = content::admin_users_list_state::editing;

    if (request().request_method() == "POST") {
        
    }

    admin_users_show(c);
}

void admin_users_app::delete_user()
{
    content::admin_users c;

    c.list_state = content::admin_users_list_state::view;

    if (request().request_method() == "POST") {
        
    }

    admin_users_show(c);
}

void admin_users_app::restore_user()
{
    content::admin_users c;

    c.list_state = content::admin_users_list_state::view;

    if (request().request_method() == "POST") {
        
    }

    admin_users_show(c);
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

