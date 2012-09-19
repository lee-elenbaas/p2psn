LIBS=
OPTIONS=-O0 -Wall -Wextra -std=c++0x -g3 -rdynamic

all: run/direct run/structured

.PHONY: all clean

run/direct: src/hellomake.cpp src/lib/hellolib.cpp src/lib/hellolib.hpp
	mkdir -p run/
	$(CXX) $(OPTIONS) -o $@ src/hellomake.cpp src/lib/hellolib.cpp

clean:
	rm -rf run/* build/*
	-rmdir run build
	find . -type f -name "*~" | xargs rm -f

run/structured: build/hellomake
	cp $< $@

build/hellomake.o: src/hellomake.cpp src/lib/hellolib.hpp
	mkdir -p build
	$(CXX) $(OPTIONS) -c $^
	mv hellomake.o $@

build/lib/hellolib.o: src/lib/hellolib.cpp src/lib/hellolib.hpp
	mkdir -p build/lib
	$(CXX) $(OPTIONS) -c $^
	mv hellolib.o $@

build/hellomake: build/hellomake.o build/lib/hellolib.o
	$(CXX) $(OPTIONS) -o $@ $^

