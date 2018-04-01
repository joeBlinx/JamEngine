//
// Created by Stiven on 01-Apr-18.
//

#ifndef INC_2DENGINE_SPHERECOLLIDER_HPP
#define INC_2DENGINE_SPHERECOLLIDER_HPP


#include <2dEngine/collider/collider.hpp>
#include <glm/vec2.hpp>
namespace JamEngine {
	class SphereCollider :public Collider{
		float diameter;
	public:
		SphereCollider(Entity * entity, glm::vec2 const & center, float diameter);

		void collide(SquareCollider &collider) override;

		void collide(SphereCollider &collider) override;

		float getDiameter() const;
	};
}

#endif //INC_2DENGINE_SPHERECOLLIDER_HPP
