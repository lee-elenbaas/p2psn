#ifndef __P2PSN_ADMIN_APP_H
#define __P2PSN_ADMIN_APP_H

#include "../node_shared/base_app.h"

namespace p2psn {
    namespace node_admin {

        /**
         * CppCMS Web interface for accessing the node configuration.
         */
        class root_app : public base_app {
        public:
            /**
             * Construct the app on the given cppcms service
             */
            root_app(cppcms::service &);
    
			/**
			 * Redirect to the default local that fits the client settings
			 */
			redirect();
			
            /**
             * handle all incoming requests
             */	
            virtual void main(std::string);
        };

    } // namespace node_admin
} // namespace p2psn

#endif // __P2PSN_ADMIN_APP_H

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

