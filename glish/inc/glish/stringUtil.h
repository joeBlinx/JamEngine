//
// Created by stiven on 17-09-29.
//

#ifndef GLENGINE_STRINGUTIL_H
#define GLENGINE_STRINGUTIL_H

#include <string>
namespace utils{
    extern std::string extractExtension(std::string const & path);
    extern std::string extractPath(std::string const & path);
    extern std::string extractFile(std::string const & path);
}

#endif //GLENGINE_STRINGUTIL_H
