LIBS=-lcppcms -lbooster -lboost_filesystem -lboost_system
OPTIONS=-O0 -std=c++11 -Wall -Wextra -g3 -rdynamic

NODE_ADMIN_GENERATED=src/generated/noded_skin.cpp
CPPCMS_TMPL_CC=third_party/cppcms/bin/cppcms_tmpl_cc

all: run

.PHONY: all clean documentation run statics dependancies

# doxygen documentation generation
documentation: docs/html/index.html

docs/html/index.html: $(MAIN_CPP) $(MAIN_HEADERS) $(NODE_ADMIN_HEADERS) $(NODE_ADMIN_CONTENT) $(NODE_ADMIN_CPP) $(NODE_API_HEADERS) $(NODE_API_CPP) $(UTILS_HEADERS) $(UTILS_CPP) $(NODE_ADMIN_SKIN)
	doxygen Doxyfile

# node deamon

build/noded:	\
		build/node/main/noded.o \
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
		build/utils/whitelist_static_app.o \
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
	$(CXX) $(OPTIONS) $^ -o $@ -lboost_program_options $(LIBS)

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
build/config.js: src/node/config/config_base.js build/node/config/node_whitelist.js build/node/config/client_whitelist.js
	$(CPP) -E -x c -P -C $< -o $@
	
#noded static files
build/node/config/node_whitelist.js: run/white_list_files
	echo $@ | sed "s/\/[^\/]*$$//" | xargs mkdir -p 
	./run/white_list_files --target="$@" --src=src/node/static_files --dst=run/static_files --pattern=".*\\.css" --pattern-type=regex --mime="text/css" --keep-extension --copy-method=hard --recursive --hash-type=md5

#client static files
build/node/config/client_whitelist.js: run/white_list_files
	echo $@ | sed "s/\/[^\/]*$$//" | xargs mkdir -p 
	./run/white_list_files --target="$@" --src=src/client --dst=run/client --pattern=".*\\.html" --pattern-type=regex --mime="text/html" --keep-extension --keep-filename --keep-folders --copy-method=hard --recursive --hash-type=md5
	./run/white_list_files --target="$@" --src=src/client --dst=run/client --pattern=".*\\.css" --pattern-type=regex --mime="text/css" --keep-extension --keep-filename --keep-folders --copy-method=hard --recursive --hash-type=md5 --append
	./run/white_list_files --target="$@" --src=src/client --dst=run/client --pattern=".*\\.js" --pattern-type=regex --mime="text/javascript" --keep-extension --keep-filename --keep-folders --copy-method=hard --recursive --hash-type=md5 --append
	./run/white_list_files --target="$@" --src=src/client --dst=run/client --pattern=".*\\.png" --pattern-type=regex --mime="image/png" --keep-extension --keep-filename --keep-folders --copy-method=hard --recursive --hash-type=md5 --append
	./run/white_list_files --target="$@" --src=src/client --dst=run/client --pattern=".*\\.svg" --pattern-type=regex --mime="image/svg+xml" --keep-extension --keep-filename --keep-folders --copy-method=hard --recursive --hash-type=md5 --append
	
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
run: run/noded run/config.js
	./noded
