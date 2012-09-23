/////////////////////////////////////////////////////////////////////////////////////////////
//
// hash folder utility
//
// hash all files from the source folder that fit the given pattern into the target folder
//
/////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>
#include <boost/program_options.hpp>
#include "../utils/white_list_folder.hpp"

using namespace p2psn::utils;
using namespace std;
namespace po = boost::program_options;

namespace {
	void version() {
		cout << "White List Folder Utility version 0.1" << endl;
	}

	void usage(string app_name, po::options_description cli_options) {
		version();
		cout	<< "Usage: " << app_name << " <options>" << endl
			<< cli_options << endl;
	}
}

int main(int argc, char** argv) {
	try {
		po::options_description cli_options("Parameters");

		cli_options.add_options()
			("help", "Generate usage message")
			("version", "Print the version message")
			("target", po::value<string>(), "Target file name to place the white list into")
			("src", po::value<string>(), "Source folder to hash files from")
			("dst", po::value<string>(), "Target folder to place files into")
			("pattern", po::value<string>(), "File pattern for files to use")
			("mime", po::value<string>(), "Mime type of the hashed files")
			("append", po::value<bool>()->default_value(false)->implicit_value(true), "Append to the target file")
			("recursive", po::value<bool>()->default_value(false)->implicit_value(true), "Recursive scan inside subfolders")
			("keep-extension", po::value<bool>()->default_value(false)->implicit_value(true), "Keep extension in destination folder")
			("keep-filename", po::value<bool>()->default_value(false)->implicit_value(true), "Keep original filename")
			("keep-folders", po::value<bool>()->default_value(false)->implicit_value(true), "Keep folder structure");

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

		white_list_folder(
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

