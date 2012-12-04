#ifndef __P2PSN_ADMIN_BASE_APP_H
#define __P2PSN_ADMIN_BASE_APP_H

#include "../shared/base_app.hpp"
#include "../admin_shared/admin_shared_content.hpp"
#include <vector>

namespace p2psn {
    namespace node_admin {

        /**
         * CppCMS Web interface for accessing the node configuration.
         */
        class admin_base_app : public base_app {
        public:
            /**
             * Construct the app on the given cppcms service
             */
            admin_base_app(cppcms::service &);
        protected:
            /**
             * The new settings to be applied
             */
            cppcms::json::value new_settings();
            /**
             * Set a new settings to be applied
             */
            void new_settings(const cppcms::json::value&);
            /**
             * Whether a new settings has been saved
             */
            bool has_new_settings();
        };

    } // namespace node_admin
} // namespace p2psn

#endif // __P2PSN_ADMIN_BASE_APP_H

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

