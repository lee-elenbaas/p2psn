LIBS=-lcppcms -lbooster

all: node

node: main/main_app.cpp build/node_skin.cpp main/content.h
	$(CXX) -O2 -Wall -g main/main_app.cpp build/node_skin.cpp -o node ${LIBS}

build/node_skin.cpp: main/master.tmpl main/page.tmpl main/about.tmpl
	cppcms_tmpl_cc main/master.tmpl main/page.tmpl main/about.tmpl -o build/node_skin.cpp

clean:
	rm -fr node node.exe cppcms_rundir build/*

