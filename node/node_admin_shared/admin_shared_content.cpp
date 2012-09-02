#include "admin_shared_content.hpp"

using namespace p2psn::node_admin::content;
using namespace std;
using namespace cppcms::json;

admin_user_state traits<admin_user_state>::get(const value& v) {
    if (v.is_undefined() || v.is_null())
        return admin_user_state::existing_user;

    return static_cast<admin_user_state>(v.get_value<int>());
}

void traits<admin_user_state>::set(value& v,const admin_user_state& s) {
    if (s == admin_user_state::existing_user)
        v.undefined();
    else
        v.set_value(static_cast<int>(s));
}

user traits<user>::get(const value& v) {
    if (v.type()!=json_type::is_object)
        throw bad_value_cast();

    user u;

    u.name = v.get<string>("user");
    u.password = v.get<string>("password");
    u.user_state = v.get<admin_user_state>("state");

    return u;
}

void traits<user>::set(value& v,const user& u) {
    v.set("user", u.name);
    v.set("password", u.password);
    v.set("state", u.user_state);
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

