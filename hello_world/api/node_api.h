//#include <cppcms/application.h>
#include <cppcms/service.h>
//#include <cppcms/applications_pool.h>
#include <cppcms/rpc_json.h>

class json_service : public cppcms::rpc::json_rpc_server {
public:
    json_service(cppcms::service &srv);
    void echo(std::string message);
};

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
