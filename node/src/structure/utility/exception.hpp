#ifndef __P2PSN_EXCEPTION_H
#define __P2PSN_EXCEPTION_H

#define DEFINE_EXCEPTION(class_name, base_class) 									\
			class class_name : public base_class {							\
				public:														\
					class_name(const string& what) : base_class(what) { }	\
					class_name(const char* what) : base_class(what) { }		\
			}
			
#endif // __P2PSN_EXCEPTION_H
