LIBS=-lcppcms -lbooster
OPTIONS=-O0 -Wall -Wextra -std=c++0x -g

#Wrapper C++ application
MAIN_HEADERS=
MAIN_CPP=main/noded.cpp

#Main node CppCMS application
NODE_ADMIN_GENERATED=build/ptp2n_node_admin_skin.cpp
NODE_ADMIN_SKIN=node_shared/master.tmpl node_guest/info.tmpl node_guest/about.tmpl node_guest/login.tmpl node_admin_menu/admin_menu.tmpl node_admin_users/admin_users.tmpl node_admin_server/admin_server.tmpl
NODE_ADMIN_CONTENT=node_shared/base_content.hpp node_guest/guest_content.hpp node_admin_shared/admin_shared_content.hpp node_admin_users/admin_users_content.hpp
NODE_ADMIN_HEADERS=node_shared/base_app.hpp node_guest/guest_app.hpp node_admin_shared/admin_base_app.hpp node_admin_menu/admin_menu_app.hpp node_admin_users/admin_users_app.hpp node_admin_server/admin_server_app.hpp
NODE_ADMIN_CPP=node_shared/base_app.cpp node_guest/guest_app.cpp node_admin_shared/admin_base_app.cpp node_admin_menu/admin_menu_app.cpp node_admin_users/admin_users_app.cpp node_shared/base_content.cpp node_guest/guest_content.cpp node_admin_shared/admin_shared_content.cpp node_admin_users/admin_users_content.cpp node_admin_server/admin_server_app.cpp

#JSON-RPC Node API CppCMS application
NODE_API_HEADERS=node_api/node_api.hpp
NODE_API_CPP=node_api/node_api.cpp

#Shared utils
UTILS_HEADERS=utils/crypto.hpp utils/locale_matching.hpp utils/regex_utils.hpp utils/log.hpp utils/signal_handler.hpp utils/serialization.hpp
UTILS_CPP=utils/crypto.cpp utils/locale_matching.cpp utils/signal_handler.cpp

all: separator run

.PHONY: all separator clean documentation run dependancies

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

dependancies: $(MAIN_CPP) $(MAIN_HEADERS) $(NODE_ADMIN_HEADERS) $(NODE_ADMIN_CONTENT) $(NODE_ADMIN_CPP) $(NODE_API_HEADERS) $(NODE_API_CPP) $(UTILS_HEADERS) $(UTILS_CPP) $(NODE_ADMIN_GENERATED)
	$(CXX) -MM $(OPTIONS) $(MAIN_CPP) $(NODE_ADMIN_CPP) $(NODE_API_CPP) $(UTILS_CPP) $(NODE_ADMIN_GENERATED) ${LIBS}

run/config.js: config/config.js
	cp config/config.js run/config.js
	
$(NODE_ADMIN_GENERATED): $(NODE_ADMIN_SKIN)
	cppcms_tmpl_cc $(NODE_ADMIN_SKIN) -o $(NODE_ADMIN_GENERATED)
	
clean:
	rm -fr run/* cppcms_rundir build/* docs/* ./*~ main/*~ node_shared/*~ node_guest/*~ node_admin_shared/*~ node_admin_menu/*~ node_admin_users/*~ node_api/*~ utils/*~ config/*~

run: run/noded run/config.js
	./noded

