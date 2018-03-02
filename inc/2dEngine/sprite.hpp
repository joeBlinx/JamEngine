//
// Created by stiven on 18-03-02.
//

#ifndef INC_2DENGINE_SPRITE_HPP
#define INC_2DENGINE_SPRITE_HPP

#include "spriteSheet.hpp"

namespace JamEngine {
	class Sprite {
		struct info{
			glm::vec2 orig;
			glm::vec2 size;
		};
		SpriteSheet & spriteSheet;
		int nbImage = 0;
		float timeChange;
		float currentTime = 0;
	public:
		Sprite(SpriteSheet & spriteSheet, float timeChange);
		info update(float delta);
	};
}


#endif //INC_2DENGINE_SPRITE_HPP
