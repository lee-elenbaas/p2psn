
#include "main_content.h"
#include "../utils/crypto.h"

using namespace std;
using namespace p2psn::node_app::content;

/**
 * Add an additional message to display to the user on the next rendered page.
 */
void master::add_message(string message /**< The message text */, string css /**< The message css class */) {
    user_messages.push_back({ message, css });
}

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

