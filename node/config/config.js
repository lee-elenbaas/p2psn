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
	"localization" {  
		"locales" : [ "en_US.UTF-8" ]  
	}  
}

