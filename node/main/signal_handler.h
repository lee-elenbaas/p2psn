
#ifndef __SIGNAL_HANDLER_H
#define __SIGNAL_HANDLER_H

#include <cppcms/service.h>
#include <signal.h> // TODO I#6: handle win 32 compilation issues
#include <stdexcept>

namespace p2psn {
namespace main {
namespace signal {

cppcms::service* srv();
void srv(cppcms::service*);

bool sigterm();
void sigterm(bool);

bool sigint();
void sigint(bool);

bool sighup();
void sighup(bool);

class signal_setup_exception : public std::runtime_error {
public:
	signal_setup_exception(const std::string& message) : std::runtime_error(message) {}
};

void setup_signal_handlers() throw (signal_setup_exception);

} // namespace signal
} // namespace main
} // namespace p2psn

#endif // __SIGNAL_HANDLER_H
