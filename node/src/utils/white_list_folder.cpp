#include "white_list_folder.hpp"

#include <boost/filesystem.hpp>
#include <cppcms/json.h>
#include "../utils/crypto.hpp"
#include <ifstream>

#include <iostream>

using namespace p2psn::utils;
using namespace std;
using namespace cppcms::json;

void p2psn::utils::white_list_folder(
	string target, 
	string source, 
	string destination, 
	string pattern, 
	string extension, 
	bool append, 
	bool keep_extension, 
	bool keep_filename, 
	bool recursive, 
	bool keep_folders
) {
	value white_list;

	if (append) {
		ifstream existing_white_list(target);

		if (existing_white_list)
			white_list.load(existing_white_list);
	}
	
	cout	<< "Process" << endl
		<< "Target " << target << endl
		<< "Source " << source << endl
		<< "Destination " << destination << endl
		<< "Pattern " << pattern << endl
		<< "Extension " << extension << endl
		<< "append " << append << endl
		<< "keep extension " << keep_extension << endl
		<< "keep filename " << keep_filename << endl;

}
