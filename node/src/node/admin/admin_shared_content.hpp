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
            
            struct user {
                std::string name;
                std::string password;
                bool is_admin;
                bool is_manager;
            };

        } // namespace content
    } // namespace node_admin
} // namespace p2psn

namespace cppcms {
    namespace json {

        template<>
        struct traits<p2psn::node_admin::content::user> {
            static p2psn::node_admin::content::user get(const value&);
            static void set(value&, const p2psn::node_admin::content::user&);
        };

    } // namespace json
} // namespace cppcms

#endif // __P2PSN_ADMIN_SHARED_CONTENT_H

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

