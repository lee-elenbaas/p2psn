LIBS=-lcppcms -lbooster

all: node

node: main/main_app.cpp
	$(CXX) -O2 -Wall -g main/main_app.cpp -o node ${LIBS}

clean:
	rm -fr node node.exe cppcms_rundir
