
#include "admin_users_content.hpp"

using namespace std;
using namespace p2psn::node_admin::content;

/**
 * Initial the new user form
 */
new_user_form::new_user_form() 
{
    user_name.message("User name");
    user_password.message("Password");
    submit.value("Add");
        
    add(user_name);
    add(user_password);
    add(submit);

    user_name.non_empty();
    user_password.non_empty();
}

/**
 * Initial the new user form
 */
edited_user_form::edited_user_form() 
{
    user_password.message("Password");
    submit.value("Update");
        
    add(user_name);
    add(user_password);
    add(submit);

    user_password.non_empty();
}
