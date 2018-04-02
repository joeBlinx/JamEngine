//
// Created by stiven on 18-03-02.
//

#ifndef INC_2DENGINE_SPRITESHEET_HPP
#define INC_2DENGINE_SPRITESHEET_HPP

#include <glish/Texture.hpp>
#include <glm/vec2.hpp>

namespace JamEngine {
	class SpriteSheet {

		int nbImage;
		glm::vec2 size;
		int nbImageHoriz;
		int nbImageVert;
		glish::Texture texture;

	public:
		SpriteSheet() = default;

		SpriteSheet(std::string const & file, int nbHoriz, int nbVert);

		int getNbImage() const;

		const glm::vec2 &getSize() const;

		void bindTexture(int number = 0) const;

		int getNbImageHoriz() const;

		int getNbImageVert() const;

		glm::vec2 getOrig(int nbImage);

	};
}


#endif //INC_2DENGINE_SPRITESHEET_HPP
