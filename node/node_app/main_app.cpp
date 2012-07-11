#include "main_app.h"

#include <cppcms/url_dispatcher.h>

void main_app::init(content::master& c) {
    c.title = "P2Psn";
	c.is_guest = !session().is_set("user");
}

main_app::main_app(cppcms::service &srv) :
    cppcms::application(srv) 
{
    dispatcher().assign("",&main_app::home,this);
    mapper().assign("");

    dispatcher().assign("/about",&main_app::about,this);
    mapper().assign("about","/about");

    dispatcher().assign("/about",&main_app::login,this);
    mapper().assign("login","/login");

    dispatcher().assign("/about",&main_app::logout,this);
    mapper().assign("logout","/logout");

    mapper().root("/node");
}

void main_app::home()
{
    content::page c;

    init(c);

	home(c);
}

void main_app::logout()
{
    content::page c;

    init(c);

	session().erase("user");
	c.add_message("User logged out","confirm");

    home(c);
}

void main_app::home(content::page c)
{
    c.page_title = "Info";

    // c.page - fill in content

    render("home",c);
}

void main_app::home()

void main_app::about()
{
    content::page c;

    init(c);
    c.page_title = "About";

    render("about",c);
}

void main_app::login()
{
    content::login_page c;

    if (request().request_method() == "POST") {
        c.login_info.load(context());

        if (c.info.validate()) {
            session()["user"]=c.login_info.user_name;
        }
        else {
            session().erase("user");
        }
    }

    init(c);
    c.page_title = "Login";

    render("login",c);
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
