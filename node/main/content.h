#ifndef __CONTENT_H
#define __CONTENT_H

#include <cppcms/view.h>
#include <string>

namespace content  {
    struct master : public cppcms::base_content {
        std::string title;
    };
    struct page : public master {
        std::string page_title, page_content;
    };
}


#endif // __CONTENT_H
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
