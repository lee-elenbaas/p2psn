#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <iostream>

class my_hello_world : public cppcms::application {
public:
    my_hello_world(cppcms::service &srv) :
        cppcms::application(srv) 
    {
        dispatcher().assign("",&myapp::intro,this);
        mapper().assign("");

        dispatcher().assign("/about",&myapp::about,this);
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
    void intro()
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
        srv.applications_pool().mount(cppcms::applications_factory<my_hello_world>());
        srv.run();
    }
    catch(std::exception const &e) {
        std::cerr<<e.what()<<std::endl;
    }
}
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
