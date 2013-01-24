#include "admin_users_app.hpp"

#include <cppcms/url_dispatcher.h>
#include <sstream>
#include <algorithm>

using namespace p2psn::node_admin;
using namespace cppcms::json;
using namespace std;

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

    dispatcher().assign("/update",&admin_users_app::update_user,this);
    mapper().assign("update","/update");
}

void admin_users_app::admin_users(const vector<content::user>& users) {
    auto s = new_settings();

    s.set("config_noded.admin", users);

    new_settings(s);
}

vector<content::user> admin_users_app::admin_users() {
    auto s = new_settings();
    
    return s.get<vector<content::user>>("config_noded.admin");
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
    c.users = admin_users();

	// make sure a state exists for every user
	auto states = admin_users_states();
	DEBUG("Making sure all users have a state");
	for(auto user : c.users) {
		auto state = states[user.name];
		
		states[user.name] = state;
		DEBUG("Making sure user "+user.name+" has state");
	}
	DEBUG("Making sure all users have a state");
	
	DEBUG("Storing user states in session");
	admin_users_states(states);
	DEBUG("User states stored in session");

    c.user_states = states;

    admin_users_show(c);
}

void admin_users_app::update_user()
{
    content::admin_users c;

    c.list_state = content::admin_users_list_state::view;
    auto users = admin_users();
    auto states = admin_users_states();

    if (request().request_method() == "POST") {
        c.edited_user.load(context());

        if (c.edited_user.validate()) {
            bool user_found = false;

            for (auto u : users) {
                if (u.name == c.edited_user.user_name.value()) {
					u.password = c.edited_user.user_password.value();
					u.is_admin = c.edited_user.is_admin.value();
					u.is_manager = c.edited_user.is_manager.value();

					auto state = states[u.name];
					state.css_class = "existing_user";
					state.allow_edit = true;
					state.allow_delete = true;
					state.allow_restore = false;

					admin_users(users);
					admin_users_states(states);

					c.add_message("user updated", "confirm");
					redirect_to_admin_users();

                    user_found = true;
                    break;
                }
            }

            if (!user_found) {
                c.add_message("user not found", "error");
				redirect_to_admin_users();
            }
        }
        else {
            c.users = users;
            c.user_states = states;
            admin_users_show(c);
        }
    }
    else {
        redirect_to_admin_users();
    }
}

void admin_users_app::add_user()
{
    content::admin_users c;

    c.list_state = content::admin_users_list_state::view;
    auto users = admin_users();
    auto states = admin_users_states();

    if (request().request_method() == "POST") {
        c.new_user.load(context());

        if (c.new_user.validate() && avaliable_user(c.new_user, users)) {
            content::user new_user;

            new_user.name = c.new_user.user_name.value();
            new_user.password = c.new_user.user_password.value();
			new_user.is_admin = c.edited_user.is_admin.value();
			new_user.is_manager = c.edited_user.is_manager.value();

            users.push_back(new_user);

			auto state = states[new_user.name];
			
			state.css_class = "new_user";
			
            admin_users(users);
            admin_users_states(states);
                    
            c.add_message("user added", "confirm");
            
            redirect_to_admin_users();
        }
    }

    c.users = users;
    c.user_states = states;
    admin_users_show(c);
}

bool admin_users_app::avaliable_user(content::new_user_form& new_user, const std::vector<content::user>& users) 
{
    for (auto u : users) {
        if (new_user.user_name.value() == u.name) {
            new_user.user_name.valid(false);
            new_user.user_name.message("User name already in use");
            //new_user.valid(false);

            return false;
        }
    }

    return true;
}

void admin_users_app::edit_user()
{
    auto users = admin_users();
    auto states = admin_users_states();

    content::admin_users c;

    c.list_state = content::admin_users_list_state::view;

    bool user_found = false;

    if (request().request_method() == "POST") {
        string user_name = request().post("user_name");

        for (auto u : users) {
            if (u.name == user_name) {
                c.edited_user.user_name.value(u.name);
                c.edited_user.is_admin.value(u.is_admin);
                c.edited_user.is_manager.value(u.is_manager);

				auto state = states[u.name];
			
				state.css_class = "editing_user";
				state.allow_edit = false;
				state.allow_delete = false;
				state.allow_restore = false;

                user_found = true;
                break;
            }
        }
    }

    if (user_found) {
        c.users = users;
        c.user_states = states;
        admin_users_show(c);
    }
    else {
        c.add_message("user not found", "error");
        redirect_to_admin_users();
    }
}

void admin_users_app::delete_user()
{
    auto users = admin_users();
    auto states = admin_users_states();

    bool user_found = false;

    if (request().request_method() == "POST") {
        string user_name = request().post("user_name");
        
        for (content::user& u : users) {
            if (u.name == user_name) {
				auto state = states[u.name];
				
                state.css_class = "deleted_user";
                state.allow_edit = false;
                state.allow_delete = false;
                state.allow_restore = true;
        
                admin_users(users);
                admin_users_states(states);

                add_message("user deleted", "confirm");
                user_found = true;
                break;
            }
        }
    }

    if (!user_found)
        add_message("user not found", "error");

    redirect_to_admin_users();
}

void admin_users_app::restore_user()
{
    auto users = admin_users();
    auto states = admin_users_states();

    bool user_found = false;

    if (request().request_method() == "POST") {
        string user_name = request().post("user_name");
        
        for (content::user& u : users) {
            if (u.name == user_name) {
				auto state = states[u.name];
				
				state.allow_edit = true;
				state.allow_delete = true;
				state.allow_restore = false;
				state.css_class = "changed_user";

				admin_users(users);
				admin_users_states(states);
			
				add_message("user restored", "confirm");

                user_found = true;
                break;
            }
        }
    }

    if (!user_found)
        add_message("user not found", "error");

    redirect_to_admin_users();
}
