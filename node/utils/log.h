/**
 * cryptographic tools used by p2psn
 *
 * providing easier to user API over the cryptografic tools cppcms provides
 */
#ifndef __LOG_H
#define __LOG_H

#include <booster/log.h>

#define LOG(lvl, msg) booster::log::logger::instance().log(booster::log::message(booster::log::level_type(lvl), std::string(msg).c_str(), __FILE__, __LINE__))

#endif // __LOG_H

