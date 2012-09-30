LIBS=-lcppcms -lbooster
OPTIONS=-O0 -Wall -Wextra -std=c++0x -g3 -rdynamic
#CPPCMS_TMPL_CC=cppcms_tmpl_cc
CPPCMS_TMPL_CC=tools/cppcms_tmpl_cc

all: run

.PHONY: all clean run build_sources

# rules for generating files

# copy build result to run folder
run/%: build/%
	-rm $@
	mkdir -p $@
	-rmdir $@
	cp $< $@

#copy files from src to build
build_sources:
	cp -r src/* build/

# generate object files
build/%.o: build/%.cpp
	$(CXX) $(OPTIONS) -c $< $(LIBS)

build/%.cpp: build/%.tmpl
	$(CPPCMS_TMPL_CC) -o $@ -H "build/$*.h" $^

# dependancies
dependancies: build/dependancies_tmpl.mk build/dependancies_cpp.mk

build/dependancies_tmpl.mk:
	mkdir -p build
	find src -type f -name "*.tmpl" | sed "s/src\/\(.*\.\)tmpl/build\/\1cpp: build\/\1tmpl/" > $@
	find src -type f -name "*.tmpl" | sed "s/src\/\(.*\.\)tmpl/build\/\1cpp/" | xargs echo "build/dependancies_cpp.mk:" >> $@

include build/dependancies_tmpl.mk

build/dependancies_cpp.mk: build/dependancies_tmpl.mk build_sources
	find build -type f -name "*.cpp" | xargs $(CXX) -MM $(OPTIONS) ${LIBS} | sed "s/.*\.o: \(.*\)\.cpp/\1\.o: \1\.cpp/" > $@

include build/dependancies_cpp.mk

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
		build/first.o
	$(CXX) $(OPTIONS) $^ -o $@ $(LIBS)

