#include "../node_guest/guest_app.h"

#include <cppcms/url_dispatcher.h>
#include "../node_api/node_api.h"
#include "../node_admin/admin_app.h"
#include "../utils/crypto.h"

using namespace p2psn::node_admin;

guest_app::guest_app(cppcms::service &srv) 
    : base_app(srv) 
{
    attach(new p2psn::api::node_api(srv), "api", "/api{1}", "/api(/(.*))?", 1);
    attach(new admin_app(srv), "admin", "/admin{1}", "/admin(/(.*))?", 1);

    dispatcher().assign("",&guest_app::home,this);
    mapper().assign("");

    dispatcher().assign("/info/",&guest_app::info,this);
    mapper().assign("info","/info");

    dispatcher().assign("/about",&guest_app::about,this);
    mapper().assign("about","/about");

    dispatcher().assign("/logout",&guest_app::logout,this);
    mapper().assign("logout","/logout");

    dispatcher().assign("/login",&guest_app::login,this);
    mapper().assign("login","/login");
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
    c.port = settings()["service"]["port"].number();
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

    c.user_messages.push_back({ session()["url_after_login"], "" });

    if (request().request_method() == "POST" && session().is_set("prelogin")) {
        c.login_info.load(context());

        if (c.login_info.validate() && validate_user(c.login_info)) { 
            auto after_login_url = (session().is_set("url_after_login"))?url(session()["url_after_login"]):url("/admin");

			session().reset_session();
            session().erase("prelogin");
            session()["user"] = c.login_info.user_name.value(); // TODO: replace name with id in session

            session().erase("url_after_login");
            response_redirect(after_login_url);

            return;
		}
    }

	session()["prelogin"] = "prelogin";

	init(c);
	c.title = "Login";

	render("login",c);
}

bool guest_app::validate_user(content::login_form& l)
{
    /// Validate login for matching user/pass combination in the settings
    for (auto user : settings()["config_noded"]["admin"].array()) {
        if (user["user"].str() != l.user_name.value())
            continue;

        // validate user password
        if (!user["password"].is_undefined() && (user["password"].str() == l.user_password.value()))
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
