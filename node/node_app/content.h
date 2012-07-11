#ifndef __CONTENT_H
#define __CONTENT_H

#include <cppcms/view.h>
#include <cppcms/form.h>
#include <string>

namespace content  {
    struct master : public cppcms::base_content {
        std::string title;
    };

    struct page : public master {
        std::string page_title, page_content;
    };

    struct login_form : public cppcms::form {
        cppcms::widgets::text user_name;
        cppcms::widgets::password user_password;

        login_form();
        virtual bool validate();
    };

    struct login_page : public page {
        login_form login_info;
    };
}


#endif // __CONTENT_H
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

