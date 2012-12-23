
#ifndef __P2PSN_ADMIN_APPLY_CONTENT_H
#define __P2PSN_ADMIN_APPLY_CONTENT_H

#include "admin_shared_content.hpp"

namespace p2psn {
    namespace node_admin {
        namespace content  {

            struct apply_form : public cppcms::form {
                cppcms::widgets::submit submit;
                
                apply_form();
            };

            struct admin_apply : public master {
                apply_form apply;
                
                cppcms::json::value new_settings;
            };

        } // namespace content
    } // namespace node_admin
} // namespace p2psn

#endif
