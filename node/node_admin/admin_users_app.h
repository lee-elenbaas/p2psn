#ifndef __P2PSN_ADMIN_USERS_APP_H
#define __P2PSN_ADMIN_USERS_APP_H

#include "../node_admin/admin_base_app.h"
#include "admin_users_content.h"

namespace p2psn {
    namespace node_admin {

        /**
         * CppCMS Web interface for accessing the node configuration.
         */
        class admin_users_app : public admin_base_app {
        public:
            /**
             * Construct the app on the given cppcms service
             */
            admin_users_app(cppcms::service &);

            /**
             * Manage admin users
             */
            void admin_users();

            /**
             * Add a new user
             */
            void add_user();

            /**
             * Edit an existing user
             */
            void edit_user();

            /**
             * Remove a user user
             */
            void delete_user();

            /**
             * Restore a deleted user
             */
            void restore_user();
        private:
            cppcms::json::value new_config();
            void new_config(const cppcms::json::value&);

            /**
             * show admin users page
             */
            void admin_users_show(content::admin_users);
        };

    } // namespace node_admin
} // namespace p2psn

#endif // __P2PSN_ADMIN_USERS_APP_H

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

