
#include "content.h"

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
login_form::login_form() {
    user_name.message("User name");
    user_password.message("Password");

    add(user_name);
    add(user_password);

    user_name.non_empty();
    user_password.non_empty();
}

/**
 * validate the login form
 */
bool content::login_form::validate() {
    /// Validate form for being filled completely
    if (!form::validate())
        return false;

    /// Validate login for matching user/pass combination in the settings
    //settings()
    return true;
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

