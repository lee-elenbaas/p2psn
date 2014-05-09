#ifndef __P2PSN_CRYPTO_SERVICE_H
#define __P2PSN_CRYPTO_SERVICE_H

#include "../crypto/primitives.hpp"
#include "../utility/exception.hpp"
#include <stdexcept>

namespace p2psn {
	namespace entities {
		template<class Message>
		class encripted;

		template<class Message>
		class crypto_signed;

		DEFINE_EXCEPTION(crypto_error, std::runtime_error);
		DEFINE_EXCEPTION(signature_error, crypto_error);
		
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
