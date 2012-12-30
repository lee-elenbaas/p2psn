
#include "admin_users_content.hpp"

using namespace std;
using namespace p2psn::node_admin::content;
using namespace cppcms::json;

base_user_form::base_user_form() 
{
    user_password.message("Password");
    is_admin.message("Administrator");
    is_manager.message("Manager");
        
    add(user_password);
    add(submit);
    add(is_admin);
    add(is_manager);

    user_password.non_empty();
}

/**
 * Initial the new user form
 */
new_user_form::new_user_form() 
{
    user_name.message("User name");
    user_name.non_empty();

    submit.value("Add");

    add(user_name);
}

/**
 * Initial the new user form
 */
edited_user_form::edited_user_form() 
{
    submit.value("Update");
    add(user_name);
}

admin_user_state cppcms::json::traits<admin_user_state>::get(const value& v) {
	admin_user_state s;
	
	s.allow_edit = v.get<bool>("allow_edit");
	s.allow_delete = v.get<bool>("allow_delete");
	s.allow_restore = v.get<bool>("allow_restore");
	
	s.css_class = v.get<string>("css_class");
	
	return s;
}

void cppcms::json::traits<admin_user_state>::set(value& v, const admin_user_state& s) {
	v.set("allow_edit", s.allow_edit);
	v.set("allow_delete", s.allow_delete);
	v.set("allow_restore", s.allow_restore);

	v.set("css_class", s.css_class);
}
