/////////////////////////////////////////////////////////////////////////////////////////////
//
// hash folder utility
//
// hash all files from the source folder that fit the given pattern into the target folder
//
/////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>
#include "../utils/crypto.hpp"

using namespace std;

namespace {
	void usage(string app_name) {
		cout	<< "Hash Folder Utility" << endl
			<< "Usage: " << app_name << " <source> <target> [<extension>]" << endl
			<< "\t<source>\t- Source folder to hash files from." << endl
			<< "\t<target>\t- Target folder to copy files to." << endl
			<< "\t<extension>\t- (Optional.) The extension of the files to copy. All files if ommited." << endl;
	}

	void hash_folder(string source, string target, string extension) {
	}
}

int main(int argc, char** argv) {

	if (argc != 3) {
		usage(argv[0]);
		return 1;
	}

	hash_folder(argv[1], argv[2], argv[3]);

	return 0;
}

