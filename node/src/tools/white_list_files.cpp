/////////////////////////////////////////////////////////////////////////////////////////////
//
// hash folder utility
//
// hash all files from the source folder that fit the given pattern into the target folder
//
/////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>
#include <ifstream>
#include <ofstream>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <cppcms/json.h>
#include "../utils/white_list_folder.hpp"

using namespace p2psn::utils;
using namespace std;
using namespace cppcms::json;
namespace po = boost::program_options;
namespace fs = boos::filesystem;

namespace {
	void version() {
		cout << "White List Folder Utility version 0.1" << endl;
	}

	void usage(string app_name, po::options_description cli_options) {
		version();
		cout	<< "Usage: " << app_name << " <options>" << endl
			<< cli_options << endl;
	}

	void build_white_list(string target, path src, path dst, string pattern, string mime, bool append, bool keep_extension, bool keep_filename, bool recursive, bool keep_folder) {
		value white_list;

		if (append) {
			ifstream existing_white_list(target);

			if (existing_white_list)
				white_list.load(existing_white_list, true);
		}
	
		white_list_folder(
			white_list, 
			src, 
			dst, 
			pattern,
			mime,
			keep_extension,
			keep_filename,
			recursive,
			keep_folders,
		);

		ofstream target_file(target);
		white_list.save(target_file);
	}
}

int main(int argc, char** argv) {
	try {
		po::options_description cli_options("Parameters");

		cli_options.add_options()
			("help,h", "Generate usage message")
			("version,v", "Print the version message")
			("target,t", po::value<string>(), "Target file name to place the white list into")
			("src,s", po::value<string>(), "Source folder to hash files from")
			("dst,d", po::value<string>(), "Target folder to place files into")
			("pattern,p", po::value<string>(), "File pattern for files to use")
			("mime,m", po::value<string>(), "Mime type of the hashed files")
			("append,a", po::value<bool>()->default_value(false)->implicit_value(true), "Append to the target file")
			("recursive,r", po::value<bool>()->default_value(false)->implicit_value(true), "Recursive scan inside subfolders")
			("keep-extension,x", po::value<bool>()->default_value(false)->implicit_value(true), "Keep extension in destination folder")
			("keep-filename,n", po::value<bool>()->default_value(false)->implicit_value(true), "Keep original filename")
			("keep-folders,f", po::value<bool>()->default_value(false)->implicit_value(true), "Keep folder structure");

		po::variables_map vm;

		po::store( po::command_line_parser( argc, argv ).options( cli_options ).run(), vm );
		po::notify( vm );

		if (vm.count("version")) {
			version();
			return 0;
		}

		if (vm.count("help")) {
			usage(argv[0], cli_options);
			return 0;
		}

		if (!vm.count("target") || !vm.count("src") || !vm.count("dst") || !vm.count("pattern") || !vm.count("mime")) {
			usage(argv[0], cli_options);
			return -1;
		}

		build_white_list(
			vm["target"].as<string>(), 
			vm["src"].as<string>(), 
			vm["dst"].as<string>(), 
			vm["pattern"].as<string>(),
			vm["mime"].as<string>(),
			vm["append"].as<bool>(),
			vm["keep-extension"].as<bool>(),
			vm["keep-filename"].as<bool>(),
			vm["recursive"].as<bool>(),
			vm["keep-folders"].as<bool>()
		);

		return 0;
	}
	catch(exception const &e) {
		cerr << e.what() << endl;
        
		return -2;
	}
}

