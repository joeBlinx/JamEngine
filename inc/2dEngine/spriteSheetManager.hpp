//
// Created by stiven on 18-03-02.
//

#ifndef INC_2DENGINE_SPRITESHEETMANGER_HPP
#define INC_2DENGINE_SPRITESHEETMANGER_HPP

#include <string>
#include <map>
#include "spriteSheet.hpp"

namespace JamEngine {
	class SpriteSheetManager {
		static SpriteSheetManager spriteSheetManager;
		SpriteSheet empty;
		std::string folder;
		std::map<std::string, SpriteSheet> spriteSheets;
	public:

		static void init(std::string && initFile);
		static SpriteSheet & get(std::string const &key);

	};
}


#endif //INC_2DENGINE_SPRITESHEETMANGER_HPP
