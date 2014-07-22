#ifndef __P2PSN_REPOSITORY_H
#define __P2PSN_REPOSITORY_H

#include "../entities/object.hpp"
#include "../utility/exception.hpp"
#include <map>

namespace p2psn {
	namespace repository {
		DEFINE_EXCEPTION(storage_error, cppcms_error);
		DEFINE_EXCEPTION(not_found_error, storage_error);
		DEFINE_EXCEPTION(id_conflict_error, storage_error);
		
		class object_repository {
			private:
				std::map<identifier, object> _objects;
				
				object _retrieve(const object_id& id) const throw (storage_error);
			public:
				object_repository();
				~object_repository();
				
				void store(object obj) throw (storage_error);
				
				template<class Type>
				Type retrieve(object_reference<Type> ref) const throw (storage_error) {
					return dynamic_cast<Type>(_retrieve(ref.id()));
				}
		};
		
	} // namespace repository
} // namespace p2psn

#endif // __P2PSN_REPOSITORY_H
