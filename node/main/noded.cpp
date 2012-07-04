#include "main/main_app.h"
#include <cppcms/applications_pool.h>
#include <cppcms/url_dispatcher.h>
#include "signal_handler.h"

int main(int argc,char ** argv)
{
    try {
        cppcms::service srv(argc,argv);
		
		signal_handler sigterm(srv, SIGTERM);
		signal_handler sighup(srv, SIGHUP);
        srv.applications_pool().mount(cppcms::applications_factory<main_app>());
		
		sighup.set_recieved(true);
		
		while (sighup.recieved()) {
			sighup.clear_recieved();
			srv.run();
		}
    }
    catch(std::exception const &e) {
        std::cerr<<e.what()<<std::endl;
    }
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
