#include "../node_shared/base_app.h"

#include "../utils/log.h"
#include "../utils/locale_matching.h"

using namespace p2psn::node_admin;
using std::string;

base_app::base_app(cppcms::service &srv) 
    : cppcms::application(srv) 
{
}

void base_app::main(string url) {
	// filter connections based on allowed IPs
	
	// set locale based on user prefrences
	context().locale(p2psn::utils::best_match_locale(request().http_accept_language(), request().http_accept_encoding(), settings()["localization"]["locales"]));

    // override locale using session value if exists
    if (session().is_set("locale"))
        context().locale(session().get("locale"));

    LOG(booster::log::level_type::alert, "before: "+url);
	cppcms::application::main(url);
    LOG(booster::log::level_type::alert, "before: "+url);
}

void base_app::init(content::master& c) {
    if (session().is_set("user"))
	    c.user_name = session()["user"];
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

