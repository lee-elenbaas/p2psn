/**
 * Content declarations for communication between the node_admin and its skin.
 *
 * The content types used by the node_admin to pass values into its skin for rendering the result HTML pages.
 */
#ifndef __P2PSN_ADMIN_USERS_CONTENT_H
#define __P2PSN_ADMIN_USERS_CONTENT_H

#include "admin_shared_content.hpp"
#include <map>

namespace p2psn {
    namespace node_admin {
        namespace content  {

			struct admin_user_state {
				bool allow_edit;
				bool allow_delete;
				bool allow_restore;

                std::string css_class;
                
                admin_user_state() 
					: allow_edit(true), allow_delete(true), allow_restore(false), css_class("existing")
                { }
			};

			typedef std::map<std::string, admin_user_state> admin_users_states_t;
			
            enum class admin_users_list_state {
                view,
                editing
            };

            struct base_user_form : public cppcms::form {
                cppcms::widgets::password user_password;
                cppcms::widgets::checkbox is_admin;
                cppcms::widgets::checkbox is_manager;
                cppcms::widgets::submit submit;
                
                base_user_form();
            };

            struct new_user_form : public base_user_form {
                cppcms::widgets::text user_name;

                new_user_form();
            };

            struct edited_user_form : public base_user_form {
                cppcms::widgets::hidden user_name;

                edited_user_form();
            };

            struct admin_users : public master {
                admin_users_list_state list_state;
                std::vector<user> users;
                admin_users_states_t user_states;
                admin_user_state cur_user_state;
                
                new_user_form new_user;
                edited_user_form edited_user;
            };

        } // namespace content
    } // namespace node_admin
} // namespace p2psn

namespace cppcms {
    namespace json {

        template<>
        struct traits<p2psn::node_admin::content::admin_user_state> {
            static p2psn::node_admin::content::admin_user_state get(const value&);
            static void set(value&, const p2psn::node_admin::content::admin_user_state&);
        };
        
        template<typename V>
        struct traits<std::map<std::string,V>> {
			static std::map<std::string,V> get(const value& val) {
				std::map<std::string,V> m;
				
				for(auto p : val.object())
					m[p.first]=traits<V>::get(p.second);
				
				return m;
			}
			static void set(value& v, const std::map<std::string,V> m) {
				for(auto p : m) {
					v.set(p.first, p.second);
				}
			}
		};

    } // namespace json
} // namespace cppcms

#endif // __P2PSN_ADMIN_USERS_CONTENT_H
