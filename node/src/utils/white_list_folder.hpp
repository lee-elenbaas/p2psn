#ifndef __TOOLS_WHITE_LIST_FOLDER_H
#define __TOOLS_WHITE_LIST_FOLDER_H

#include <string>

namespace p2psn {
	namespace utils {
		void white_list_folder(
			std::string target, 
			std::string source, 
			std::string destination, 
			std::string pattern, 
			std::string extension, 
			bool append, 
			bool keep_extension, 
			bool keep_filename, 
			bool recursive, 
			bool keep_folders
		);
	}
}

#endif // __TOOLS_WHITE_LIST_FOLDER_H

