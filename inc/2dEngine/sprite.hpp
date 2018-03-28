//
// Created by stiven on 18-03-02.
//

#ifndef INC_2DENGINE_SPRITE_HPP
#define INC_2DENGINE_SPRITE_HPP

#include <2dEngine/spriteSheet.hpp>
#include <glm/vec2.hpp>

namespace JamEngine {
	struct info{
		glm::vec2 orig;
		glm::vec2 size;
	};
	class Sprite {

		SpriteSheet * spriteSheet = nullptr ;
		float timeChange = 0;
		float currentTime = 0;
		int nbImage = 0;
		info infoSprite;
	public:
		Sprite() = default;
		Sprite(SpriteSheet *spriteSheet, float timeChange, int nbImage = 0);
		void update(float delta);

		const info &getInfoSprite() const;

		operator bool(){
			return spriteSheet;
		}
	};
}


#endif //INC_2DENGINE_SPRITE_HPP
