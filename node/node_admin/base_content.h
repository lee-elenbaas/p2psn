/**
 * Content declarations for communication between the node_admin and its skin.
 *
 * The content types used by the node_admin to pass values into its skin for rendering the result HTML pages.
 */
#ifndef __P2PSN_BASE_CONTENT_H
#define __P2PSN_BASE_CONTENT_H

#include <cppcms/view.h>
#include <cppcms/form.h>
#include <cppcms/json.h>
#include <string>
#include <array>

namespace p2psn {
    namespace node_admin {
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

        } // namespace content
    } // namespace node_admin
} // namespace p2psn

#endif // __P2PSN_BASE_CONTENT_H

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

