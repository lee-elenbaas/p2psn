#ifndef __P2PSN_NODE_API_H
#define __P2PSN_NODE_API_H

#include <cppcms/service.h>
#include <cppcms/rpc_json.h>

namespace p2psn {
    namespace api {

        class node_api : public cppcms::rpc::json_rpc_server {
        public:
            node_api(cppcms::service&);

            void echo(const std::string&);
        };

    } // namespace api
} // namespace p2psn

#endif

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

