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
    std::vector<std::string> split(std::string const & str, char delimiter){
        std::vector<std::string> splitString;
        char const * string = str.c_str();
        std::string add;
        bool isDelim = false;
        while(*string){
            if((isDelim = *string == delimiter)){
                splitString.push_back(add);
                add.clear();
            }else{
                add += *string;
            }
            string++;
        }
        if(!isDelim) {
            splitString.push_back(add);
        }
	    return splitString;
    }

	std::string removeChar(std::string str, char toRemove){
		for (auto it = str.begin() ; it != str.end() ; ){
			if(*it == toRemove){
				str.erase(it);
			}else{
				it++;
			}
		}
		return str;
	}

	std::string toLowerCase(std::string str) {
		for (auto & a : str){
			if(a >= 'A' && a <= 'Z'){
				a = a - 'A' + 'a';
			}
		}
		return str;
	}

	std::string toUpperCase(std::string str) {
		for (auto & a : str){
			if(a >= 'a' && a <= 'z'){
				a = a - 'a' + 'A';
			}
		}
		return str;
	}
}