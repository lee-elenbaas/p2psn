#ifndef __P2PSN_ADMIN_APP_H
#define __P2PSN_ADMIN_APP_H

#include "base_app.h"
//#include "admin_content.h"

namespace p2psn {
    namespace node_app {

        /**
         * CppCMS Web interface for accessing the node configuration.
         */
        class admin_app : public base_app {
        public:
            /**
             * Construct the app on the given cppcms service
             */
            admin_app(cppcms::service &);
    
            /**
             * handle all incoming requests
             */	
            virtual void main(std::string);

            /**
             * The admin menu
             */
			void home();

            /**
             * Manage admin users
             */
            void users();
            /**
             * Manage server
             */
            void server();
        };

    } // namespace node_app
} // namespace p2psn

#endif // __P2PSN_ADMIN_APP_H

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

