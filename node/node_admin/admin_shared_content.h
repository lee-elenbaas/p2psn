/**
 * Content declarations for communication between the node_admin and its skin.
 *
 * The content types used by the node_admin to pass values into its skin for rendering the result HTML pages.
 */
#ifndef __P2PSN_ADMIN_SHARED_CONTENT_H
#define __P2PSN_ADMIN_SHARED_CONTENT_H

#include "../node_shared/base_content.h"

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
                string name;
                string password;
                admin_user_state user_state;
            };

        } // namespace content
    } // namespace node_admin
} // namespace p2psn

namespace boost {
    namespace serialization {

        /**
         * serialization support to the admin user
         */
        template<class Archive>
        void serialize(Archive & ar, p2psn::node_admin::content::user & u, const unsigned int version)
        {
            ar & u.name;
            ar & u.password;
            ar & u.user_state;
        }

    } // namespace serialization
} // namespace boost

#endif // __P2PSN_ADMIN_SHARED_CONTENT_H

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

