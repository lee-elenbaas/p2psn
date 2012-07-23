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
    dispatcher().assign("",&main_app::home,this);
    mapper().assign("");

    dispatcher().assign("/info",&main_app::info,this);
    mapper().assign("info","/info");

    dispatcher().assign("/about",&main_app::about,this);
    mapper().assign("about","/about");

    dispatcher().assign("/login",&main_app::login,this);
    mapper().assign("login","/login");

    dispatcher().assign("/logout",&main_app::logout,this);
    mapper().assign("logout","/logout");

    dispatcher().assign("/admin",&main_app::admin,this);
    mapper().assign("admin","/admin");

    mapper().root("/node");
}

void main_app::home()
{
	response().set_redirect_header(url("/info"));
}

void main_app::info()
{
    content::info c;

    init(c);
    c.title = "Info";
    c.port = settings()["service"]["port"].number();
    c.host = "localhost"; // TODO: make host discovery from OS or CppCMS lib

    render("info",c);
}

void main_app::logout()
{
    content::page c;

    session().clear();
	response().set_redirect_header(url("/info"));
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
    content::login_page c(settings()["config_noded"]["admin"].array());

    if (request().request_method() == "POST") {
        c.login_info.load(context());

        if (c.login_info.validate()) { 
			session().clear();
            session()["user"] = c.login_info.user_name.value();
			response().set_redirect_header(url("/admin"));
		}
    }
	else {
		session()["form"] = "login";

		init(c);
		c.title = "Login";

		render("login",c);
	}
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
