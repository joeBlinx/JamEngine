//
// Created by stiven on 18-01-20.
//

#include <fstream>
#include "stringUtil.h"
#include <vector>

#include <iostream>
#include <2dEngine/keyHandler.hpp>
#include <SDL2/SDL_keycode.h>

namespace JamEngine {

/***
 *
 * @param configFile path to configFile
 *
 * content of configFile must be
 *
 * Forward = w, z
 */
	std::map<std::string, int> const keyBind{
			{"left_ctrl",   SDLK_LCTRL},
			{"right_ctrl",  SDLK_RCTRL},
			{"left_shift",  SDLK_LSHIFT},
			{"right_shift", SDLK_RSHIFT},
			{"space",       SDLK_SPACE},
			{"up",          SDLK_UP},
			{"down",        SDLK_DOWN},
			{"right",       SDLK_RIGHT},
			{"left",        SDLK_LEFT},
			{"escape",      SDLK_ESCAPE},
			{"tab",         SDLK_TAB},
			{"left_alt",    SDLK_LALT},
			{"right_alt",   SDLK_RALT},
			{"enter",       SDLK_KP_ENTER}
	};

	void assign(int & value, std::string strValue){
		strValue = utils::removeChar(std::move(strValue), ' ');
		if(strValue.size() > 1){
			strValue = utils::toLowerCase(std::move(strValue));
			try {
				value = keyBind.at(strValue);
			}catch (std::out_of_range const & e){
				value = -1;
				std::cerr << strValue << " is not a valid value" << std::endl;
			}
		}else{
			//strValue = utils::toUpperCase(std::move(strValue)); // SDL2 take the loweer case, glfw the uppercase
			value = strValue[0];
		}
	}

	void KeyHandler::mapKey(std::string &&configFile) {
		using namespace utils;
		std::ifstream file{configFile};
		if(!file.is_open()){
			std::cerr<< "file "<< configFile << " hasn't been find" <<std::endl;
			return;
		}
		unsigned constexpr size = 100;
		char line[size] = {};
		std::string linestr;
		while (true) {

			typeMap newPair;
			auto & [key, pair] = newPair;
			auto & [value1, value2] = pair;
			file.getline(line, size);

			linestr = line;
			if(linestr.empty()){
				continue;
			}
			std::vector<std::string> splits = utils::split(linestr, '=');
			key = removeChar(splits[0], ' ');
			if(splits.size() < 2){
				std::cerr << "there is no value with the key "<< key << ".Make sure you haven't forgot to add one" << std::endl;
				value1 = -1;
				value2 = -1;
			}else {
				splits = split(splits[1], ',');
				assign(value1, splits[0]);

				if (splits.size() > 1) {
					assign(value2, splits[1]);
				} else {
					value2 = -1;
				};
			}
			keys.emplace(std::move(newPair));
			if (file.eof()) {
				break;
			}
		}
	}

	KeyHandler::iterator KeyHandler::begin() {
		return keys.begin();
	}

	KeyHandler::const_iterator KeyHandler::begin() const {
		return keys.begin();
	}

	KeyHandler::iterator KeyHandler::end() {
		return keys.end();
	}

	KeyHandler::const_iterator KeyHandler::end() const {
		return keys.end();
	}



	std::pair<int, int>  & KeyHandler::operator[](std::string const & key) {
		return keys[key];
	}

}