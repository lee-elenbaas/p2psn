#include "../node_app/main_app.h"
#include <cppcms/applications_pool.h>
#include <cppcms/url_dispatcher.h>
#include "signal_handler.h"

int main(int argc,char ** argv)
{
    using namespace p2psn::main;

    try {
		signal::setup_signal_handlers();
		
		signal::set_sighup(true);
		
		while (signal::sighup()) {
			signal::set_sighup(false);
			
			cppcms::service srv(argc,argv);
			
			signal::set_srv(&srv);

			srv.applications_pool().mount(cppcms::applications_factory<main_app>());
			srv.run();

            signal::set_srv(nullptr);
		}

        return 0;
    }
    catch(std::exception const &e) {
        signal::set_srv(nullptr);

        std::cerr<<e.what()<<std::endl;
        
        return -1;
    }
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
