#include "guest_app.hpp"

#include <cppcms/url_dispatcher.h>

#include "../node_api/node_api.hpp"
#include "../admin_menu/admin_menu_app.hpp"
#include "../../utils/whitelist_static_app.hpp"
#include "../../utils/locale_matching.hpp"
#include "../../utils/crypto.hpp"

using namespace p2psn::node_admin;
using namespace std;
using namespace cppcms::json;
using namespace p2psn::utils;

guest_app::guest_app(cppcms::service &srv) 
    : base_app(srv) 
{
    attach(new whitelist_static_app(srv, settings().get<string>("config_noded.client.path"), settings().at("config_noded.client.whitelist"), hash_algorithm::md5), "client", "/client{1}", "/client(/(.*))?", 1);

    attach(new p2psn::api::node_api(srv), "api", "/api{1}", "/api(/(.*))?", 1);
    attach(new admin_menu_app(srv), "admin", "/admin{1}", "/admin(/(.*))?", 1);
    attach(new whitelist_static_app(srv, settings().get<string>("config_noded.static_files.path"), settings().at("config_noded.static_files.whitelist"), hash_algorithm::md5), "static", "/static{1}", "/static(/(.*))?", 1);

    dispatcher().assign("",&guest_app::home,this);
    mapper().assign("");

    dispatcher().assign("/info",&guest_app::info,this);
    mapper().assign("info","/info");

    dispatcher().assign("/about",&guest_app::about,this);
    mapper().assign("about","/about");

    dispatcher().assign("/logout",&guest_app::logout,this);
    mapper().assign("logout","/logout");

    dispatcher().assign("/login",&guest_app::login,this);
    mapper().assign("login","/login");

    mapper().root("/node");
}

void guest_app::main(string url) {
	// TODO: filter connections based on allowed IPs
	DEBUG("Request from IP: "+request().remote_addr());
	
	// set locale based on user prefrences
	context().locale(
        p2psn::utils::best_match_locale(
            request().http_accept_language(), 
            request().http_accept_encoding(), 
            settings().at("localization.locales")
        ));

    // override locale using session value if exists
    if (session().is_set("locale"))
        context().locale(session().get("locale"));

	cppcms::application::main(url);
}

void guest_app::home()
{
	response_redirect(url("/info"));
}

void guest_app::info()
{
    content::info c;

    init(c);
    c.title = "Info";
    c.port = settings().get<double>("service.port");
    c.host = "localhost"; // TODO: make host discovery from OS or CppCMS lib

    render("info",c);
}

void guest_app::about()
{
    content::master c;

    init(c);
    c.title = "About";

    render("about",c);
}

void guest_app::logout()
{
    session().clear();
	response_redirect(url("/info"));
}

void guest_app::login()
{
    content::login_page c;

    if (request().request_method() == "POST" && session().is_set("prelogin")) {
        c.login_info.load(context());

        if (c.login_info.validate() && validate_user(c.login_info)) { 
            string after_login_url = session().get("url_after_login", url("/admin"));

			session().reset_session();
            session().erase("prelogin");
            session().set("user", c.login_info.user_name.value()); // TODO: replace name with id in session

            session().erase("url_after_login");
            response_redirect(after_login_url);

            return;
		}
    }

	session().set("prelogin", "prelogin");

	init(c);
	c.title = "Login";

	render("login",c);
}

bool guest_app::validate_user(content::login_form& l)
{
    /// Validate login for matching user/pass combination in the settings
    for (auto user : settings().at("config_noded.admin").array()) {
        if (user.get<string>("user") != l.user_name.value())
            continue;

        // validate user password
        if (!user.at("password").is_undefined() && (user.get<string>("password") == l.user_password.value()))
            return true;

        // TODO: handle password signatures instead of open passwords
//        if (!user["password_hmac"].is_undefined()) {
//                        
//        }

        break;
    }

    l.user_name.valid(false);
    l.user_password.valid(false);
    return false;
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
