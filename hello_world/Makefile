LIBS=-lcppcms -lbooster

MAIN_SKIN=main/master.tmpl main/page.tmpl main/about.tmpl
MAIN_CONTENT=main/content.h
MAIN_HEADERS=main/main_app.h 
MAIN_CPP=main/main_app.cpp

API_HEADERS=api/node_api.h
API_CPP=api/node_api.cpp

all: node

.PHONY: all

node: node.cpp build/main_skin.cpp $(MAIN_HEADERS) $(MAIN_CONTENT) $(MAIN_CPP) $(API_HEADERS) $(API_CPP)
	$(CXX) -O2 -Wall -g node.cpp build/main_skin.cpp $(MAIN_CPP) $(API_CPP) -o node ${LIBS}

build/main_skin.cpp: $(MAIN_SKIN)
	cppcms_tmpl_cc $(MAIN_SKIN) -o build/main_skin.cpp

clean:
	rm -fr node node.exe cppcms_rundir build/* *~ main/*~ api/*~

