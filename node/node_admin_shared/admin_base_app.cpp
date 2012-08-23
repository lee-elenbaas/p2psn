#include "admin_base_app.hpp"
#include <boost/serialization/vector.hpp>
#include <cppcms/json.h>

using namespace p2psn::node_admin;
using namespace std;
using namespace cppcms::json;

admin_base_app::admin_base_app(cppcms::service &srv) 
    : base_app(srv) 
{
}

void admin_base_app::main(std::string request_url)
{
    if (session().is_set("user")) {
        base_app::main(request_url);
    }
    else {
        session().set("url_after_login", request().path_info());
        response_redirect(url("/login"));
    }
}

vector<content::user> admin_base_app::admin_users()
{
    /// Use stores list if present in session
    if (session().is_set("admin_users"))
        return session_get<vector<content::user>>("admin_users");

    /// Convert current config to admin list
    vector<content::user> users;

    value existing_users = settings().at("config_noded.admin");
    
    if (existing_users.type() == json_type::is_array) {
        for(auto u : existing_users.array()) {
            content::user user;

            user.name = u["user"].str();
            user.password = u["password"].str();
            user.user_state = content::admin_user_state::existing_user;

            users.push_back(user);
        }
    }

    return users;
}

void admin_base_app::admin_users(const vector<content::user>& users)
{
    session_set("admin_users", users);
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

