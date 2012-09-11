#ifndef __P2PSN_BASE_APP_H
#define __P2PSN_BASE_APP_H

#include <cppcms/application.h>
#include <cppcms/service.h>

#include "base_content.hpp"
#include "../utils/serialization.hpp"
#include "../utils/log.hpp"

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

            /**
             * redirect to a new url - and place a log message in there
             */
            void response_redirect(std::string);
        protected:
            /**
             * Shared inialization of page content
             */
            void init(content::master&);
            /**
             * Add message to show the user into the session
             */
            void add_message(const std::string&, const std::string&);
            /**
             * Get current messages in the session
             */
            content::messages_list messages();

            /**
             * Get serialized value from session
             */
            template<typename T>
            T session_get(const std::string& key) {
                return utils::serialization<T>::deserialize(session().get(key));
            }
            /**
             * Get serialized value from session with default value in case no information in the session
             */
            template<typename T>
            T session_get(const std::string& key, const T& def) {
                return utils::serialization<T>::deserialize(session().get(key, utils::serialization<T>::serialize(def)));
            }
            /**
             * Set serialized value to session
             */
            template<typename T>
            void session_set(const std::string& key, const T& value) {
                session().set(key, utils::serialization<T>::serialize(value));
            }
        };

    } // namespace node_admin
} // namespace p2psn

#endif // __P2PSN_BASE_APP_H

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

