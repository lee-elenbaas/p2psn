/**
 * cryptographic tools used by p2psn
 *
 * providing easier to user API over the cryptografic tools cppcms provides
 */
#ifndef __LOG_H
#define __LOG_H

#include <booster/log.h>
#include <typeinfo>

namespace p2psn {
	namespace utils {

	using booster::log::level_type;

	} // namespace utils
} // namepsace p2psn

#define SLOG(lvl, msg) booster::log::logger::instance().log(booster::log::message(p2psn::utils::level_type(lvl), std::string(msg).c_str(), __FILE__, __LINE__))

#define LOG(lvl, msg) SLOG((lvl), std::string(typeid(*this).name())+": "+(msg))

#endif // __LOG_H

