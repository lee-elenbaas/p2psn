#ifndef __P2PSN_EXCEPTION_H
#define __P2PSN_EXCEPTION_H

#include <exception>
			
namespace p2psn {
	namespace utility {
		
		template<class B>
			struct DEFINE_EXCEPTION {
				class type : public B {						
				public:														
					exception(const string& what) : B(what) { }	
					exception(const char* what) : B(what) { }	
				};	
			};
			
		typedef DEFINE_EXCEPTION<std::exception>::type cppcms_error;
	} // namespace utility
} // namespace p2psn

#endif // __P2PSN_EXCEPTION_H
