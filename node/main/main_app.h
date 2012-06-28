#include <cppcms/application.h>
#include <cppcms/service.h>

#include "content.h"

class main_app : public cppcms::application {
public:
    main_app(cppcms::service &srv);
    void init(content::master& c);
    void intro();
    void about();
};

int main(int argc,char ** argv);

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
