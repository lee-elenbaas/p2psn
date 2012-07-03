
#include "signal_handlers.h"

// TODO: need to handle win32 case using #ifdef
#include <signal.h>
#include <errono.h>

signal_handler::signal_handler(sppcms::service& srv, int sig) throw (signal_setup_exception)
	: _srv(srv), _signal(sig)
{
	signal(sig, signal_handler::handler)
}

