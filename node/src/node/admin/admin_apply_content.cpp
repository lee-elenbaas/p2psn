
#include "admin_apply_content.hpp"

using namespace std;
using namespace p2psn::node_admin::content;

/**
 * Initial the new user form
 */
apply_form::apply_form() 
{
    submit.value("Apply new configuration");
        
    add(submit);
}

