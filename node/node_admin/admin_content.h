/**
 * Content declarations for communication between the node_admin and its skin.
 *
 * The content types used by the node_admin to pass values into its skin for rendering the result HTML pages.
 */
#ifndef __P2PSN_ADMIN_CONTENT_H
#define __P2PSN_ADMIN_CONTENT_H

#include "base_content.h"

namespace p2psn {
    namespace node_admin {
        namespace content  {

            struct user {
                string name;
                string password;
            };

            struct admin_users : public master {
                std::vector<user> users;
            };

        } // namespace content
    } // namespace node_admin
} // namespace p2psn

#endif // __P2PSN_ADMIN_CONTENT_H

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

