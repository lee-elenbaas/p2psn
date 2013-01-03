#include "admin_users.hpp"

#line 3 "src/node/admin/admin_users.tmpl"
namespace ptp2n_node_admin_skin {
	#line 6 "src/node/admin/admin_users.tmpl"
	void admin_users::page_content() {
		#line 7 "src/node/admin/admin_users.tmpl"
		out()<<"\n"
				"";
		#line 7 "src/node/admin/admin_users.tmpl"
		if(content.list_state == content::admin_users_list_state::view) {
			#line 8 "src/node/admin/admin_users.tmpl"
			out()<<"\n"
					"\t";
			#line 8 "src/node/admin/admin_users.tmpl"
			new_user();
			#line 9 "src/node/admin/admin_users.tmpl"
			out()<<"\n"
					"";
		#line 9 "src/node/admin/admin_users.tmpl"
		}else{
			#line 10 "src/node/admin/admin_users.tmpl"
			out()<<"\n"
					"\t";
			#line 10 "src/node/admin/admin_users.tmpl"
			edit_user();
			#line 11 "src/node/admin/admin_users.tmpl"
			out()<<"\n"
					"";
		#line 11 "src/node/admin/admin_users.tmpl"
		}
		#line 12 "src/node/admin/admin_users.tmpl"
		out()<<"\n"
				"";
		#line 12 "src/node/admin/admin_users.tmpl"
		users_list();
		#line 13 "src/node/admin/admin_users.tmpl"
		out()<<"\n"
				"";
	#line 13 "src/node/admin/admin_users.tmpl"
	} // end of template page_content
	#line 15 "src/node/admin/admin_users.tmpl"
	void admin_users::new_user() {
		#line 17 "src/node/admin/admin_users.tmpl"
		out()<<"\n"
				"<h2>New User</h2>\n"
				"<form method=\"post\" action=\"";
		#line 17 "src/node/admin/admin_users.tmpl"
		content.app().mapper().map(out(),"/admin/users/new");
		#line 18 "src/node/admin/admin_users.tmpl"
		out()<<"\">\n"
				"";
		#line 18 "src/node/admin/admin_users.tmpl"
		out() << "<input type=\"hidden\" name=\"_csrf\" value=\"" << content.app().session().get_csrf_token() <<"\" >\n";
		#line 21 "src/node/admin/admin_users.tmpl"
		out()<<"\n"
				"<ul>\n"
				"<li>\n"
				"<b><label for=\"user_name_box\">User Name</label></b> ";
		#line 21 "src/node/admin/admin_users.tmpl"
		{ cppcms::form_context _form_context(out(),cppcms::form_flags::as_html);
		#line 21 "src/node/admin/admin_users.tmpl"
		    _form_context.widget_part(cppcms::form_context::first_part);
		#line 21 "src/node/admin/admin_users.tmpl"
		    (content.new_user.user_name).render_input(_form_context);
		#line 21 "src/node/admin/admin_users.tmpl"
		}
			#line 21 "src/node/admin/admin_users.tmpl"
			out()<<" id=\"user_name_box\" ";
		#line 21 "src/node/admin/admin_users.tmpl"
		{ cppcms::form_context _form_context(out(),cppcms::form_flags::as_html);
		#line 21 "src/node/admin/admin_users.tmpl"
		    _form_context.widget_part(cppcms::form_context::second_part);
		#line 21 "src/node/admin/admin_users.tmpl"
		    (content.new_user.user_name).render_input(_form_context);
		#line 21 "src/node/admin/admin_users.tmpl"
		}
		#line 24 "src/node/admin/admin_users.tmpl"
		out()<<"\n"
				"</li>\n"
				"<li>\n"
				"<b><label for=\"password_box\">Password</label></b> ";
		#line 24 "src/node/admin/admin_users.tmpl"
		{ cppcms::form_context _form_context(out(),cppcms::form_flags::as_html);
		#line 24 "src/node/admin/admin_users.tmpl"
		    _form_context.widget_part(cppcms::form_context::first_part);
		#line 24 "src/node/admin/admin_users.tmpl"
		    (content.new_user.user_password).render_input(_form_context);
		#line 24 "src/node/admin/admin_users.tmpl"
		}
			#line 24 "src/node/admin/admin_users.tmpl"
			out()<<" id=\"password_box\" ";
		#line 24 "src/node/admin/admin_users.tmpl"
		{ cppcms::form_context _form_context(out(),cppcms::form_flags::as_html);
		#line 24 "src/node/admin/admin_users.tmpl"
		    _form_context.widget_part(cppcms::form_context::second_part);
		#line 24 "src/node/admin/admin_users.tmpl"
		    (content.new_user.user_password).render_input(_form_context);
		#line 24 "src/node/admin/admin_users.tmpl"
		}
		#line 27 "src/node/admin/admin_users.tmpl"
		out()<<"\n"
				"</li>\n"
				"<li>\n"
				"";
		#line 27 "src/node/admin/admin_users.tmpl"
		{ cppcms::form_context _form_context(out(),cppcms::form_flags::as_html);
		#line 27 "src/node/admin/admin_users.tmpl"
		    _form_context.widget_part(cppcms::form_context::first_part);
		#line 27 "src/node/admin/admin_users.tmpl"
		    (content.new_user.is_admin).render_input(_form_context);
		#line 27 "src/node/admin/admin_users.tmpl"
		    out() << (content.new_user.is_admin).attributes_string();
		#line 27 "src/node/admin/admin_users.tmpl"
		    _form_context.widget_part(cppcms::form_context::second_part);
		#line 27 "src/node/admin/admin_users.tmpl"
		    (content.new_user.is_admin).render_input(_form_context);
		#line 27 "src/node/admin/admin_users.tmpl"
		}
		#line 30 "src/node/admin/admin_users.tmpl"
		out()<<"\n"
				"</li>\n"
				"<li>\n"
				"";
		#line 30 "src/node/admin/admin_users.tmpl"
		{ cppcms::form_context _form_context(out(),cppcms::form_flags::as_html);
		#line 30 "src/node/admin/admin_users.tmpl"
		    _form_context.widget_part(cppcms::form_context::first_part);
		#line 30 "src/node/admin/admin_users.tmpl"
		    (content.new_user.is_manager).render_input(_form_context);
		#line 30 "src/node/admin/admin_users.tmpl"
		    out() << (content.new_user.is_manager).attributes_string();
		#line 30 "src/node/admin/admin_users.tmpl"
		    _form_context.widget_part(cppcms::form_context::second_part);
		#line 30 "src/node/admin/admin_users.tmpl"
		    (content.new_user.is_manager).render_input(_form_context);
		#line 30 "src/node/admin/admin_users.tmpl"
		}
		#line 33 "src/node/admin/admin_users.tmpl"
		out()<<"\n"
				"</li>\n"
				"<li>\n"
				"";
		#line 33 "src/node/admin/admin_users.tmpl"
		{ cppcms::form_context _form_context(out(),cppcms::form_flags::as_html);
		#line 33 "src/node/admin/admin_users.tmpl"
		    _form_context.widget_part(cppcms::form_context::first_part);
		#line 33 "src/node/admin/admin_users.tmpl"
		    (content.new_user.submit).render_input(_form_context);
		#line 33 "src/node/admin/admin_users.tmpl"
		    out() << (content.new_user.submit).attributes_string();
		#line 33 "src/node/admin/admin_users.tmpl"
		    _form_context.widget_part(cppcms::form_context::second_part);
		#line 33 "src/node/admin/admin_users.tmpl"
		    (content.new_user.submit).render_input(_form_context);
		#line 33 "src/node/admin/admin_users.tmpl"
		}
		#line 37 "src/node/admin/admin_users.tmpl"
		out()<<"\n"
				"</li>\n"
				"</ul>\n"
				"</form>\n"
				"";
	#line 37 "src/node/admin/admin_users.tmpl"
	} // end of template new_user
	#line 39 "src/node/admin/admin_users.tmpl"
	void admin_users::edit_user() {
		#line 41 "src/node/admin/admin_users.tmpl"
		out()<<"\n"
				"<h2>Edit User</h2>\n"
				"<form method=\"post\" action=\"";
		#line 41 "src/node/admin/admin_users.tmpl"
		content.app().mapper().map(out(),"/admin/users/update");
		#line 42 "src/node/admin/admin_users.tmpl"
		out()<<"\">\n"
				"";
		#line 42 "src/node/admin/admin_users.tmpl"
		out() << "<input type=\"hidden\" name=\"_csrf\" value=\"" << content.app().session().get_csrf_token() <<"\" >\n";
		#line 43 "src/node/admin/admin_users.tmpl"
		out()<<"\n"
				"";
		#line 43 "src/node/admin/admin_users.tmpl"
		{ cppcms::form_context _form_context(out(),cppcms::form_flags::as_html);
		#line 43 "src/node/admin/admin_users.tmpl"
		    _form_context.widget_part(cppcms::form_context::first_part);
		#line 43 "src/node/admin/admin_users.tmpl"
		    (content.edited_user.user_name).render_input(_form_context);
		#line 43 "src/node/admin/admin_users.tmpl"
		    out() << (content.edited_user.user_name).attributes_string();
		#line 43 "src/node/admin/admin_users.tmpl"
		    _form_context.widget_part(cppcms::form_context::second_part);
		#line 43 "src/node/admin/admin_users.tmpl"
		    (content.edited_user.user_name).render_input(_form_context);
		#line 43 "src/node/admin/admin_users.tmpl"
		}
		#line 46 "src/node/admin/admin_users.tmpl"
		out()<<"\n"
				"<ul>\n"
				"<li>\n"
				"<b>User name</b> <span>";
		#line 46 "src/node/admin/admin_users.tmpl"
		out()<<cppcms::filters::escape(content.edited_user.user_name.value());
		#line 49 "src/node/admin/admin_users.tmpl"
		out()<<"</span>\n"
				"</li>\n"
				"<li>\n"
				"<b><label for=\"password_box\">Password</label></b> ";
		#line 49 "src/node/admin/admin_users.tmpl"
		{ cppcms::form_context _form_context(out(),cppcms::form_flags::as_html);
		#line 49 "src/node/admin/admin_users.tmpl"
		    _form_context.widget_part(cppcms::form_context::first_part);
		#line 49 "src/node/admin/admin_users.tmpl"
		    (content.edited_user.user_password).render_input(_form_context);
		#line 49 "src/node/admin/admin_users.tmpl"
		}
			#line 49 "src/node/admin/admin_users.tmpl"
			out()<<" id=\"password_box\" ";
		#line 49 "src/node/admin/admin_users.tmpl"
		{ cppcms::form_context _form_context(out(),cppcms::form_flags::as_html);
		#line 49 "src/node/admin/admin_users.tmpl"
		    _form_context.widget_part(cppcms::form_context::second_part);
		#line 49 "src/node/admin/admin_users.tmpl"
		    (content.edited_user.user_password).render_input(_form_context);
		#line 49 "src/node/admin/admin_users.tmpl"
		}
		#line 52 "src/node/admin/admin_users.tmpl"
		out()<<"\n"
				"</li>\n"
				"<li>\n"
				"";
		#line 52 "src/node/admin/admin_users.tmpl"
		{ cppcms::form_context _form_context(out(),cppcms::form_flags::as_html);
		#line 52 "src/node/admin/admin_users.tmpl"
		    _form_context.widget_part(cppcms::form_context::first_part);
		#line 52 "src/node/admin/admin_users.tmpl"
		    (content.new_user.is_admin).render_input(_form_context);
		#line 52 "src/node/admin/admin_users.tmpl"
		    out() << (content.new_user.is_admin).attributes_string();
		#line 52 "src/node/admin/admin_users.tmpl"
		    _form_context.widget_part(cppcms::form_context::second_part);
		#line 52 "src/node/admin/admin_users.tmpl"
		    (content.new_user.is_admin).render_input(_form_context);
		#line 52 "src/node/admin/admin_users.tmpl"
		}
		#line 55 "src/node/admin/admin_users.tmpl"
		out()<<"\n"
				"</li>\n"
				"<li>\n"
				"";
		#line 55 "src/node/admin/admin_users.tmpl"
		{ cppcms::form_context _form_context(out(),cppcms::form_flags::as_html);
		#line 55 "src/node/admin/admin_users.tmpl"
		    _form_context.widget_part(cppcms::form_context::first_part);
		#line 55 "src/node/admin/admin_users.tmpl"
		    (content.new_user.is_manager).render_input(_form_context);
		#line 55 "src/node/admin/admin_users.tmpl"
		    out() << (content.new_user.is_manager).attributes_string();
		#line 55 "src/node/admin/admin_users.tmpl"
		    _form_context.widget_part(cppcms::form_context::second_part);
		#line 55 "src/node/admin/admin_users.tmpl"
		    (content.new_user.is_manager).render_input(_form_context);
		#line 55 "src/node/admin/admin_users.tmpl"
		}
		#line 58 "src/node/admin/admin_users.tmpl"
		out()<<"\n"
				"</li>\n"
				"<li>\n"
				"";
		#line 58 "src/node/admin/admin_users.tmpl"
		{ cppcms::form_context _form_context(out(),cppcms::form_flags::as_html);
		#line 58 "src/node/admin/admin_users.tmpl"
		    _form_context.widget_part(cppcms::form_context::first_part);
		#line 58 "src/node/admin/admin_users.tmpl"
		    (content.edited_user.submit).render_input(_form_context);
		#line 58 "src/node/admin/admin_users.tmpl"
		    out() << (content.edited_user.submit).attributes_string();
		#line 58 "src/node/admin/admin_users.tmpl"
		    _form_context.widget_part(cppcms::form_context::second_part);
		#line 58 "src/node/admin/admin_users.tmpl"
		    (content.edited_user.submit).render_input(_form_context);
		#line 58 "src/node/admin/admin_users.tmpl"
		}
		#line 62 "src/node/admin/admin_users.tmpl"
		out()<<"\n"
				"</li>\n"
				"</ul>\n"
				"</form>\n"
				"";
	#line 62 "src/node/admin/admin_users.tmpl"
	} // end of template edit_user
	#line 64 "src/node/admin/admin_users.tmpl"
	void admin_users::users_list() {
		#line 74 "src/node/admin/admin_users.tmpl"
		out()<<"\n"
				"<h2>Existing Users</h2>\n"
				"<table class=\"users\">\n"
				"\t<thead>\n"
				"\t<tr>\n"
				"\t\t<th>Name</th>\n"
				"\t\t<th>Password</th>\n"
				"\t\t<th>&nbsp;</th>\n"
				"\t</tr>\n"
				"\t</thead>\n"
				"";
		#line 74 "src/node/admin/admin_users.tmpl"
		if((content.users).begin()!=(content.users).end()) {
			#line 76 "src/node/admin/admin_users.tmpl"
			out()<<"\n"
					"\t<tbody>\n"
					"\t\t";
			#line 76 "src/node/admin/admin_users.tmpl"
			for(CPPCMS_TYPEOF((content.users).begin()) user_ptr=(content.users).begin(),user_ptr_end=(content.users).end();user_ptr!=user_ptr_end;++user_ptr) {
			#line 76 "src/node/admin/admin_users.tmpl"
			CPPCMS_TYPEOF(*user_ptr) &user=*user_ptr;
				#line 77 "src/node/admin/admin_users.tmpl"
				out()<<"\n"
						"\t\t\t";
				#line 77 "src/node/admin/admin_users.tmpl"
				auto user_state = content.user_states[user.name]; 
				#line 79 "src/node/admin/admin_users.tmpl"
				out()<<"\n"
						"\t\t\t<tr>\n"
						"\t\t\t\t<td class=\"";
				#line 79 "src/node/admin/admin_users.tmpl"
				out()<<cppcms::filters::escape(content.user_state.css_class);
				#line 79 "src/node/admin/admin_users.tmpl"
				out()<<"\">";
				#line 79 "src/node/admin/admin_users.tmpl"
				out()<<cppcms::filters::escape(user.name);
				#line 80 "src/node/admin/admin_users.tmpl"
				out()<<"</td>\n"
						"\t\t\t\t<td class=\"";
				#line 80 "src/node/admin/admin_users.tmpl"
				out()<<cppcms::filters::escape(content.user_state.css_class);
				#line 80 "src/node/admin/admin_users.tmpl"
				out()<<"\">";
				#line 80 "src/node/admin/admin_users.tmpl"
				out()<<cppcms::filters::escape(user.password);
				#line 82 "src/node/admin/admin_users.tmpl"
				out()<<"</td>\n"
						"\t\t\t\t<td class=\"actions\">\n"
						"\t\t\t\t\t";
				#line 82 "src/node/admin/admin_users.tmpl"
				if(user_state.allow_edit) {
					#line 83 "src/node/admin/admin_users.tmpl"
					out()<<"\n"
							"\t\t\t\t\t\t<form method=\"post\" action=\"";
					#line 83 "src/node/admin/admin_users.tmpl"
					content.app().mapper().map(out(),"/admin/users/edit");
					#line 84 "src/node/admin/admin_users.tmpl"
					out()<<"\">\n"
							"\t\t\t\t\t\t\t";
					#line 84 "src/node/admin/admin_users.tmpl"
					out() << "<input type=\"hidden\" name=\"_csrf\" value=\"" << content.app().session().get_csrf_token() <<"\" >\n";
					#line 85 "src/node/admin/admin_users.tmpl"
					out()<<"\n"
							"\t\t\t\t\t\t\t<input type=\"hidden\" name=\"user_name\" value=\"";
					#line 85 "src/node/admin/admin_users.tmpl"
					out()<<cppcms::filters::escape(user.name);
					#line 88 "src/node/admin/admin_users.tmpl"
					out()<<"\" />\t\n"
							"\t\t\t\t\t\t\t<input type=\"submit\" value=\"Edit\" />\n"
							"\t\t\t\t\t\t</form>\n"
							"\t\t\t\t\t";
				#line 88 "src/node/admin/admin_users.tmpl"
				} // endif
				#line 89 "src/node/admin/admin_users.tmpl"
				out()<<"\n"
						"\t\t\t\t\t";
				#line 89 "src/node/admin/admin_users.tmpl"
				if(user_state.allow_delete) {
					#line 90 "src/node/admin/admin_users.tmpl"
					out()<<"\n"
							"\t\t\t\t\t\t<form method=\"post\" action=\"";
					#line 90 "src/node/admin/admin_users.tmpl"
					content.app().mapper().map(out(),"/admin/users/delete");
					#line 91 "src/node/admin/admin_users.tmpl"
					out()<<"\">\n"
							"\t\t\t\t\t\t\t";
					#line 91 "src/node/admin/admin_users.tmpl"
					out() << "<input type=\"hidden\" name=\"_csrf\" value=\"" << content.app().session().get_csrf_token() <<"\" >\n";
					#line 92 "src/node/admin/admin_users.tmpl"
					out()<<"\n"
							"\t\t\t\t\t\t\t<input type=\"hidden\" name=\"user_name\" value=\"";
					#line 92 "src/node/admin/admin_users.tmpl"
					out()<<cppcms::filters::escape(user.name);
					#line 95 "src/node/admin/admin_users.tmpl"
					out()<<"\" />\t\n"
							"\t\t\t\t\t\t\t<input type=\"submit\" value=\"Delete\" />\n"
							"\t\t\t\t\t\t</form>\n"
							"\t\t\t\t\t";
				#line 95 "src/node/admin/admin_users.tmpl"
				} // endif
				#line 96 "src/node/admin/admin_users.tmpl"
				out()<<"\n"
						"\t\t\t\t\t";
				#line 96 "src/node/admin/admin_users.tmpl"
				if(user_state.allow_restore) {
					#line 97 "src/node/admin/admin_users.tmpl"
					out()<<"\n"
							"\t\t\t\t\t\t<form method=\"post\" action=\"";
					#line 97 "src/node/admin/admin_users.tmpl"
					content.app().mapper().map(out(),"/admin/users/restore");
					#line 98 "src/node/admin/admin_users.tmpl"
					out()<<"\">\n"
							"\t\t\t\t\t\t\t";
					#line 98 "src/node/admin/admin_users.tmpl"
					out() << "<input type=\"hidden\" name=\"_csrf\" value=\"" << content.app().session().get_csrf_token() <<"\" >\n";
					#line 99 "src/node/admin/admin_users.tmpl"
					out()<<"\n"
							"\t\t\t\t\t\t\t<input type=\"hidden\" name=\"user_name\" value=\"";
					#line 99 "src/node/admin/admin_users.tmpl"
					out()<<cppcms::filters::escape(user.name);
					#line 102 "src/node/admin/admin_users.tmpl"
					out()<<"\" />\t\n"
							"\t\t\t\t\t\t\t<input type=\"submit\" value=\"Restore\" />\n"
							"\t\t\t\t\t\t</form>\n"
							"\t\t\t\t\t";
				#line 102 "src/node/admin/admin_users.tmpl"
				} // endif
				#line 105 "src/node/admin/admin_users.tmpl"
				out()<<"\n"
						"\t\t\t\t</td>\n"
						"\t\t\t</tr>\n"
						"\t\t";
			#line 105 "src/node/admin/admin_users.tmpl"
			} // end of item
			#line 107 "src/node/admin/admin_users.tmpl"
			out()<<"\n"
					"\t</tbody>\n"
					"\t";
		#line 107 "src/node/admin/admin_users.tmpl"
		}
		#line 109 "src/node/admin/admin_users.tmpl"
		out()<<"\n"
				"</table>\n"
				"";
	#line 109 "src/node/admin/admin_users.tmpl"
	} // end of template users_list
#line 112 "src/node/admin/admin_users.tmpl"
} // end of namespace ptp2n_node_admin_skin
#line 114 "src/node/admin/admin_users.tmpl"
namespace {
#line 114 "src/node/admin/admin_users.tmpl"
 cppcms::views::generator my_generator; 
#line 114 "src/node/admin/admin_users.tmpl"
 struct loader { 
#line 114 "src/node/admin/admin_users.tmpl"
  loader() { 
#line 114 "src/node/admin/admin_users.tmpl"
   my_generator.name("ptp2n_node_admin_skin");
#line 114 "src/node/admin/admin_users.tmpl"
   my_generator.add_view<ptp2n_node_admin_skin::admin_users,content::admin_users>("admin_users",true);
#line 114 "src/node/admin/admin_users.tmpl"
    cppcms::views::pool::instance().add(my_generator);
#line 114 "src/node/admin/admin_users.tmpl"
 }
#line 114 "src/node/admin/admin_users.tmpl"
 ~loader() {  cppcms::views::pool::instance().remove(my_generator); }
#line 114 "src/node/admin/admin_users.tmpl"
} a_loader;
#line 114 "src/node/admin/admin_users.tmpl"
} // anon 
