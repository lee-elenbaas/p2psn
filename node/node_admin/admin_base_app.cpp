#include "admin_base_app.h"

using namespace p2psn::node_admin;

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
        session()["url_after_login"] = request().path_info();
        response_redirect(url("/login"));
    }
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

