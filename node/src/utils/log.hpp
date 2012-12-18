#ifndef __LOG_H
#define __LOG_H

#include <cassert>
#include <string>
#include <booster/log.h>
#include <typeinfo>

namespace p2psn {
	namespace utils {

		using booster::log::level_type;

	} // namespace utils
} // namepsace p2psn

#ifndef NDEBUG
	#define SLOG(lvl, msg) booster::log::logger::instance().log(booster::log::message(p2psn::utils::level_type(lvl), std::string(msg).c_str(), __FILE__, __LINE__))
	#define LOG(lvl, msg) SLOG((lvl), std::string(typeid(*this).name())+": "+(msg))
#else
	#define SLOG(lvl, msg) 
	#define LOG(lvl, msg) 
#endif

#define DEBUG(msg) LOG(p2psn::utils::level_type::debug, (msg))
#define SDEBUG(msg) SLOG(p2psn::utils::level_type::debug, (msg))

#endif // __LOG_H

