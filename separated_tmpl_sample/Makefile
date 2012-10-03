LIBS=-lcppcms -lbooster
OPTIONS=-O0 -Wall -Wextra -std=c++0x -g3 -rdynamic
#CPPCMS_TMPL_CC=cppcms_tmpl_cc
CPPCMS_TMPL_CC=tools/cppcms_tmpl_cc

all: run

.PHONY: all clean run

# rules for generating files

# copy build result to run folder
run/%: build/%
	-rm $@
	mkdir -p $@
	-rmdir $@
	cp $< $@

#copy files from src to build
build/%: src/%
	mkdir -p build
	cp -r src/* build/

# generate object files
build/%.o: build/%.cpp
	$(CXX) $(OPTIONS) -c $< $(LIBS)
	mv *.o $@

build/%.cpp: build/%.tmpl
	$(CPPCMS_TMPL_CC) -o $@ -H "build/$*.h" $^

# dependancies
build/derived.cpp: build/derived.tmpl
build/base.cpp: build/base.tmpl
build/dependancies_cpp.mk: build/derived.cpp build/base.cpp

build/derived.o: build/derived.cpp build/derived.h build/base.h build/content.h
build/base.o: build/base.cpp build/base.h build/content.h
build/separated-tmpl-sample.o: build/separated-tmpl-sample.cpp build/content.h

#Clean up	
clean:
	rm -fr run cppcms_rundir build
	-rmdir run
	-rmdir build
	find . -type f -name "*~" | xargs rm -f
	find . -type f -name "*.gch" | xargs rm -f

#run
run: run/separated-tmpl-sample run/config.js
	run/separated-tmpl-sample -c run/config.js

#sample app

build/separated-tmpl-sample:	\
		build/separated-tmpl-sample.o \
		build/base.o \
		build/derived.o
	$(CXX) $(OPTIONS) $^ -o $@ $(LIBS)

