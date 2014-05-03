#ifndef __P2PSN_CONTACT_H
#define __P2PSN_CONTACT_H

#include <string>
#include "object.hpp"

namespace p2psn {
	namespace entities {
		
		class contact : public object {
			public:
				std::string display_name;
				
				std::string signature; // cryptographic signature to validate content coming from the conact
				
				std::string offline_transport_email; // how to send messages to the contact
				std::string watch_transport_url; // how to check contact for updates
				std::string online_tranport_channel; // how to communicate p2p with the conact for real time changes
		};
		
	} // namespace entities
} // namespace p2psn

#endif // __P2PSN_CONTACT_H
