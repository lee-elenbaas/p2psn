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

bool admin_apply_app::validate_settings(const value& settings) {
	bool is_valid = true;
	
	bool has_admin = false;
	bool has_manager = false;
	
    for (auto user : settings.at("config_noded.admin").array()) {
        if (user.get<bool>("is_admin"))
            has_admin = true;
        if (user.get<bool>("is_manager"))
            has_manager = true;

		if (user.get<string>("user") == "admin")
			add_message("Default admin user was not removed.", "warning");
        if (user.get<bool>("is_admin") && user.get<bool>("is_manager"))
			add_message("User "+user.get<string>("user")+" has no rights.", "warning");
    }
    
    if (!has_admin) {
		is_valid = false;
		add_message("Configuration is missing an admin user", "error");
	}
	
	if (!has_manager)
		add_message("Configuration is missing a manager user", "warning");
		
	if (settings.get<int>("service.port") < 1024)
		add_message("Listening port is below port 1024.", "warning");
		
	return is_valid;
}

void admin_apply_app::admin_apply_show(content::admin_apply& c) {
    init(c);
    c.title = "Apply New Server Configuration";
	c.is_valid = validate_settings(c.new_settings);
	
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
