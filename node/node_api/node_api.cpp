#include "node_api.h"

using namespace std;
using namespace p2psn::api;

node_api::node_api(cppcms::service& srv) : cppcms::rpc::json_rpc_server(srv)
{
	bind("echo",cppcms::rpc::json_method(&node_api::echo,this),method_role);
}

void node_api::echo(const string& message)
{
	return_result(message);
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
