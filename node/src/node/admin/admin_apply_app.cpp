#include "admin_apply_app.hpp"
#include <cppcms/url_dispatcher.h>

using namespace p2psn::node_admin;
using cppcms::json::value;
using std::string;

admin_apply_app::admin_apply_app(cppcms::service &srv) 
    : admin_base_app(srv) 
{
    dispatcher().assign("",&admin_apply_app::apply,this);
    mapper().assign("");

    dispatcher().assign("/set",&admin_apply_app::set,this);
    mapper().assign("set","/set");
}

void admin_apply_app::apply()
{
    content::admin_apply c;

    c.new_settings = new_settings();
    
    admin_apply_show(c);
}

void admin_apply_app::admin_apply_show(content::admin_apply& c) {
    init(c);
    c.title = "Apply New Server Configuration";

    render("admin_apply",c);
}

void admin_apply_app::set()
{
    content::admin_apply c;

    if (request().request_method() == "POST") {
        c.apply.load(context());

        if (c.apply.validate()) {
			// TODO: apply the new settings

            redirect_to_admin_apply();
        }
        else {
            admin_apply_show(c);
        }
    }
    else {
        redirect_to_admin_apply();
    }
}
