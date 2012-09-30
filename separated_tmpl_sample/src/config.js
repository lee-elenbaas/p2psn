{
	"service" : {
		"api" : "http",
		"port" : 8080
	},
	"http" : {
		"script" : "/sample",
		"rewrite" : [
			{ "regex" : "/sample(/.*)?", "pattern" : "$0" },
			{ "regex" : ".*", "pattern" : "/sample" }
		]
	}
}
