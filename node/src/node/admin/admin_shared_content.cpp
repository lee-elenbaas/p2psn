#include "admin_shared_content.hpp"

using namespace p2psn::node_admin::content;
using namespace std;
using namespace cppcms::json;
using namespace booster;

user traits<user>::get(const value& v) {
	if (v.type()!=json_type::is_object)
		throw bad_value_cast();

	user u;

	u.name = v.get<string>("user");
	u.password = v.get<string>("password");
	u.is_admin = v.get<bool>("is_admin");
	u.is_manager = v.get<bool>("is_manager");

	return u;
}

void traits<user>::set(value& v,const user& u) {
	v.set("user", u.name);
	v.set("password", u.password);
	v.set("is_admin", u.is_admin);
	v.set("is_manager", u.is_manager);
}
