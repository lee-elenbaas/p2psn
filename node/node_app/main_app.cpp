#include "main_app.h"

#include <cppcms/url_dispatcher.h>

void main_app::init(content::master& c) {
    c.title = "P2Psn";
}

main_app::main_app(cppcms::service &srv) :
    cppcms::application(srv) 
{
    dispatcher().assign("",&main_app::home,this);
    mapper().assign("");

    dispatcher().assign("/about",&main_app::about,this);
    mapper().assign("about","/about");

    mapper().root("/node");
}

void main_app::home()
{
    content::page c;

    init(c);
    c.page_title = "Info";

    // c.page - fill in content

    render("home",c);
}

void main_app::about()
{
    content::page c;

    init(c);
    c.page_title = "About";

    render("about",c);
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
