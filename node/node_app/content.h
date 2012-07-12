/**
 * Content declarations for communication between the node_app and its skin.
 *
 * The content types used by the node_app to pass values into its skin for rendering the result HTML pages.
 */
#ifndef __CONTENT_H
#define __CONTENT_H

#include <cppcms/view.h>
#include <cppcms/form.h>
#include <string>
#include <array>

namespace p2psn {
    namespace node_app {
        namespace content  {

            /**
             * Collection of messages to display to the user.
             */	
            typedef std::vector<std::pair<std::string, std::string>> messages_list;

            /**
             * Content data shared by all pages
             */
            struct master : public cppcms::base_content {
	        public:
                /** 
                 *Rendered page title 
                 */
                std::string title; 
                /**
                 * Currently logged in user
                 */ 
		        std::string user_name;
                /**
                 * Messages to render to the user
                 */
		        messages_list user_messages;
		
                /**
                 * Add message to display to the user.
                 */
		        void add_message(std::string, std::string);
            };

            struct page : public master {
                std::string page_content;
            };

            struct login_form : public cppcms::form {
                cppcms::widgets::text user_name;
                cppcms::widgets::password user_password;
                cppcms::widgets::submit submit;

                login_form();
                virtual bool validate();
            };

            struct login_page : public page {
                login_form login_info;
            };

        } // namespace content
    } // namespace node_app
} // namespace p2psn

#endif // __CONTENT_H
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

