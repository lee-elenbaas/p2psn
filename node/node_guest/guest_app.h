#ifndef __P2PSN_MAIN_APP_H
#define __P2PSN_MAIN_APP_H

#include "../node_shared/base_app.h"
#include "../node_guest/guest_content.h"

namespace p2psn {
    namespace node_admin {

        /**
         * CppCMS Web interface for accessing the node configuration.
         */
        class guest_app : public base_app {
        public:
            /**
             * Construct the app on the given cppcms service
             */
            guest_app(cppcms::service &);
	
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
             * validate login user
             */
            bool validate_user(content::login_form&);
        };

    } // namespace node_admin
} // namespace p2psn

#endif // __P2PSN_MAIN_APP_H
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
