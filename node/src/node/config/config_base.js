{
	"service" : {
		"api" : "http",
		"port" : 8080
	},
	"http" : {
		"script" : "/node",
		"rewrite" : [
			{ "regex" : "/node(/.*)?", "pattern" : "$0" },
	//		{ "regex" : "/client(/.*)?", "pattern", : "/node$0" },
			{ "regex" : "/media(/.*)?", "pattern" : "$0" },
			{ "regex" : "/favicon\\.ico", "pattern" : "/node/static/images/favicon.ico" },
			{ "regex" : ".*", "pattern" : "/node" }
		]
	},
	"localization" : {  
		"locales" : [ "en_US.UTF-8" ]  
	},
	"security" : {  
	   "csrf" : {  
	      "enable" : true  
	   }  
	}, 
	"session" : {  
		"expire" : "browser",  
		"timeout" : 604800,  
		"location" : "client",  
		"client" :      {  
		    "hmac" :        "sha1",  
		    "hmac_key" :    "3891bbf7f845fd4277008a63d72640fc13bb9a31"  ,
		}      
	},  
	"config_noded" : {
		"client" : {
			"path" : "run/client",
			"whitelist" :
#include "../../../build/node/config/client_whitelist.js"
		},
		"static_files" : {
			"path" : "run/static_files",
			"whitelist" :
#include "../../../build/node/config/node_whitelist.js"
		},
		"tasks" : {
			"admin users" : false,
			"server settings" : {
				"port" : false,
				"ip filtering" : false,
				"admin ip filtering" : false
			},
			"apply new settings" : false
		},
		"admin" : [
			{ "user" : "admin", "password" : "admin", "is_admin" : true, "is_manager" : true },
			{ "user" : "lior", "password" : "lior", "is_admin" : true, "is_manager" : true },
		]
	}
}

