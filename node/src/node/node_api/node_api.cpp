#include "node_api.hpp"

using namespace std;
using namespace p2psn::api;

node_api::node_api(cppcms::service& srv) : cppcms::rpc::json_rpc_server(srv)
{
	bind("echo",cppcms::rpc::json_method(&node_api::echo,this),method_role);
	bind("version",cppcms::rpc::json_method(&node_api::version,this),method_role);
}

void node_api::version()
{
	return_result("P2Psn v0.0.2");
}

void node_api::echo(const string& message)
{
	return_result(message);
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
