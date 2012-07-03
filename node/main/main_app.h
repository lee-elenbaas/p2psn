#ifndef __MAIN_APP_H
#define __MAIN_APP_H

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

#endif // __MAIN_APP_H
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4