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
        response_redirect(url("/node/login"));
    }
}

bool admin_base_app::has_new_settings() {
    return session().is_set("new_settings");
}

value admin_base_app::new_settings()
{
    /// Use stores list if present in session
    if (has_new_settings())
        return session_get<value>("new_settings");

    /// Convert current config to admin list
    return settings();
}

void admin_base_app::new_settings(const value& settings)
{
    session_set("new_settings", settings);
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

