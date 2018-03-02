//
// Created by stiven on 17-09-29.
//

#include "stringUtil.h"
namespace utils{

    std::string extractExtension(std::string const & path){
        size_t pos = path.rfind('.');
        return path.substr(pos);
    }
    std::string extractPath(std::string const & path){
        std::string absolutePath;
        size_t pos = path.rfind('/');

        return path.substr(0, pos+1);

    }
    std::string extractFile(std::string const & path){
        std::string absolutePath;
        size_t pos = path.rfind('/');

        return path.substr(pos+1);
    }
}