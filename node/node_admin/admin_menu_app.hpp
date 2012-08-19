#ifndef __P2PSN_ADMIN_APP_H
#define __P2PSN_ADMIN_APP_H

#include "../node_admin/admin_base_app.h"

namespace p2psn {
    namespace node_admin {

        /**
         * CppCMS Web interface for accessing the node configuration.
         */
        class admin_menu_app : public admin_base_app {
        public:
            /**
             * Construct the app on the given cppcms service
             */
            admin_menu_app(cppcms::service &);
    
            /**
             * The admin menu
             */
			void admin_menu();
        };

    } // namespace node_admin
} // namespace p2psn

#endif // __P2PSN_ADMIN_APP_H

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

