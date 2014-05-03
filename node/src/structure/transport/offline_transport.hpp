#ifndef __P2PSN_OFFLINE_TRANSPORT_H
#define __P2PSN_OFFLINE_TRANSPORT_H

#include <func>
#include "../entities/contact.hpp"

namespace p2psn {
	namespace transport {
		
		typedef std::func<object, nullptr> message_handler; // TODO: check syntax
		
		class offline_transport {
			public:
				void send_message(contact to, object msg) = 0;
				
				void register_message_handler(message_handler) = 0;
				void unregister_message_handler(message_handler) = 0;
		};
		
	} // namespace transport
} // namespace p2psn

#endif // __P2PSN_OFFLINE_TRANSPORT_H
