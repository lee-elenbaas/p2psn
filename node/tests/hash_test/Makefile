LIBS=-lcppcms
OPTIONS=-O0 -Wall -Wextra -std=c++0x -g3 -rdynamic

all: hash_test

.PHONY: all clean

hash_test: hash_test.cpp ../../src/utils/crypto.cpp ../../src/utils/crypto.hpp
	$(CXX) $(OPTIONS) hash_test.cpp ../../src/utils/crypto.cpp -o hash_test ${LIBS}
	
clean:
	rm -f hash_test *~

