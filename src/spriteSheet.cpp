//
// Created by stiven on 18-03-02.
//

#include "spriteSheet.hpp"

namespace JamEngine{

	int SpriteSheet::getNbImage() const {
		return nbImage;
	}

	const glm::vec2 &SpriteSheet::getSize() const {
		return size;
	}



	int SpriteSheet::getNbImageHoriz() const {
		return nbImageHoriz;
	}

	int SpriteSheet::getNbImageVert() const {
		return nbImageVert;
	}

	void SpriteSheet::bindTexture(int number) const{
		texture.bindTexture(number);
	}

	SpriteSheet::SpriteSheet(std::string const &file, int nbHoriz, int nbVert):
			nbImage(nbHoriz*nbVert),
			nbImageHoriz(nbHoriz),
			nbImageVert(nbVert),
			texture(file){
		size.x = 1.0f/nbHoriz;
		size.y = 1.0f/nbVert;
	}

	glm::vec2 SpriteSheet::getOrig(int nbImage) {
		glm::vec2 orig;
		orig.x = nbImage%nbImageHoriz * size.x;

		orig.y = nbImage/nbImageHoriz * size.y;



		return orig;
	}
}
