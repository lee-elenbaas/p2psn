
#include "serialization.hpp"

#include <cppcms/json.h>

using namespace p2psn::utils;
using namespace cppcms::json;
using namespace std;

template<>
string serialization<value>::serialize(const value& v) {
	return v.save();
}

template<>
value serialization<value>::deserialize(const string& s) {
	value v;

	v.load(istringstream(s));

	return v;
}

