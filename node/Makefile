LIBS=-lcppcms -lbooster

MAIN_SKIN=main/master.tmpl main/page.tmpl main/about.tmpl
MAIN_GENERATED=build/main_skin.cpp
MAIN_CONTENT=main/content.h
MAIN_HEADERS=main/main_app.h 
MAIN_CPP=main/node_app.cpp main/main_app.cpp
API_HEADERS=api/node_api.h
API_CPP=api/node_api.cpp

all: run/noded run/config.js

.PHONY: all

run/noded: $(MAIN_HEADERS) $(MAIN_CONTENT) $(MAIN_CPP) $(API_HEADERS) $(API_CPP) $(MAIN_GENERATED)
	$(CXX) -O2 -Wall -g $(MAIN_CPP) $(API_CPP) $(MAIN_GENERATED) -o run/noded ${LIBS}

run/config.js: config/config.js
	cp config/config.js run/config.js
	
$(MAIN_GENERATED): $(MAIN_SKIN)
	cppcms_tmpl_cc $(MAIN_SKIN) -o $(MAIN_GENERATED)

clean:
	rm -fr run/* cppcms_rundir build/* *~ main/*~ api/*~

