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
             * Messages to be displayed to the user
             */	
            struct message {
                std::string message_str;
                std::string css_class;
            }

            /**
             * Collection of messages to display to the user.
             */	
            class messages_list : public std::vector<message> {
            public:
                void add(const std::string& message, const string& css) {
                    push_back(message({message, css}));
                }
            };

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
		        void add_message(const std::string& str, const std::string& css) {
                    user_messages.add(str, css);
                }
            };

        } // namespace content
    } // namespace node_admin
} // namespace p2psn

namespace cppcms {
    namespace json {

        template<>
        traits<p2psn::node_admin::content::message> {
            static p2psn::node_admin::content::message get(const value&);
            static void set(value&, const p2psn::node_admin::content::message&);
        };

    } // namespace json
} // namespace cppcms

#endif // __P2PSN_BASE_CONTENT_H

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

