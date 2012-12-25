
#include "admin_users_content.hpp"

using namespace std;
using namespace p2psn::node_admin::content;
using namespace cppcms::json;

base_user_form::base_user_form() 
{
    user_name.message("User name");
    user_password.message("Password");
    is_admin.message("Administrator");
    is_manager.message("Manager");
        
    add(user_name);
    add(user_password);
    add(submit);
    add(is_admin);
    add(is_manager);

    user_name.non_empty();
    user_password.non_empty();
}

/**
 * Initial the new user form
 */
new_user_form::new_user_form() 
{
    submit.value("Add");
}

/**
 * Initial the new user form
 */
edited_user_form::edited_user_form() 
{
    submit.value("Update");
}

template<>
admin_user_state traits<admin_user_state>::get(const value& v) {
	s.is_changed = v.get<bool>("is_changed");
	s.is_removed = v.get<bool>("is_removed");
}

template<>
void traits<admin_user_state>set(value& v, const admin_user_state& s) {
	v.set("is_changed", s.is_changed);
	v.set("is_removed", s.is_removed);
}
