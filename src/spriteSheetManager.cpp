//
// Created by stiven on 18-03-02.
//

#include <fstream>
#include <iostream>
#include "spriteSheetManager.hpp"
#include "stringUtil.h"
namespace JamEngine{
	SpriteSheetManager SpriteSheetManager::spriteSheetManager;


	void SpriteSheetManager::init(std::string &&initFile) {
		std::string & folder = spriteSheetManager.folder;
		auto & spriteSheets = spriteSheetManager.spriteSheets;

		std::ifstream file{initFile};
		if(!file.is_open()){
			std::cerr << initFile << " was not found" << std::endl;
			return;
		}

		file >> folder;

		std::string key, path;
		int nbHoriz, nbVert;
		while (1){
			if(!(file >> key >> path >> nbHoriz >> nbVert)){
				break;
			}
			spriteSheets.emplace(std::pair{key, SpriteSheet{folder+"/" + path, nbHoriz, nbVert}});
		}

	}

	SpriteSheet & SpriteSheetManager::get(std::string const &key) {
		auto & spriteSheets = spriteSheetManager.spriteSheets;
		if(spriteSheets.find(key) != spriteSheets.end()){
			return spriteSheets[key];
		}
		std::cerr << "this key : " << key << " doesn't exist";
		return spriteSheetManager.empty;

	}
}