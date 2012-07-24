/**
 * Content declarations for communication between the node_app and its skin.
 *
 * The content types used by the node_app to pass values into its skin for rendering the result HTML pages.
 */
#ifndef __P2PSN_MAIN_CONTENT_H
#define __P2PSN_MAIN_CONTENT_H

#include <cppcms/view.h>
#include <cppcms/form.h>
#include <cppcms/json.h>
#include <string>
#include <array>

namespace p2psn {
    namespace node_app {
        namespace content  {

            /**
             * introduce the std::string as string into this namespace - it is used as primitive a lot, so worth the introduction
             */
            using std::string;

            /**
             * Collection of messages to display to the user.
             */	
            typedef std::vector<std::pair<string, string>> messages_list;

            /**
             * Content data shared by all pages
             */
            struct master : public cppcms::base_content {
	        public:
                /** 
                 *Rendered page title 
                 */
                string title; 
                /**
                 * Currently logged in user
                 */ 
		        string user_name;
                /**
                 * Messages to render to the user
                 */
		        messages_list user_messages;
		
                /**
                 * Add message to display to the user.
                 */
		        void add_message(string, string);
            };

            struct info : public master {
                double port;
                string host;
            };

            struct login_form : public cppcms::form {
                cppcms::widgets::text user_name;
                cppcms::widgets::password user_password;
                cppcms::widgets::submit submit;

                login_form();
            };

            struct login_page : public master {
                login_form login_info;
            };

        } // namespace content
    } // namespace node_app
} // namespace p2psn

#endif // __P2PSN_MAIN_CONTENT_H

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

