#ifndef __P2PSN_ADMIN_SERVER_CONTENT_H
#define __P2PSN_ADMIN_SERVER_CONTENT_H

#include "admin_shared_content.hpp"

namespace p2psn {
    namespace node_admin {
        namespace content  {

            struct connection_form : public cppcms::form {
                cppcms::widgets::numeric<int> port;
                cppcms::widgets::submit submit;
                
                connection_form();
            };

            struct admin_server : public master {
                connection_form connection;
            };

        } // namespace content
    } // namespace node_admin
} // namespace p2psn

#endif
