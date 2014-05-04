#include "offline_transport.hpp"

namespace p2psn {
	namespace transport {
		
		void offline_transport::send_message(contact to, object msg) {
			// * Serialize object to a new buffer
			// * Crypto msg using contact public key
			// * Sign message with my signature
			// * Generate & Send email to contact offline email
		}
		
		void offline_transport::handle_incoming_message(object msg) {
			// * Check if this is the newest version of the object avaliable
				// * Store the object in the local repository (If profile is synced, send a new sync message to other installations)
				// * Update the notification objects on the new object
				// * Update UI
		}

		void offline_transport::handle_sync_message(object msg) {
			// * Check if this is the newest version of the object avaliable
				// * Store the object in the local repository
				// * Update UI
		}
		
		void offline_transport::poll_incoming_messages() {
			// * Check for new emails on my offline transport email since last check
			// * For each new email
				// * If email is a p2psn incoming message
					// * Extract crypto object from the message
					// * Check crypto signature with email contact
					// * Decript object using my private key
					// * handle_incoming_message(msg)
		}

		void offline_transport::poll_sync_messages() {
			// * Check for new emails on my sync transport email since last check
			// * For each new email
				// * If email is a p2psn sync message
					// * Extract crypto object from the message
					// * Check crypto signature with my signature
					// * Decript object using my private key
					// * handle_sync_message(msg)
		}

		offline_transport::offline_transport() {
			// * If profile is synced
				// * poll_sync_messages()
				// * Start a thread for checking sync messages
			// * poll_incoming_messages()
			// * Start a thread for  checking incoming messages
		}

		offline_transport::~offline_transport() {
			// * If profile is synced
				// * Stop checking sync messages thread
			// * Stop checking incoming messages thread
		}
			
	} // namespace transport
} // namespace p2psn

#endif // __P2PSN_OFFLINE_TRANSPORT_H
