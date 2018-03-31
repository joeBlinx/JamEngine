//
// Created by stiven on 18-03-02.
//

#include "sprite.hpp"
namespace JamEngine{

	Sprite::Sprite(SpriteSheet *spriteSheet, float timeChange, int nbImage) :
			spriteSheet(spriteSheet),
			timeChange(timeChange),
			nbImage(nbImage){

	}

	void Sprite::update(float delta) {
		infoSprite.size = spriteSheet->getSize();
		infoSprite.orig = spriteSheet->getOrig(nbImage);

		currentTime += delta;
		if( currentTime > timeChange && timeChange){
			nbImage++;
			currentTime = 0;
			if(nbImage >= spriteSheet->getNbImage()){
				nbImage = 0;
			}
		}
		spriteSheet->bindTexture(0);


	}

	const info &Sprite::getInfoSprite() const {
		return infoSprite;
	}
}