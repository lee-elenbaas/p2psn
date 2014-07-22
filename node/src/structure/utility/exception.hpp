#ifndef __P2PSN_EXCEPTION_H
#define __P2PSN_EXCEPTION_H

#include <exception>

#define DEFINE_EXCEPTION(class_name, base_class) 									\
			class class_name : public base_class {							\
				public:														\
					class_name(const string& what) : base_class(what) { }	\
					class_name(const char* what) : base_class(what) { }		\
			}
			
namespace p2psn {
	namespace repository {
		
		using std::exception;
		
		DEFINE_EXCEPTION(cppcms_error, exception);
		
	} // namespace repository
} // namespace p2psn

#endif // __P2PSN_EXCEPTION_H
