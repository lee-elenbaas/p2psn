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

            enum class 

            enum class admin_user_state {
                existing_user,
                new_user,
                edited_user,
                deleted_user
            };
            
            struct user {
                string name;
                string password;
                admin_user_state state;
            };

            struct new_user_form : public cppcms::form {
                cppcms::widgets::text user_name;
                cppcms::widgets::password user_password;
                cppcms::widgets::submit submit;
                
                new_user_form();
            };

            struct edited_user_form : public cppcms::form {
                cppcms::widgets::hidden user_name;
                cppcms::widgets::password user_password;
                cppcms::widgets::submit submit;
                
                edited_user_form();
            };

            struct admin_users : public master {
                std::vector<user> existing_users;
                
                new_user_form new_user;
                edited_user_form edited_user;
            };

        } // namespace content
    } // namespace node_admin
} // namespace p2psn

#endif // __P2PSN_ADMIN_CONTENT_H

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

