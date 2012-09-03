
#include "base_content.hpp"

using namespace std;
using namespace p2psn::node_admin::content;
using namespace cppcms::json;

static message traits<message>::get(const value& v) {
    message m;

    m.message_str = v.get<string>("message");
    m.css_class = v.get<string>("cssClass");

    return m;
}

static void traits<message>::set(value& v, const message& m) {
    v.set("message", m.message_str);
    v.set("cssClass", m.css_class);
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

