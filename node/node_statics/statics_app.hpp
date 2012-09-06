#ifndef __P2PSN_STATICS_APP_H
#define __P2PSN_STATICS_APP_H

#include "../node_shared/base_app.hpp"
#include "../node_guest/guest_content.hpp"

namespace p2psn {
    namespace node_admin {

        /**
         * CppCMS Web interface for accessing the node configuration.
         */
        class statics_app : public base_app {
        public:
            /**
             * Construct the app on the given cppcms service
             */
            statics_app(cppcms::service&, const std::string&);
    
            /**
             * handle all incoming requests
             */	
            virtual void main(std::string);
        };

    } // namespace node_admin
} // namespace p2psn

#endif // __P2PSN_STATICS_APP_H
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
