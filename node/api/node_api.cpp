#include "node_api.h"

json_service :: json_service(cppcms::service &srv) : cppcms::rpc::json_rpc_server(srv)
{
	bind("echo",cppcms::rpc::json_method(&json_service::echo,this),method_role);
}

void json_service:: echo(std::string message)
{
	return_result(message);
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
