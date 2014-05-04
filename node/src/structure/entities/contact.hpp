#ifndef __P2PSN_CONTACT_H
#define __P2PSN_CONTACT_H

#include "primitives.hpp"
#include "object.hpp"

namespace p2psn {
	namespace entities {
		
		class contact : public object {
			private:
				string display_name;
				
				crypto_key signature; // cryptographic signature to validate content coming from the contact
				crypto_key public_key; // cryptographic public key to send content to the contact
				
				email offline_transport_email; // how to send messages to the contact
				url watch_transport_url; // how to check contact for updates
				channel online_tranport_channel; // how to communicate p2p with the conact for real time changes
		};
		
	} // namespace entities
} // namespace p2psn

#endif // __P2PSN_CONTACT_H
