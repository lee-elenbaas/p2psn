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
    c.existing_users = admin_users();

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
        c.new_user.load(context());

        auto users = admin_users();
        
        if (c.new_user.validate() && avaliable_user(c.new_user, users)) {
            content::user new_user;

            new_user.name = c.new_user.user_name.value();
            new_user.password = c.new_user.user_password.value();
            new_user.user_state = content::admin_user_state::new_user;

            users.push_back(new_user);

            admin_users(users);
            // TODO: place message to user
            
            response_redirect("/admin");
        }
    }

    admin_users_show(c);
}

bool admin_users_app::avaliable_user(content::new_user_form& new_user, const vector<content::user>& users) 
{
    for (auto u : users) {
        if (new_user.user_name.value() == u.name) {
            new_user.user_name.valid(false);

            return false;
        }
    }

    return true;
}

void admin_users_app::edit_user()
{
    auto users = admin_users();
    content::admin_users c;

    c.list_state = content::admin_users_list_state::view;

    if (request().request_method() == "POST") {
        string user_name = requst().post("user_name");

        for (auto u : users) {
            if (u.name == user_name) {
                // TODO: set user to be edited
                c.list_state = content::admin_users_list_state::editing;
            }
        }
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

