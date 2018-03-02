//
// Created by stiven on 18-03-02.
//

#include "sprite.hpp"
namespace JamEngine{

	Sprite::Sprite(SpriteSheet &spriteSheet, float timeChange):
			spriteSheet(spriteSheet),
			timeChange(timeChange) {

	}

	Sprite::info Sprite::update(float delta) {
		Sprite::info info{};
		info.size = spriteSheet.getSize();
		info.orig = spriteSheet.getOrig(nbImage);

		currentTime += delta;

		if( currentTime > timeChange){
			nbImage++;
			if(nbImage >= spriteSheet.getNbImage()){
				nbImage = 0;
			}
		}
		spriteSheet.bindTexture(0);

		return info;
	}
}