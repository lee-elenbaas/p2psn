
#ifndef __SIGNAL_HANDLERS_H
#define __SIGNAL_HANDLERS_H

#include <signal.h> // TODO I#6: handle win 32 compilation issues
#include <stdexcept>

class signal_setup_exception : public std::runtime_error {
public:
	signal_setup_exception(const std::string& message) : std::runtime_error(message) {}
};

class signal_handler {
public:
	signal_handler(sppcms::service& srv, int signal) throw (signal_setup_exception);
	~signal_handler() = default; // no need to handle signal removal

	bool recieved() const { return _signal_recieved; }
	void reset_recieved() { _signal_recieved = false; }
	void set_recieved(bool _recieved) { _signal_recieved = recieved; }
	
	void set_srv(cppcms::service* srv) { _srv = srv; }
private:
	cppcms::service* _srv = nullptr;
	int _signal;
	bool _signal_recieved = false;

	void handler(int);
};

#endif // __SIGNAL_HANDLERS_H
