/**
 * Content declarations for communication between the node_admin and its skin.
 *
 * The content types used by the node_admin to pass values into its skin for rendering the result HTML pages.
 */
#ifndef __P2PSN_GUEST_CONTENT_H
#define __P2PSN_GUEST_CONTENT_H

#include "../shared/base_content.hpp"

namespace p2psn {
    namespace node_admin {
        namespace content  {

            struct info : public master {
                double port;
                std::string host;
            };

            struct login_form : public cppcms::form {
                cppcms::widgets::text user_name;
                cppcms::widgets::password user_password;
                cppcms::widgets::submit submit;

                login_form();
            };

            struct login_page : public master {
                login_form login_info;
            };

        } // namespace content
    } // namespace node_admin
} // namespace p2psn

#endif // __P2PSN_GUEST_CONTENT_H

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

