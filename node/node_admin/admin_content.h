/**
 * Content declarations for communication between the node_admin and its skin.
 *
 * The content types used by the node_admin to pass values into its skin for rendering the result HTML pages.
 */
#ifndef __P2PSN_ADMIN_CONTENT_H
#define __P2PSN_ADMIN_CONTENT_H

#include "../node_shared/base_content.h"

namespace p2psn {
    namespace node_admin {
        namespace content  {

            struct user {
                string name;
                string password;
            };

            class enum admin_users_state {
                view,
                new_user,
                edit_user
            };
            
            class existing_user_form : public cppcms::form {
                cppcms::widgets::hidden user_name;
                cppcms::widgets::password user_password;
                cppcms::widgets::submit submit;
                
                existing_user_form();
            };

            class new_user_form : public cppcms::form {
                cppcms::widgets::text user_name;
                cppcms::widgets::password user_password;
                cppcms::widgets::submit submit;
                
                new_user_form();
            };

            struct admin_users : public master {
                admin_users_state state;
                std::vector<user> existing_users;
            };

        } // namespace content
    } // namespace node_admin
} // namespace p2psn

#endif // __P2PSN_ADMIN_CONTENT_H

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

