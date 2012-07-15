
#include "admin_content.h"
#include "../utils/crypto.h"

using namespace std;
using namespace p2psn::node_admin::content;

/**
 * Add an additional message to display to the user on the next rendered page.
 */
void master::add_message(string message /**< The message text */, string css /**< The message css class */) {
    user_messages.push_back({ message, css });
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

