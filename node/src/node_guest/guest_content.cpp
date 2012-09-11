
#include "guest_content.hpp"

using namespace std;
using namespace p2psn::node_admin::content;

/**
 * Initial the login form
 */
login_form::login_form() 
{
    user_name.message("User name");
    user_password.message("Password");
    submit.value("Login");
        
    add(user_name);
    add(user_password);
    add(submit);

    user_name.non_empty();
    user_password.non_empty();
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

