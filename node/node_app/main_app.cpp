#include "main_app.h"

#include <cppcms/url_dispatcher.h>

void main_app::init(content::master& c) {
    c.title = "P2Psn";
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

    mapper().root("/node");
}

void main_app::info()
{
    content::page c;

    init(c);
    c.page_title = "Info";

    // c.page - fill in content

    render("info",c);
}

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

//        if (c.login_info.validate()) 
//            session()["user"] = c.login_info.user_name.value();
//        else 
//            session().erase("user");
    }

    init(c);
    c.page_title = "Login";

    render("login",c);
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
