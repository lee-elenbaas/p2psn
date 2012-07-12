#include "main_app.h"

#include <cppcms/url_dispatcher.h>

using namespace p2psn::node_app;

void main_app::init(content::master& c) {
    if (session().is_set("user"))
	    c.user_name = session()["user"];
}

main_app::main_app(cppcms::service &srv) :
    cppcms::application(srv) 
{
    dispatcher().assign("",&main_app::info,this);
    mapper().assign("");

    dispatcher().assign("/about",&main_app::about,this);
    mapper().assign("about","/about");

    dispatcher().assign("/about",&main_app::login,this);
    mapper().assign("login","/login");

    dispatcher().assign("/about",&main_app::logout,this);
    mapper().assign("logout","/logout");

    mapper().root("/node");
}

void main_app::info()
{
    content::page c;

	info(c);
}

void main_app::logout()
{
    content::page c;

	session().erase("user");
    session().clear();

	c.add_message("User logged out","confirm");

    info(c);
}

void main_app::info(content::page& c)
{
    c.title = "Info";
    init(c);

    render("info",c);
}

void main_app::about()
{
    content::page c;

    init(c);
    c.title = "About";

    render("about",c);
}

void main_app::login()
{
    content::login_page c;

    if (request().request_method() == "POST") {
        c.login_info.load(context());

//        if (c.login_info.validate()) 
//            session()["user"] = c.login_info.user_name.value();
//        else 
//            session().erase("user");
    }

    init(c);
    c.title = "Login";

    render("login",c);
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
