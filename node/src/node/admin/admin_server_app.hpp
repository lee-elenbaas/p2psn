#ifndef __P2PSN_ADMIN_SERVER_APP_H
#define __P2PSN_ADMIN_SERVER_APP_H

#include "admin_base_app.hpp"
#include "admin_server_content.hpp"

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
            
            void connection();
        private:
            void port(int);
            int port();

            /**
             * redirect user back to admin users list
             */
            void redirect_to_admin_server() { response_redirect("/node/admin/server"); }
            
            void admin_server_show(content::admin_server&);
        };

    } // namespace node_admin
} // namespace p2psn

#endif // __P2PSN_ADMIN_SERVER_APP_H
