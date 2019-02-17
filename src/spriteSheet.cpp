//
// Created by stiven on 18-03-02.
//

#include "spriteSheet.hpp"
#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>
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

	void SpriteSheet::bindTexture(int number) {
		texture.activeTexture(number);
	}

	SpriteSheet::SpriteSheet(std::string const &file, int nbHoriz, int nbVert):
			nbImage(nbHoriz*nbVert),
			nbImageHoriz(nbHoriz),
			nbImageVert(nbVert){
		size.x = 1.0f/nbHoriz;
		size.y = 1.0f/nbVert;

		int texWidth, texHeight, texChannels;
		stbi_uc *pixels = stbi_load(file.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

		texture = glish3::Texture2D{glish3::texture_settings{
			texWidth, texHeight, pixels
		}};

	}

	glm::vec2 SpriteSheet::getOrig(int nbImage) {
		glm::vec2 orig;
		orig.x = nbImage%nbImageHoriz * size.x;

		orig.y = nbImage/nbImageHoriz * size.y;



		return orig;
	}
}
