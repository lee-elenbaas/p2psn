#include "main/main_app.h"
#include <cppcms/applications_pool.h>
#include <cppcms/url_dispatcher.h>

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
