/////////////////////////////////////////////////////////////////////////////////////////////
//
// hash folder utility
//
// hash all files from the source folder that fit the given pattern into the target folder
//
/////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
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
using cppcms::json::value;
namespace po = boost::program_options;
namespace fs = boost::filesystem;

namespace {
	typedef void (*copy_function_t)(const fs::path&, const fs::path&);

	void copy_file(const fs::path& src, const fs::path& dst) {
	//	fs::copy_file(src, dst);
	}
	void hard_link_file(const fs::path& src, const fs::path& dst) {
		fs::create_hard_link(src,dst);
	}
	void soft_link_file(const fs::path& src, const fs::path& dst) {
		fs::create_symlink(src,dst);
	}
	
	void version() {
		cout << "White List Folder Utility version 0.1" << endl;
	}

	void usage(string app_name, po::options_description cli_options) {
		version();
		cout	<< "Usage: " << app_name << " <options>" << endl
			<< cli_options << endl;
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

	void handle_file(value& white_list, const fs::path& src, const fs::path& dst, fs::path file, const string& mime, const string& http_headers, bool keep_extension, bool keep_filename, bool keep_folder, copy_function_t copy, hash_function_t hash) {
		auto relative_file = file.string().substr(src.string().length());
		
		auto sig = hash(relative_file);
	
		auto tf = storage_path(relative_file.substr(1), sig, keep_extension, keep_filename, keep_folder);
		
		auto dst_file = dst/tf;

		fs::create_directory(dst_file.parent_path());
		fs::remove(dst_file);
		copy(file, dst_file);

		white_list.set(sig+".mime", mime);
		white_list.set(sig+".path", tf.string());
		white_list.set(sig+".request_path", relative_file);
		
		if (!http_header.empty())
			white_list.set(sig+".http_headers", http_headers);
	}

	template<typename FileIterator>
	void handle_file_list(value& white_list, const fs::path& src, const fs::path& dst, FileIterator start, FileIterator end, const booster::regex& pattern, const string& mime, const string& http_headers, bool keep_extension, bool keep_filename, bool keep_folder, copy_function_t copy, hash_function_t hash) {
		for(FileIterator f = start; f != end; ++f) {
			fs::path file = f->path();

			if (!is_regular_file(f->status()))
				continue;
			if (!regex_match(file.string(), pattern))
				continue;

			handle_file(white_list, src, dst, file, mime, http_headers, keep_extension, keep_filename, keep_folder, copy, hash);
		}
	}

	void build_white_list(string target, const fs::path& src, const fs::path& dst, const booster::regex& pattern, const string& mime, const string& http_headers, bool append, bool recursive, bool keep_extension, bool keep_filename, bool keep_folder, copy_function_t copy, hash_function_t hash) {
		value white_list;

		if (append) {
			ifstream existing_white_list(target.c_str());

			if (existing_white_list)
				white_list.load(existing_white_list, true);
		}
	
		if (recursive)
			handle_file_list(
				white_list,
				src, 
				dst, 
				fs::recursive_directory_iterator(src), 
				fs::recursive_directory_iterator(), 
				pattern, 
				mime, 
				http_headers,
				keep_extension, 
				keep_filename, 
				keep_folder, 
				copy,
				hash
			);
		else
			handle_file_list(
				white_list, 
				src, 
				dst,
				fs::directory_iterator(src), 
				fs::directory_iterator(), 
				pattern, 
				mime, 
				http_headers,
				keep_extension, 
				keep_filename, 
				keep_folder, 
				copy,
				hash
			);

		if (!white_list.is_undefined()) {
			ofstream target_file(target.c_str());
		
			white_list.save(target_file);
		}
	}
}

int main(int argc, char** argv) {
	try {
		po::options_description cli_generic("Generic Options");
		po::options_description cli_output("Output Options");
		po::options_description cli_mapping("Mapping Options");
		po::options_description cli_outfiles("Static File Options");
		po::options_description cli_scanfiles("Scan File Options");

		cli_generic.add_options()
			("help,h", "Generate usage message")
			("version,v", "Print the version message")
			("config,c", "Config file");
		cli_output.add_options()
			("target,t", po::value<string>(), "Target file name to place the white list into")
			("append,a", po::value<bool>()->default_value(false)->implicit_value(true), "Append to the target file");
		cli_mapping.add_options()
			("mime,m", po::value<string>(), "Mime type of the hashed files")
			("http-header,H", po::value<vector<string>>(), "HTTP Header to place in the response (can be specified several times for several headers)")
			("hash-type", po::value<string>()->default_value("md5"), "Hash algorithm used for hashing paths: md5, sha1");
		cli_outfiles.add_options()
			("dst,d", po::value<string>(), "Target folder to place files into")
			("keep-extension,x", po::value<bool>()->default_value(false)->implicit_value(true), "Keep extension in destination folder")
			("keep-filename,n", po::value<bool>()->default_value(false)->implicit_value(true), "Keep original filename")
			("keep-folders,f", po::value<bool>()->default_value(false)->implicit_value(true), "Keep folder structure")
			("copy-method", po::value<string>()->default_value("copy"), "Copy method to copy the files with: copy, hard"); // , soft
		cli_scanfiles.add_options()
			("src,s", po::value<string>(), "Source folder to hash files from")
			("recursive,r", po::value<bool>()->default_value(false)->implicit_value(true), "Recursive scan inside subfolders")
			("pattern,p", po::value<string>(), "File pattern for files to use")
			("pattern-type", po::value<string>()->default_value("path"), "Type of file matching mechanism: path, regex");

		po::options_description cli_options;
		po::options_description config_options;
		
		cli_options.add(cli_generic).add(cli_output).add(cli_outfiles).add(cli_scanfiles);
		config_options.add(cli_output).add(cli_outfiles).add(cli_scanfiles);
		
		po::variables_map vm;

		po::store( po::parse_command_line( argc, argv, cli_options ), vm );
		
		if (vm.count("config"))
			po::store( po::parse_config_file(vm["config"].as<string>(), config_options), vm);

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

		booster::regex pattern_regex;

		if (vm["pattern-type"].as<string>() == "regex") {
			pattern_regex = booster::regex(vm["pattern"].as<string>());
		}
		else if (vm["pattern-type"].as<string>() == "path") {
			cout << "path pattern: " << vm["pattern"].as<string>() << endl;
			string reg = pattern_to_regex<booster::regex>(vm["pattern"].as<string>());
//			auto reg = regex_replace(vm["pattern"].as<string>(), regex("\\."), "\\."); // replace all . in the pattern with \.
//			reg = regex_replace(reg, regex("\\?"), "."); // replace all pattern ? with regex .
//			reg = regex_replace(reg, regex("\\*"), ".*"); // replace all patten * with regex .*
			cout << "regex pattern: " << reg << endl;
			pattern_regex = booster::regex(reg);
		}
		else {
			cout << "unsupported pattern type" << endl;
			usage(argv[0], cli_options);
			return -1;
		}

		copy_function_t copy;

		if (vm["copy-method"].as<string>() == "copy")
			copy = copy_file;
		else if (vm["copy-method"].as<string>() == "hard")
			copy = hard_link_file;
		else if (vm["copy-method"].as<string>() == "soft")
			copy == soft_link_file;
		else {
			cout << "unsupported copy method" << endl;
			usage(argv[0], cli_options);
			return -1;
		}

		hash_algorithm algo = parse_hash_algorithm(vm["hash-type"].as<string>());

		if (algo == hash_algorithm::illegal) {
			cout << "unsupported hash algorithm" << endl;
			usage(argv[0], cli_options);
			return -1;
		}

		build_white_list(
			vm["target"].as<string>(), 
			vm["src"].as<string>(), 
			vm["dst"].as<string>(), 
			pattern_regex,
			vm["mime"].as<string>(),
			vm["http-header"].as<vector<string>>(),
			vm["append"].as<bool>(),
			vm["recursive"].as<bool>(),
			vm["keep-extension"].as<bool>(),
			vm["keep-filename"].as<bool>(),
			vm["keep-folders"].as<bool>(),
			copy,
			signature::hash_function(algo)
		);

		return 0;
	}
	catch(std::exception const &e) {
		cerr << e.what() << endl;
        
		return -2;
	}
}

