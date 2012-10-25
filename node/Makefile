LIBS=-lcppcms -lbooster
OPTIONS=-O0 -std=c++0x -Wall -Wextra -g3 -rdynamic -I third_party/boost -L third_party/boost/stage/lib

NODE_ADMIN_GENERATED=src/generated/noded_skin.cpp
CPPCMS_TMPL_CC=third_party/cppcms/bin/cppcms_tmpl_cc

all: run

.PHONY: all clean documentation run statics dependancies

# doxygen documentation generation
documentation: docs/html/index.html

docs/html/index.html: $(MAIN_CPP) $(MAIN_HEADERS) $(NODE_ADMIN_HEADERS) $(NODE_ADMIN_CONTENT) $(NODE_ADMIN_CPP) $(NODE_API_HEADERS) $(NODE_API_CPP) $(UTILS_HEADERS) $(UTILS_CPP) $(NODE_ADMIN_SKIN)
	doxygen Doxyfile

# node deamon

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
		build/generated/node/shared/master.o \
		build/generated/node/guest/about.o \
		build/generated/node/guest/info.o \
		build/generated/node/guest/login.o \
		build/generated/node/admin_menu/admin_menu.o \
		build/generated/node/admin_server/admin_server.o \
		build/generated/node/admin_users/admin_users.o
	$(CXX) $(OPTIONS) $^ -o $@ $(LIBS)

# node tools
build/white_list_files:	\
		build/utils/crypto.o \
		build/tools/white_list_files.o
	$(CXX) $(OPTIONS) $^ -o $@ $(LIBS) -lboost_program_options -lboost_filesystem -lboost_system

# rules for generating files

# copy build result to run folder
run/%: build/%
	echo $@ | sed "s/\/[^\/]*$$//" | xargs mkdir -p 
	cp $< $@

# generate object files
build/%.o: src/%.cpp
	echo $@ | sed "s/\/[^\/]*$$//" | xargs mkdir -p 
	$(CXX) $(OPTIONS) -c $< $(LIBS)
	mv *.o $@

src/generated/%.cpp: src/%.tmpl
	echo $@ | sed "s/\/[^\/]*$$//" | xargs mkdir -p 
	$(CPPCMS_TMPL_CC) -o $@ -H "src/generated/$*.hpp" $^

# dependancies
dependancies: build/dependancies_tmpl.mk build/dependancies_cpp.mk

build/dependancies_tmpl.mk:
	mkdir -p build
	find . -type f -name "*.tmpl" | sed "s/\.\/src\/\(.*\.\)tmpl/src\/generated\/\1cpp: src\/\1tmpl/" > $@
	find . -type f -name "*.tmpl" | sed "s/\.\/src\/\(.*\.\)tmpl/src\/generated\/\1cpp/" | xargs echo "build/dependancies_cpp.mk:" >> $@

build/dependancies_cpp.mk: build/dependancies_tmpl.mk
	mkdir -p build
	find . -type f -name "*.cpp" | xargs $(CXX) -MM $(OPTIONS) ${LIBS} | sed "s/.*\.o: src\(\/.*\)\.cpp/build\1\.o: src\1\.cpp/" > $@

include build/dependancies_tmpl.mk 
include build/dependancies_cpp.mk

#configuration
run/config.js: src/node/config/config.js
	mkdir -p run
	cp src/node/config/config.js run/config.js
	
#CppCMS skin
$(NODE_ADMIN_GENERATED):
	echo $@ | sed "s/\/[^\/]*$$//" | xargs mkdir -p 
	$(CPPCMS_TMPL_CC) $^ -o $@

#Clean up	
clean:
	rm -fr run/* cppcms_rundir build/* docs/* src/generated/*
	-rmdir run
	-rmdir build
	-rmdir docs
	-rmdir src/generated
	find . -type f -name "*~" | xargs rm -f
	find . -type f -name "*.gch" | xargs rm -f

# run the node deamon
#run: run/noded run/config.js statics
#	./noded
run:	run/white_list_files
	./run/white_list_files --help
	./run/white_list_files --version
	./run/white_list_files --target build/white_list.js --src src/node/static_files/css --dst run/css --pattern "*.css" --mime "text/css" --keep-extension --copy-method hasr

# static files
statics: run/css/node.css

run/css/node.css: src/node/static_files/css/node.css
	mkdir -p run/css
	cp src/node/static_files/css/node.css run/css

# dependancies for templates
#src/generated/noded_skin.cpp: \
#	src/node/shared/master.tmpl \
#	src/node/guest/login.tmpl \
#	src/node/guest/info.tmpl \
#	src/node/guest/about.tmpl \
#	src/node/admin_menu/admin_menu.tmpl \
#	src/node/admin_users/admin_users.tmpl \
#	src/node/admin_server/admin_server.tmpl


