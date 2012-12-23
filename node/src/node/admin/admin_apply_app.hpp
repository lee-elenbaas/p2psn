#ifndef __P2PSN_ADMIN_APPLY_APP_H
#define __P2PSN_ADMIN_APPLY_APP_H

#include "admin_base_app.hpp"
#include "admin_apply_content.hpp"

namespace p2psn {
    namespace node_admin {

        /**
         * CppCMS Web interface for accessing the node configuration.
         */
        class admin_apply_app : public admin_base_app {
        public:
            /**
             * Construct the app on the given cppcms service
             */
            admin_apply_app(cppcms::service &);

            void apply();
            
            void set();
        private:
            /**
             * redirect user back to admin users list
             */
            void redirect_to_admin_apply() { response_redirect("/node/admin/apply"); }
            
            void admin_apply_show(content::admin_apply&);
        };

    } // namespace node_admin
} // namespace p2psn

#endif // __P2PSN_ADMIN_APPLY_APP_H
