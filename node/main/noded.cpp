#include "../node_root/root_app.h"
#include <cppcms/applications_pool.h>
#include <cppcms/url_dispatcher.h>
#include "signal_handler.h"

/**
 * Main C++ application function
 */
int main(int argc,char ** argv)
{
	using namespace p2psn::main;
	using namespace p2psn::node_admin;

	try {
		signal::setup_signal_handlers();
		
		signal::sighup(true);
		
		while (signal::sighup()) {
			signal::sighup(false);
			
			cppcms::service srv(argc,argv);
			
			signal::srv(&srv);

			srv.applications_pool().mount(cppcms::applications_factory<root_app>());
			srv.run();

			signal::srv(nullptr);
		}

		return 0;
	}
	catch(std::exception const &e) {
		signal::srv(nullptr);

		std::cerr<<e.what()<<std::endl;
        
		return -1;
	}
}

// vim: tabstop=8 shiftwidth=8 softtabstop=8
