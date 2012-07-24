LIBS=-lcppcms -lbooster
OPTIONS=-O2 -Wall -std=gnu++0x -g

#Wrapper C++ application
MAIN_HEADERS=main/signal_handler.h
MAIN_CPP=main/noded.cpp main/signal_handler.cpp

#Main node CppCMS application
NODE_ADMIN_SKIN=node_admin/master.tmpl node_admin/info.tmpl node_admin/about.tmpl node_admin/login.tmpl node_admin/admin.tmpl
NODE_ADMIN_GENERATED=build/ptp2n_NODE_ADMIN_skin.cpp
NODE_ADMIN_CONTENT=node_admin/base_content.h node_admin/main_content.h
NODE_ADMIN_HEADERS=node_admin/base_app.h node_admin/main_app.h node_admin/admin_app.h
NODE_ADMIN_CPP=node_admin/base_app.cpp node_admin/main_app.cpp node_admin/admin_app.cpp node_admin/base_content.cpp node_admin/main_content.cpp

#JSON-RPC Node API CppCMS application
NODE_API_HEADERS=node_api/node_api.h
NODE_API_CPP=node_api/node_api.cpp

#Shared utils
UTILS_HEADERS=utils/crypto.h
UTILS_CPP=utils/crypto.cpp

all: separator run

.PHONY: all, separator, clean, documentation, run

separator:
	@echo
	@echo
	@echo Running make all on p2psn
	@echo
	@echo

documentation: docs/html/index.html

docs/html/index.html: $(MAIN_CPP) $(MAIN_HEADERS) $(NODE_ADMIN_HEADERS) $(NODE_ADMIN_CONTENT) $(NODE_ADMIN_CPP) $(NODE_API_HEADERS) $(NODE_API_CPP) $(UTILS_HEADERS) $(UTILS_CPP) $(NODE_ADMIN_SKIN)
	doxygen Doxyfile

run/noded: $(MAIN_CPP) $(MAIN_HEADERS) $(NODE_ADMIN_HEADERS) $(NODE_ADMIN_CONTENT) $(NODE_ADMIN_CPP) $(NODE_API_HEADERS) $(NODE_API_CPP) $(UTILS_HEADERS) $(UTILS_CPP) $(NODE_ADMIN_GENERATED)
	$(CXX) $(OPTIONS) $(MAIN_CPP) $(NODE_ADMIN_CPP) $(NODE_API_CPP) $(UTILS_CPP) $(NODE_ADMIN_GENERATED) -o run/noded ${LIBS}

run/config.js: config/config.js
	cp config/config.js run/config.js
	
$(NODE_ADMIN_GENERATED): $(NODE_ADMIN_SKIN)
	cppcms_tmpl_cc $(NODE_ADMIN_SKIN) -o $(NODE_ADMIN_GENERATED)
	
clean:
	rm -fr run/* cppcms_rundir build/* docs/* *~ main/*~ node_admin/*~ node_api/*~ consif/*~

run: run/noded run/config.js
	./noded

