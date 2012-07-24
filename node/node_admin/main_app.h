#ifndef __P2PSN_MAIN_APP_H
#define __P2PSN_MAIN_APP_H

#include <cppcms/application.h>
#include <cppcms/service.h>

#include "content.h"

namespace p2psn {
    namespace node_app {

        /**
         * CppCMS Web interface for accessing the node configuration.
         */
        class main_app : public cppcms::application {
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
             * Shared inialization of page content
             */
            void init(content::master&);
            /**
             * validate login user
             */
            bool validate_user(content::login_form&);
            /**
             * check that user is an admin user
             */
            bool ensure_admin_user();
        };

    } // namespace node_app
} // namespace p2psn

#endif // __P2PSN_MAIN_APP_H
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
