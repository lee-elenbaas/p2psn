#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/url_dispatcher.h>
#include <iostream>

#include "content.h"

class separated_tmpl_sample : public cppcms::application {
public:
    separated_tmpl_sample(cppcms::service &s) :
       cppcms::application(s)
    {
        dispatcher().assign("",&separated_tmpl_sample::home,this);
        mapper().assign("");

        dispatcher().assign("/base",&separated_tmpl_sample::base,this);
        mapper().assign("base","/base");

        dispatcher().assign("/derived",&separated_tmpl_sample::derived,this);
        mapper().assign("derived","/derived");

        mapper().root("/sample");
    }
private:
    void home()
    {
        response().set_redirect_header(url("/base"));
    }
    void base()
    {
        content::base c;

        c.page_content = "base content";

        render("base", c);
    }
    void derived()
    {
        content::base c;

        c.page_content = "derived content";

        render("derived", c);
    }
};



int main(int argc,char ** argv)
{
    try {
        cppcms::service srv(argc,argv);
        srv.applications_pool().mount(cppcms::applications_factory<separated_tmpl_sample>());
        srv.run();
    }
    catch(std::exception const &e) {
        std::cerr<<e.what()<<std::endl;
    }
}
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

