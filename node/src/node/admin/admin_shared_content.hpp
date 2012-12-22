/**
 * Content declarations for communication between the node_admin and its skin.
 *
 * The content types used by the node_admin to pass values into its skin for rendering the result HTML pages.
 */
#ifndef __P2PSN_ADMIN_SHARED_CONTENT_H
#define __P2PSN_ADMIN_SHARED_CONTENT_H

#include "../guest/base_content.hpp"

namespace p2psn {
    namespace node_admin {
        namespace content  {

            enum class admin_user_state {
                existing_user,
                new_user,
                edited_user,
                deleted_user
            };
            
            struct user {
                std::string name;
                std::string password;
                admin_user_state user_state;

                std::string state_str() const;
            };

        } // namespace content
    } // namespace node_admin
} // namespace p2psn

namespace cppcms {
    namespace json {

        template<>
        struct traits<p2psn::node_admin::content::admin_user_state> {
            static p2psn::node_admin::content::admin_user_state get(const value&);
            static void set(value&, const p2psn::node_admin::content::admin_user_state&);
        };

        template<>
        struct traits<p2psn::node_admin::content::user> {
            static p2psn::node_admin::content::user get(const value&);
            static void set(value&, const p2psn::node_admin::content::user&);
        };

    } // namespace json
} // namespace cppcms

#endif // __P2PSN_ADMIN_SHARED_CONTENT_H

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

