//
// Created by stiven on 18-04-01.
//

#include "2dEngine/collider/squareCollider.hpp"

namespace JamEngine {
	SquareCollider::SquareCollider(JamEngine::Entity *ent, glm::vec2 upperLeftCorner, glm::vec2 size):
	Collider(ent, upperLeftCorner),
	size(size){

	}

	void SquareCollider::collide(SquareCollider &collider) {
		float x = getReference().x - size.x/2;
		float y = getReference().y - size.y/2;
		float colliderx = collider.getReference().x - collider.size.x/2;
		float collidery = collider.getReference().y - collider.size.y/2;

		if (x < colliderx + collider.size.x &&

		    x + size.x > colliderx &&

		    y < collidery + collider.size.y &&

		    size.y + y > collidery) {

			//callCollideFunction(collider);
		}

		if (abs(colliderx - x) < collider.size.x + size.x){
			if (abs(collidery - y) < collider.size.y + size.y){
				callCollideFunction(collider);

			}
		}

	}

	void SquareCollider::collide(SphereCollider &collider) {

	}

	const glm::vec2 &SquareCollider::getSize() const {
		return size;
	}
}
