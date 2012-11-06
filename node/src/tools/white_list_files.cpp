/////////////////////////////////////////////////////////////////////////////////////////////
//
// hash folder utility
//
// hash all files from the source folder that fit the given pattern into the target folder
//
/////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <cppcms/json.h>
#include <booster/regex.h>
#include "../utils/crypto.hpp"
#include "../utils/regex_utils.hpp"
#include "../utils/log.hpp"

using namespace p2psn::utils;
using namespace std;
using namespace cppcms::json;
using namespace booster;
namespace po = boost::program_options;
namespace fs = boost::filesystem;

namespace {
	typedef void (*copy_function_t)(const fs::path&, const fs::path&);

	void version() {
		cout << "White List Folder Utility version 0.1" << endl;
	}

	void usage(string app_name, po::options_description cli_options) {
		version();
		cout	<< "Usage: " << app_name << " <options>" << endl
			<< cli_options << endl;
	}

	inline string hash_file(fs::path file) {
		return signature::md5(file.string());
	}

	fs::path storage_path(const fs::path& file, const string& hash, bool keep_extension, bool keep_filename, bool keep_folder) {
		fs::path res;

		if (keep_folder)
			res /= file.parent_path();
		if (keep_filename)
			res /= file.stem();
		else
			res /= hash;
		if (keep_extension)
			res += file.extension();

		return res;
	}

	void handle_file(value& white_list, const fs::path& dst, fs::path file, const string& mime, bool keep_extension, bool keep_filename, bool keep_folder, copy_function_t copy) {
		string hash = hash_file(file);
	
		fs::path tf = storage_path(file, hash, keep_extension, keep_filename, keep_folder);

		fs::path dst_file = dst/tf;

		fs::create_directory(dst_file.parent_path());
		fs::remove(dst_file);
		copy(file, dst_file);

		white_list.set(hash+".mime", mime);
		white_list.set(hash+".path", tf.string());
	}

	template<typename FileIterator>
	void handle_file_list(value& white_list, const fs::path& dst, FileIterator start, FileIterator end, const booster::regex& pattern, const string& mime, bool keep_extension, bool keep_filename, bool keep_folder, copy_function_t copy) {
		for(FileIterator f = start; f != end; ++f) {
			fs::path file = f->path();

			if (regex_match(file.string(), pattern))
				handle_file(white_list, dst, file, mime, keep_extension, keep_filename, keep_folder, copy);
		}
	}

	void build_white_list(string target, const fs::path& src, const fs::path& dst, const regex& pattern, const string& mime, bool append, bool recursive, bool keep_extension, bool keep_filename, bool keep_folder, copy_function_t copy) {
		value white_list;

		if (append) {
			ifstream existing_white_list(target.c_str());

			if (existing_white_list)
				white_list.load(existing_white_list, true);
		}
	
		if (recursive)
			handle_file_list(white_list, dst, fs::recursive_directory_iterator(src), fs::recursive_directory_iterator(), pattern, mime, keep_extension, keep_filename, keep_folder, copy);
		else
			handle_file_list(white_list, dst, fs::directory_iterator(src), fs::directory_iterator(), pattern, mime, keep_extension, keep_filename, keep_folder, copy);

		ofstream target_file(target.c_str());
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
			("keep-folders,f", po::value<bool>()->default_value(false)->implicit_value(true), "Keep folder structure")
			("pattern-type", po::value<string>()->default_value("pattern"), "Type of file matching mechanism: pattern, regex")
			("copy-method", po::value<string>()->default_value("copy"), "Copy method to copy the files with: copy, hard"); // , soft

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

		if (!vm.count("target")) {
			cout << "missing target file" << endl;
			usage(argv[0], cli_options);
			return -1;
		}
		if (!vm.count("src")) {
			cout << "missing source folder" << endl;
			usage(argv[0], cli_options);
			return -1;
		}
		if (!vm.count("dst")) {
			cout << "missing destination folder" << endl;
			usage(argv[0], cli_options);
			return -1;
		}
		if (!vm.count("mime")) {
			cout << "missing mime type" << endl;
			usage(argv[0], cli_options);
			return -1;
		}
		if (!vm.count("pattern")) {
			cout << "missing file pattern" << endl;
			usage(argv[0], cli_options);
			return -1;
		}

		regex pattern_regex;

		if (vm["pattern-type"].as<string>() == "regex") {
			SDEBUG("pattern reg");
			pattern_regex = regex(vm["pattern"].as<string>());
		}
		else if (vm["pattern-type"].as<string>() == "pattern") {
			SDEBUG("pattern path");
			pattern_regex = regex(pattern_to_regex<regex>(vm["pattern"].as<string>()));
		}
		else {
			cout << "unsupported pattern type" << endl;
			usage(argv[0], cli_options);
			return -1;
		}
		SDEBUG("pattern regex: " + pattern_regex.str());

		copy_function_t copy;

		if (vm["copy-method"].as<string>() == "copy")
			copy = (copy_function_t)&fs::copy_file;
		else if (vm["copy-method"].as<string>() == "hard")
			copy = (copy_function_t)&fs::create_hard_link;
//		else if (vm["copy-method"].as<string>() == "soft")
//			copy == (copy_function_t)&fs::create_symlink;
		else {
			cout << "unsupported copy method" << endl;
			usage(argv[0], cli_options);
			return -1;
		}

		build_white_list(
			vm["target"].as<string>(), 
			vm["src"].as<string>(), 
			vm["dst"].as<string>(), 
			pattern_regex,
			vm["mime"].as<string>(),
			vm["append"].as<bool>(),
			vm["recursive"].as<bool>(),
			vm["keep-extension"].as<bool>(),
			vm["keep-filename"].as<bool>(),
			vm["keep-folders"].as<bool>(),
			copy
		);

		return 0;
	}
	catch(std::exception const &e) {
		cerr << e.what() << endl;
        
		return -2;
	}
}

