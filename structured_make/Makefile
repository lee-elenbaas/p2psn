LIBS=-lcppcms -lbooster

all: clean hello-tmpl

hello-tmpl: hello-tmpl.o my_skin.o
	$(CXX) -Wall $^ -o hello-tmpl ${LIBS}

my_skin.cpp: first.tmpl content.h
	cppcms_tmpl_cc first.tmpl -o my_skin.cpp

clean:
	rm -fr hello-tmpl *.exe *.so my_skin.cpp cppcms_rundir *~ *.o

%.o: %.cpp content.h
	$(CXX) -Wall $< -c ${LIBS}


