
#include "signal_handlers.h"

// TODO I#6: need to handle win32 case using #ifdef
#include <errono.h>

signal_handler::signal_handler(int sig) throw (signal_setup_exception)
	: _signal(sig)
{
	if (SIG_ERR == signal(sig, signal_handler::handler))
		throw signal_exception("Error setting up signal handler");
}

void signal_handler::handler(int)
{
	_signal_recieved = true;
	
	if (nullptr != _srv)
		_srv->shutdown();
}
