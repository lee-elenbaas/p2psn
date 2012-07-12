#ifndef __MAIN_APP_H
#define __MAIN_APP_H

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
             * The shared initial page
             */
            void info(content::page&);
        };

    } // namespace node_app
} // namespace p2psn

#endif // __MAIN_APP_H
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
