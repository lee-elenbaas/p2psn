#ifndef __P2PSN_BASE_APP_H
#define __P2PSN_BASE_APP_H

#include <cppcms/application.h>
#include <cppcms/service.h>

#include "base_content.h"

namespace p2psn {
    namespace node_admin {

        /**
         * CppCMS Web interface for accessing the node configuration.
         */
        class base_app : public cppcms::application {
        public:
            /**
             * Construct the app on the given cppcms service
             */
            base_app(cppcms::service &);
    
            /**
             * handle all incoming requests
             */	
            virtual void main(std::string);
        protected:
            /**
             * Shared inialization of page content
             */
            void init(content::master&);
        };

    } // namespace node_admin
} // namespace p2psn

#endif // __P2PSN_BASE_APP_H

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

