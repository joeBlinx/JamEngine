//
// Created by stiven on 18-04-01.
//

#ifndef INC_2DENGINE_SQUARECOLLIDER_HPP
#define INC_2DENGINE_SQUARECOLLIDER_HPP

#include <2dEngine/collider/collider.hpp>

namespace JamEngine {
	class SquareCollider : public  Collider{
		glm::vec2 size;
	public:
		SquareCollider(Entity * ent, glm::vec2 upperLeftCorner, glm::vec2 size );

		void collide(SquareCollider &collider) override;

		void collide(SphereCollider &collider) override;

		const glm::vec2 &getSize() const;
	};
}


#endif //INC_2DENGINE_SQUARECOLLIDER_HPP
