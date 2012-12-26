
#include "admin_server_content.hpp"

using namespace std;
using namespace p2psn::node_admin::content;

/**
 * Initial the new user form
 */
connection_form::connection_form() 
{
    port.message("Listening Port");
    submit.value("Set");
        
    add(port);
    add(submit);

    port.non_empty();
    port.range(1, 49151);
}
