//
// Created by stiven on 18-01-20.
//

#include <fstream>
#include <utils/stringUtil.h>
#include <vector>

#include <iostream>
#include <2dEngine/input/keyHandler.hpp>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_gamecontroller.h>

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
			    {"enter",       SDLK_RETURN},
			    // Mouse
			    {"btn_left",    SDL_BUTTON_LEFT},
			    {"btn_right",   SDL_BUTTON_RIGHT},
			    {"btn_middle",  SDL_BUTTON_MIDDLE},
			    {"btn_x1",      SDL_BUTTON_X1},
			    {"btn_x2",      SDL_BUTTON_X2},
				{"btn_x1",      SDL_BUTTON_X1},
			    {"btn_x2",      SDL_BUTTON_X2},
				{"wheel_up",    JAMENGINE_WHEEL_UP},
				{"wheel_down",  JAMENGINE_WHEEL_DOWN},
			//Controller

			    {"pad_a",               SDL_CONTROLLER_BUTTON_A},
			    {"pad_b",               SDL_CONTROLLER_BUTTON_B},
			    {"pad_x",               SDL_CONTROLLER_BUTTON_X},
			    {"pad_y",               SDL_CONTROLLER_BUTTON_Y},
			    {"pad_back",            SDL_CONTROLLER_BUTTON_BACK},
			    {"pad_guide",           SDL_CONTROLLER_BUTTON_GUIDE},
			    {"pad_start",           SDL_CONTROLLER_BUTTON_START},
			    {"pad_left_stick",      SDL_CONTROLLER_BUTTON_LEFTSTICK},
			    {"pad_right_stick",     SDL_CONTROLLER_BUTTON_RIGHTSTICK},
			    {"pad_left_shoulder",   SDL_CONTROLLER_BUTTON_LEFTSHOULDER},
			    {"pad_right_shoulder",  SDL_CONTROLLER_BUTTON_RIGHTSHOULDER},
			    {"pad_up",              SDL_CONTROLLER_BUTTON_DPAD_UP},
			    {"pad_down",            SDL_CONTROLLER_BUTTON_DPAD_DOWN},
			    {"pad_left",            SDL_CONTROLLER_BUTTON_DPAD_LEFT},
			    {"pad_right",           SDL_CONTROLLER_BUTTON_DPAD_RIGHT},



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
			linestr = removeChar(linestr, '\r');
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