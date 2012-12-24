
#include "admin_apply_content.hpp"

using namespace std;
using namespace p2psn::node_admin::content;

/**
 * Initial the new user form
 */
apply_form::apply_form() 
{
	apply_password.message("Password");
    submit.value("Apply new configuration");
        
    add(apply_password);
    add(submit);
    
    apply_password.non_empty();
}

