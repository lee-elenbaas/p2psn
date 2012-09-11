#ifndef __P2PSN_ADMIN_SERVER_APP_H
#define __P2PSN_ADMIN_SERVER_APP_H

#include "../node_admin_shared/admin_base_app.hpp"

namespace p2psn {
    namespace node_admin {

        /**
         * CppCMS Web interface for accessing the node configuration.
         */
        class admin_server_app : public admin_base_app {
        public:
            /**
             * Construct the app on the given cppcms service
             */
            admin_server_app(cppcms::service &);

            void server();
        };

    } // namespace node_admin
} // namespace p2psn

#endif // __P2PSN_ADMIN_SERVER_APP_H

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

