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

    c.new_settings = 
    
    admin_server_show(c);
}

void admin_server_app::admin_server_show(content::admin_server& c) {
    init(c);
    c.title = "Server Admin";

    render("admin_server",c);
}

void admin_server_app::connection()
{
    content::admin_server c;

    if (request().request_method() == "POST") {
        c.connection.load(context());

        if (c.connection.validate()) {
			port(c.connection.port.value());
			c.add_message("Port set", "confirmed");

            redirect_to_admin_server();
        }
        else {
			c.connection.port.error_message("Port must be a number in the range: 1024-49151");
            admin_server_show(c);
        }
    }
    else {
        redirect_to_admin_server();
    }
}

void admin_server_app::port(int p) {
    auto s = new_settings();

    s.set("service.port", p);

    new_settings(s);
}

int admin_server_app::port() {
    auto s = new_settings();
    
    return s.get<int>("service.port");
}
