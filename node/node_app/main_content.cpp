
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
login_form::login_form(cppcms::json::array admin_users) 
    : admin_users_(admin_users)
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

/**
 * Initiate the login page content
 */
login_page::login_page(cppcms::json::array admin_users)
    : login_info(admin_users) { }

/**
 * validate the login form
 */
bool login_form::validate() {
    /// Validate form for being filled completely
    if (!form::validate())
        return false;

    /// Validate login for matching user/pass combination in the settings
    for (auto user : admin_users_) {
        if (user["user"].str() != user_name.value())
            continue;

        // validate user password
        if (!user["password"].is_undefined() && (user["password"].str() != user_password.value()))
            break;

        // TODO: handle password signatures instead of open passwords
//        if (!user["password_hmac"].is_undefined()) {
//                        
//        }

        return true;
    }

    user_name.valid(false);
    return false;
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

