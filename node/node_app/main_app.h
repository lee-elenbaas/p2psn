#ifndef __MAIN_APP_H
#define __MAIN_APP_H

#include <cppcms/application.h>
#include <cppcms/service.h>

#include "main_content.h"

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
        private:
            /**
             * Shared inialization of page content
             */
            void init(content::master&);
            /**
             * validate login user
             */
            validate_user(login_form&);
        };

    } // namespace node_app
} // namespace p2psn

#endif // __MAIN_APP_H
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
