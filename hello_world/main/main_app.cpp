#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/url_dispatcher.h>
#include <iostream>

#include "content.h"

class main_app : public cppcms::application {
public:
    main_app(cppcms::service &srv) :
        cppcms::application(srv) 
    {
        dispatcher().assign("",&main_app::intro,this);
        mapper().assign("");

        dispatcher().assign("/about",&main_app::about,this);
        mapper().assign("about","/about");

        mapper().root("/node");
    }
    void intro()
    {
        content::page c;

        init(c);
        c.page_title = "Node";

        // c.page - fill in content

        render("page",c);
    }
    void about()
    {
        content::page c;

        init(c);
        c.page_title = "About";

        render("about",c);
    }
    void init(content::master& c) {
        c.title = "P2Psn";
    }
};

int main(int argc,char ** argv)
{
    try {
        cppcms::service srv(argc,argv);
        srv.applications_pool().mount(cppcms::applications_factory<main_app>());
        srv.run();
    }
    catch(std::exception const &e) {
        std::cerr<<e.what()<<std::endl;
    }
}
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
