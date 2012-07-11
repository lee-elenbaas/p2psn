LIBS=-lcppcms -lbooster

#Wrapper C++ application
MAIN_HEADERS=main/signal_handler.h
MAIN_CPP=main/noded.cpp main/signal_handler.cpp

#Main node CppCMS application
NODE_APP_SKIN=node_app/master.tmpl node_app/page.tmpl node_app/info.tmpl node_app/about.tmpl node_app/login.tmpl
NODE_APP_GENERATED=build/main_skin.cpp
NODE_APP_CONTENT=node_app/content.h
NODE_APP_HEADERS=node_app/main_app.h 
NODE_APP_CPP=node_app/main_app.cpp node_app/content.cpp

#JSON-RPC Node API CppCMS application
NODE_API_HEADERS=node_api/node_api.h
NODE_API_CPP=node_api/node_api.cpp

all: separator run/noded run/config.js

.PHONY: all, separator, clean

separator:
	echo
	echo
	echo
	echo Running make all on p2psn
	echo

run/noded: $(MAIN_CPP) $(MAIN_HEADERS) $(NODE_APP_HEADERS) $(NODE_APP_CONTENT) $(NODE_APP_CPP) $(NODE_API_HEADERS) $(NODE_API_CPP) $(NODE_APP_GENERATED)
	$(CXX) -O2 -Wall -std=c++0x -g $(MAIN_CPP) $(NODE_APP_CPP) $(NODE_API_CPP) $(NODE_APP_GENERATED) -o run/noded ${LIBS}

run/config.js: config/config.js
	cp config/config.js run/config.js
	
$(NODE_APP_GENERATED): $(NODE_APP_SKIN)
	cppcms_tmpl_cc $(NODE_APP_SKIN) -o $(NODE_APP_GENERATED)

clean:
	rm -fr run/* cppcms_rundir build/* *~ main/*~ node_app/*~ node_api/*~ consif/*~

