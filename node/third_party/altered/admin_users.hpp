#ifndef CPPCMS_GENERATED_HEADER_SRC_GENERATED_NODE_ADMIN_ADMIN_USERS_HPP_TMPL_HEADER_INCLUDED
#define CPPCMS_GENERATED_HEADER_SRC_GENERATED_NODE_ADMIN_ADMIN_USERS_HPP_TMPL_HEADER_INCLUDED

#line 1 "src/node/admin/admin_users.tmpl"
#include "../guest/master.hpp" 
#line 2 "src/node/admin/admin_users.tmpl"
#include "../../../node/admin/admin_users_content.hpp" 
#line 3 "src/node/admin/admin_users.tmpl"
namespace ptp2n_node_admin_skin {
	#line 4 "src/node/admin/admin_users.tmpl"
	struct admin_users :public master
	#line 4 "src/node/admin/admin_users.tmpl"
	{
	#line 4 "src/node/admin/admin_users.tmpl"
		content::admin_users &content;
	#line 4 "src/node/admin/admin_users.tmpl"
		admin_users(std::ostream &_s,content::admin_users &_content): master(_s,_content),content(_content)
	#line 4 "src/node/admin/admin_users.tmpl"
		{
	#line 4 "src/node/admin/admin_users.tmpl"
		}
		#line 6 "src/node/admin/admin_users.tmpl"
		virtual void page_content();
		#line 15 "src/node/admin/admin_users.tmpl"
		virtual void new_user();
		#line 39 "src/node/admin/admin_users.tmpl"
		virtual void edit_user();
		#line 64 "src/node/admin/admin_users.tmpl"
		virtual void users_list();
	#line 111 "src/node/admin/admin_users.tmpl"
	}; // end of class admin_users
#line 112 "src/node/admin/admin_users.tmpl"
} // end of namespace ptp2n_node_admin_skin
#endif // CPPCMS_GENERATED_HEADER_SRC_GENERATED_NODE_ADMIN_ADMIN_USERS_HPP_TMPL_HEADER_INCLUDED
