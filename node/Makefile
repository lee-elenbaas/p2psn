LIBS=-lcppcms -lbooster
OPTIONS=-O2 -Wall -std=gnu++0x -g

#Wrapper C++ application
MAIN_HEADERS=main/signal_handler.h
MAIN_CPP=main/noded.cpp main/signal_handler.cpp

#Main node CppCMS application
NODE_APP_SKIN=node_app/main_master.tmpl node_app/info.tmpl node_app/about.tmpl node_app/login.tmpl
NODE_APP_GENERATED=build/ptp2n_node_app_skin.cpp
NODE_APP_CONTENT=node_app/main_content.h
NODE_APP_HEADERS=node_app/main_app.h 
NODE_APP_CPP=node_app/main_app.cpp node_app/main_content.cpp

#JSON-RPC Node API CppCMS application
NODE_API_HEADERS=node_api/node_api.h
NODE_API_CPP=node_api/node_api.cpp

#Shared utils
UTILS_HEADERS=utils/crypto.h
UTILS_CPP=utils/crypto.cpp

all: separator run/noded run/config.js run

.PHONY: all, separator, clean, documentation, run

separator:
	@echo
	@echo
	@echo Running make all on p2psn
	@echo
	@echo

documentation: docs/html/index.html

docs/html/index.html: $(MAIN_CPP) $(MAIN_HEADERS) $(NODE_APP_HEADERS) $(NODE_APP_CONTENT) $(NODE_APP_CPP) $(NODE_API_HEADERS) $(NODE_API_CPP) $(UTILS_HEADERS) $(UTILS_CPP) $(NODE_APP_SKIN)
	doxygen Doxyfile

run/noded: $(MAIN_CPP) $(MAIN_HEADERS) $(NODE_APP_HEADERS) $(NODE_APP_CONTENT) $(NODE_APP_CPP) $(NODE_API_HEADERS) $(NODE_API_CPP) $(UTILS_HEADERS) $(UTILS_CPP) $(NODE_APP_GENERATED)
	$(CXX) $(OPTIONS) $(MAIN_CPP) $(NODE_APP_CPP) $(NODE_API_CPP) $(NODE_API_CPP) $(UTILS_CPP) $(NODE_APP_GENERATED) -o run/noded ${LIBS}

run/config.js: config/config.js
	cp config/config.js run/config.js
	
$(NODE_APP_GENERATED): $(NODE_APP_SKIN)
	cppcms_tmpl_cc $(NODE_APP_SKIN) -o $(NODE_APP_GENERATED)
	
clean:
	rm -fr run/* cppcms_rundir build/* docs/* *~ main/*~ node_app/*~ node_api/*~ consif/*~

run:
	./noded

