{
	"service" : {
		"api" : "http",
		"port" : 8080
	},
	"http" : {
		"script" : "/node",
		"rewrite" : [
			{ "regex" : "/node(/.*)?", "pattern" : "$0" },
			{ "regex" : "/media(/.*)?", "pattern" : "$0" },
			{ "regex" : "/favicon\\.ico", "pattern" : "$0" },
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
//			"cbc" : "aes256",
//			"cbc_key" : "4bf2cc8ba8",
//			"encryptor" : "aes256",
		    "hmac" :        "sha1",  
		    "hmac_key" :    "3891bbf7f845fd4277008a63d72640fc13bb9a31"  ,
//			"key" : "3894bf2cc8ba81bbf7f845fd42774bf2cc8ba8008a63d72644bf2cc8ba80fc4bf2cc8ba813bb9a31"
		}      
	    },  
	"config_noded" : {
		"admin" : [
			{ "user" : "admin", "password" : "admin" },
			{ "user" : "lior", "password" : "lior" },
		]
	}
}

