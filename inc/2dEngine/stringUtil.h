//
// Created by stiven on 17-09-29.
//

#ifndef JAMENGINE_STRINGUTIL_H
#define JAMENGINE_STRINGUTIL_H

#include <string>
#include <vector>
namespace utils{
    extern std::string extractExtension(std::string const & path);
    extern std::string extractPath(std::string const & path);
    extern std::string extractFile(std::string const & path);
	extern std::vector<std::string> split(std::string const & str, char delimiter);
	extern std::string removeChar(std::string str, char toRemove);
	// change only the letter
	extern std::string toLowerCase(std::string str);
	extern std::string toUpperCase(std::string str);
}

#endif //JAMENGINE_STRINGUTIL_H
