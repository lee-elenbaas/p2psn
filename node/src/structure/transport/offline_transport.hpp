#ifndef __P2PSN_OFFLINE_TRANSPORT_H
#define __P2PSN_OFFLINE_TRANSPORT_H

#include "../entities/contact.hpp"

namespace p2psn {
	namespace transport {
		
		class offline_transport {
			private:
				void handle_message(object msg);
				void poll_incoming_messages();
				void poll_sync_messages();
			public:
				void send_message(contact to, object msg);
				offline_transport();
				~offline_transport();
		};
		
	} // namespace transport
} // namespace p2psn

#endif // __P2PSN_OFFLINE_TRANSPORT_H
