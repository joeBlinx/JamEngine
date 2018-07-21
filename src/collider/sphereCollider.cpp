//
// Created by Stiven on 01-Apr-18.
//

#include <glm/glm.hpp>
#include "2dEngine/collider/sphereCollider.hpp"
#include <glm/vec2.hpp>
#include <iostream>

namespace JamEngine {
	SphereCollider::SphereCollider(Entity *entity,
											  const glm::vec2 &center,
											  float diameter) : Collider(entity, center),
									diameter(diameter){

	}

	void SphereCollider::collide(SquareCollider &collider) {
			collision(*this, collider);
	}

	float SphereCollider::getDiameter() const {
		return diameter;
	}

	// need Test
	void SphereCollider::collide(SphereCollider &collider) {
			float distance = glm::distance(getReference(), collider.getReference());
			if(distance < diameter + collider.diameter){
				callCollideFunction(collider, *this);
			}
	}

	float SphereCollider::getRadius() const {
		return diameter/2.0f;
	}
}