
#ifndef __SIGNAL_HANDLERS_H
#define __SIGNAL_HANDLERS_H

#include <stdexcept>

class signal_setup_exception : public std::runtime_error {
public:
	signal_setup_exception(const std::string& message) : std::runtime_error(message) {}
};

class signal_handler {
public:
	signal_handler(sppcms::service& srv, int signal) throw (signal_setup_exception);
	~signal_handler();

	bool signal_recieved() const { return _signal_recieved; }
	void reset_signal() { _signal_recieved = false; }
private:
	cppcms::service& _srv;
	int _signal;
	bool _signal_recieved = false;

	void handler();
};

#endif // __SIGNAL_HANDLERS_H
