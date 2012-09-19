LIBS=-lcppcms -lbooster
OPTIONS=-O0 -Wall -Wextra -std=c++0x -g3 -rdynamic

#Wrapper C++ application
MAIN_HEADERS=
MAIN_CPP=src/node/main/noded.cpp

#Main node CppCMS application
NODE_ADMIN_GENERATED=src/generated/noded_skin.cpp
NODE_ADMIN_SKIN=src/node/shared/master.tmpl src/node/guest/info.tmpl src/node/guest/about.tmpl src/node/guest/login.tmpl src/node/admin_menu/admin_menu.tmpl src/node/admin_users/admin_users.tmpl src/node/admin_server/admin_server.tmpl
NODE_ADMIN_CONTENT=src/node/shared/base_content.hpp src/node/guest/guest_content.hpp src/node/admin_shared/admin_shared_content.hpp src/node/admin_users/admin_users_content.hpp
NODE_ADMIN_HEADERS=src/node/shared/base_app.hpp src/node/guest/guest_app.hpp src/node/admin_shared/admin_base_app.hpp src/node/admin_menu/admin_menu_app.hpp src/node/admin_users/admin_users_app.hpp src/node/admin_server/admin_server_app.hpp
NODE_ADMIN_CPP=src/node/shared/base_app.cpp src/node/guest/guest_app.cpp src/node/admin_shared/admin_base_app.cpp src/node/admin_menu/admin_menu_app.cpp src/node/admin_users/admin_users_app.cpp src/node/shared/base_content.cpp src/node/guest/guest_content.cpp src/node/admin_shared/admin_shared_content.cpp src/node/admin_users/admin_users_content.cpp src/node/admin_server/admin_server_app.cpp

#JSON-RPC Node API CppCMS application
NODE_API_HEADERS=src/node/node_api/node_api.hpp
NODE_API_CPP=src/node/node_api/node_api.cpp

#Shared utils
UTILS_HEADERS=src/utils/streamutils.hpp src/utils/crypto.hpp src/utils/locale_matching.hpp src/utils/regex_utils.hpp src/utils/log.hpp src/utils/signal_handler.hpp src/utils/serialization.hpp src/utils/hashed_static_app.hpp
UTILS_CPP=src/utils/crypto.cpp src/utils/locale_matching.cpp src/utils/signal_handler.cpp src/utils/hashed_static_app.cpp

#hash folder app

all: separator run

.PHONY: all separator clean documentation run statics dependancies

separator:
	@echo
	@echo
	@echo Running make all on p2psn
	@echo
	@echo

documentation: docs/html/index.html

docs/html/index.html: $(MAIN_CPP) $(MAIN_HEADERS) $(NODE_ADMIN_HEADERS) $(NODE_ADMIN_CONTENT) $(NODE_ADMIN_CPP) $(NODE_API_HEADERS) $(NODE_API_CPP) $(UTILS_HEADERS) $(UTILS_CPP) $(NODE_ADMIN_SKIN)
	doxygen Doxyfile

run/noded: build/noded

build/noded:	build/node/main/noded.o \
		build/node/shared/base_app.o \
		build/node/guest/guest_app.o \
		build/node/admin_shared/admin_base_app.o \
		build/node/admin_menu/admin_menu_app.o \
		build/node/admin_users/admin_users_app.o \
		build/node/shared/base_content.o \
		build/node/guest/guest_content.o \
		build/node/admin_shared/admin_shared_content.o \
		build/node/admin_users/admin_users_content.o \
		build/node/admin_server/admin_server_app.o \
		build/node/node_api/node_api.o \
		build/utils/crypto.o \
		build/utils/locale_matching.o \
		build/utils/signal_handler.o \
		build/utils/hashed_static_app.o \
		build/generated/noded_skin.o
	$(CXX) $(OPTIONS) $(LIBS) -o $@ $^

run/%: build/%
	cp $< $@

build/%.o: src/%.cpp
	-rm $@
	mkdir -p $@
	-rmdir $@
	$(CXX) $(OPTIONS) $(LIBS) -c $^
	mv *.o $@

dependancies: build/dependancies.mk

build/dependancies.mk: $(NODE_ADMIN_GENERATED)
	mkdir -p build
	find . -type f -name "*.cpp" | xargs $(CXX) -MM $(OPTIONS) ${LIBS} | sed "s/.*\.o: src\(\/.*\)\.cpp/build\1\.o: src\1\.cpp/" > build/dependancies.mk

include build/dependancies.mk

run/config.js: src/node/config/config.js
	mkdir -p run
	cp src/node/config/config.js run/config.js
	
$(NODE_ADMIN_GENERATED): $(NODE_ADMIN_SKIN)
	-rm $@
	mkdir -p $@
	-rmdir $@
	cppcms_tmpl_cc $(NODE_ADMIN_SKIN) -o $(NODE_ADMIN_GENERATED)
	
clean:
	rm -fr run/* cppcms_rundir build/* docs/* src/generated/*
	-rmdir run
	-rmdir build
	-rmdir docs
	-rmdir src/generated
	find . -type f -name "*~" | xargs rm -f
	find . -type f -name "*.gch" | xargs rm -f

run: run/noded run/config.js statics
	./noded

statics: run/css/node.css

run/css/node.css: src/node/static_files/css/node.css
	mkdir -p run/css
	cp src/node/static_files/css/node.css run/css

