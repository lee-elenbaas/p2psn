
#include "content.h"

content::login_form::login_form() {
    user_name.message("User name");
    user_password.message("Password");

    add(user_name);
    add(user_password);

    user_name.non_empty();
    user_password.non_empty();
}

bool content::login_form::validate() {
    if (!form::validate())
        return false;

//    settings().
    return true;
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

