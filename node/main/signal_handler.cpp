
#include "signal_handler.h"

// TODO I#6: need to handle win32 case using #ifdef
#include <errno.h>

namespace p2psn {
namespace main {
namespace signal {

namespace {
	cppcms::service* srv_ = nullptr;
	bool sigterm_ = false;
	bool sigint_ = false;
	bool sighup_ = false;

	void sigterm_handler(int) {
		sigterm_ = true;

		if (srv_ != nullptr)
			srv_->shutdown();
	}

	void sigint_handler(int) {
		sigint = true;

		if (srv_ != nullptr)
			srv_->shutdown();
	}

	void sighup_handler(int) {
		sighup_ = true;

		if (srv_ != nullptr)
			srv_->shutdown();
	}
}

cppcms::service* srv() { return srv_; }
void srv(cppcms::service* srv) { srv_ = srv; }

bool sigterm() { return sigterm_; }
void sigterm(bool sigterm) { sigterm_ = sigterm; }

bool sigint() { return sigint_; }
void sigint(bool sigint) { sigint_ = sigint; }

bool sighup() { return sighup_; }
void sighup(bool sighup) { sighup_ = sighup; }

void setup_signal_handlers() throw (signal_setup_exception) {
	// Terminate signal
	if (SIG_ERR == ::signal(SIGTERM, sigterm_handler))
		throw signal_setup_exception("Error setting up signal handler: SIGTERM");

	// Ctrl-C in console
	if (SIG_ERR == ::signal(SIGINT, sigint_handler))
		throw signal_setup_exception("Error setting up signal handler: SIGINT");

	// Reload configuration
	if (SIG_ERR == ::signal(SIGHUP, sighup_handler))
		throw signal_setup_exception("Error setting up signal handler: SIGHUP");
}

} // namespace signal
} // namespace main
} // namespace p2psn

