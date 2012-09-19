LIBS=
OPTIONS=-O0 -Wall -Wextra -std=c++0x -g3 -rdynamic

all: run/direct run/structured

dependancies: build/dependancies.mk

build/dependancies.mk:
	mkdir -p build
	find . -type f -name "*.cpp" | xargs $(CXX) -MM $(OPTIONS) ${LIBS} | sed "s/.*\.o: src\(\/.*\)\.cpp/build\1\.o: src\1\.cpp/" > build/dependancies.mk

include build/dependancies.mk

.PHONY: all clean rebuild dependancies

run/direct: src/hellomake.cpp src/lib/hellolib.cpp src/lib/hellolib.hpp
	mkdir -p run/
	$(CXX) $(OPTIONS) -o $@ src/hellomake.cpp src/lib/hellolib.cpp

rebuild: clean all

clean:
	rm -rf run/* build/*
	-rmdir run build
	find . -type f -name "*~" | xargs rm -f
	find . -type f -name "*.gch" | xargs rm -f

run/structured: build/hellomake
	cp $< $@

build/%.o: src/%.cpp
	-rm $@
	mkdir -p $@
	-rmdir $@
	$(CXX) $(OPTIONS) -c $^
	mv *.o $@

#build/hellomake.o: src/hellomake.cpp src/lib/hellolib.hpp
#	mkdir -p build
#	$(CXX) $(OPTIONS) -c $^
#	mv hellomake.o $@

#build/lib/hellolib.o: src/lib/hellolib.cpp src/lib/hellolib.hpp
#	mkdir -p build/lib
#	$(CXX) $(OPTIONS) -c $^
#	mv hellolib.o $@

build/hellomake: build/hellomake.o build/lib/hellolib.o
	$(CXX) $(OPTIONS) -o $@ $^

