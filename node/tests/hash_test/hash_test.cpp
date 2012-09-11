#include <iostream>
#include "../../src/utils/crypto.hpp"

using namespace std;
using namespace p2psn::utils;

int main(int argc, char** argv) {
	string param = argv[1];

	cout << signature::md5(param) << endl;

	return 0;	
}

