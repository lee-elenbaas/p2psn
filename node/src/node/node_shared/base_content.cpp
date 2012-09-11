/**
 * Content declarations for communication between the node_admin and its skin.
 *
 * The content types used by the node_admin to pass values into its skin for rendering the result HTML pages.
 */

#include "base_content.hpp"

using namespace p2psn::node_admin::content;
using namespace cppcms::json;
using namespace std;

message traits<message>::get(const value& v) {
    message m;

    m.message_str = v.get<std::string>("message");
    m.css_class = v.get<std::string>("cssClass");

    return m;
}
void traits<message>::set(value& v, const message& m) {
    v.set("message", m.message_str);
    v.set("cssClass", m.css_class);
}

messages_list traits<messages_list>::get(const value& v) {
    messages_list ml;

    ml.add(traits<vector<message>>::get(v));

    return ml;
}
void traits<messages_list>::set(value& v, const messages_list& ml) {
    traits<vector<message>>::set(v, ml);
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

