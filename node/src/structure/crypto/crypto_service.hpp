#ifndef __P2PSN_CRYPTO_SERVICE_H
#define __P2PSN_CRYPTO_SERVICE_H

#include "../crypto/primitives.hpp"

namespace p2psn {
	namespace entities {
		template<class Message>
		class encripted;

		template<class Message>
		class crypto_signed;

		class crypto_error : public std::
		class crypto_service {
			public:
				template<class Message>
				encripted<Message> encrypt(Message msg, crypto_key key) throw(crypto_error);
				
				template<class Message>
				Message decrypt(encripted<Message> msg, crypto_key key) throw(crypto_error);
				
				template<class Message>
				crypto_signed<Message> sign(Message msg, crypto_key key) throw(crypto_error);

				template<class Message>
				Message unsign(crypto_signed<Message> msg, crypto_key key) throw(crypto_error);
		}
		
	} // namespace entities
} // namespace p2psn

#endif // __P2PSN_CRYPTO_SERVICE_H
