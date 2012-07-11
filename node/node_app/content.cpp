
#include "content.h"

using namespace std;
using namespace content;

void master::add_message(string message, string css) {
	user_messages.push_back({ message, css });
}

login_form::login_form() {
    user_name.message("User name");
    user_password.message("Password");

    add(user_name);
    add(user_password);

    user_name.non_empty();
    user_password.non_empty();
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

