#ifndef __P2PSN_MAIN_APP_H
#define __P2PSN_MAIN_APP_H

#include "base_app.h"
#include "content.h"

namespace p2psn {
    namespace node_app {

        /**
         * CppCMS Web interface for accessing the node configuration.
         */
        class main_app : public base_app {
        public:
            /**
             * Construct the app on the given cppcms service
             */
            main_app(cppcms::service &);
	
            /**
             * The initial page
             */
			void home();
			
			/**
			 * noded information page
			 */
            void info();
            /**
             * The about page
             */
            void about();
            /**
             * The login form page
             */
            void login();
            /**
             * The logout operation
             */
            void logout();
            /**
             * The admin menu
             */
            void admin();
            /**
             * Manage admin users
             */
            void admin_users();
            /**
             * Manage server
             */
            void admin_server();
        private:
            /**
             * validate login user
             */
            bool validate_user(content::login_form&);
        };

    } // namespace node_app
} // namespace p2psn

#endif // __P2PSN_MAIN_APP_H
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
