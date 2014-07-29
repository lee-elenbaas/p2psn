#ifndef __P2PSN_REPOSITORY_H
#define __P2PSN_REPOSITORY_H

#include "../entities/object.hpp"
#include "../utility/exception.hpp"
#include <map>

namespace p2psn {
	namespace repository {
		typedef utility::DEFINE_EXCEPTION<cppcms_error>::type storage_error;

		typedef utility::DEFINE_EXCEPTION<storage_error>::type storage_retrieval_error;
		typedef utility::DEFINE_EXCEPTION<storage_retrieval_error>::type not_found_error;

		typedef utility::DEFINE_EXCEPTION<storage_error>::type storage_store_error;
		typedef utility::DEFINE_EXCEPTION<storage_store_error>::type id_conflict_error;
		typedef utility::DEFINE_EXCEPTION<storage_store_error>::type version_conflict_error;
		typedef utility::DEFINE_EXCEPTION<storage_store_error>::type store_older_version_error;
		
		class object_repository {
			private:
				std::map<identifier, object> _objects;
				
				object _retrieve(const object_id& id) const throw (not_found_error);
			public:
				object_repository();
				~object_repository();
				
				void store(object obj) throw (storage_error);
				
				template<class Type>
				Type retrieve(object_reference<Type> ref) const throw (id_conflict_error, version_conflict_error, store_older_version_error) {
					return dynamic_cast<Type>(_retrieve(ref.id()));
				}
		};
		
	} // namespace repository
} // namespace p2psn

#endif // __P2PSN_REPOSITORY_H
