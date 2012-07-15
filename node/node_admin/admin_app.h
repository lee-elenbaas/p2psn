#ifndef __ADMIN_APP_H
#define __ADMIN_APP_H

#include <cppcms/application.h>
#include <cppcms/service.h>

#include "admin_content.h"

namespace p2psn {
    namespace node_admin {

        /**
         * CppCMS Web interface for accessing the node configuration.
         */
        class admin_app : public cppcms::application {
        public:
            /**
             * Construct the app on the given cppcms service
             */
            admin_app(cppcms::service &);
	
            /**
             * The initial page
             */
			void menu();

        private:
            /**
             * Shared inialization of page content
             */
            void init(content::master&);
        };

    } // namespace node_admin
} // namespace p2psn

#endif // __ADMIN_APP_H
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
