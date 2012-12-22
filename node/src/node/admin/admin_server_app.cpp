#include "admin_server_app.hpp"
#include <cppcms/url_dispatcher.h>

using namespace p2psn::node_admin;
using cppcms::json::value;
using std::string;

admin_server_app::admin_server_app(cppcms::service &srv) 
    : admin_base_app(srv) 
{
    dispatcher().assign("",&admin_server_app::server,this);
    mapper().assign("");

    dispatcher().assign("/connection",&admin_server_app::connection,this);
    mapper().assign("connection","/connection");
}

void admin_server_app::server()
{
    content::admin_server c;

    c.connection.port.value(port());
    
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
