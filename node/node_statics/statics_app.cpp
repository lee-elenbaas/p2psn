#include "../node_statics/statics_app.hpp"

#include <ifstream>

using namespace p2psn::node_admin;
using namespace std;
using namespace cppcms::json;

statics_app::statics_app(cppcms::service &srv) 
    : base_app(srv) 
{
}

void statics_app::main(string url) {
 // TODO: serve the CSS as a first step - then convert the statics files into hashed names on the make - and serve files using the hash of the requests as step 2   
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
