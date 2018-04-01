//
// Created by Stiven on 01-Apr-18.
//

#include "2dEngine/collider/collider.hpp"
#include <2dEngine/collider/sphereCollider.hpp>
#include <iostream>

namespace JamEngine{

	Collider::Collider(Entity *entity, glm::vec2 const &referencePoint) : owner(entity),
																		  reference(referencePoint){

	}

	void Collider::onCollideEvent(Collider::collideFunction function) {
		onCollide = std::move(function);
	}




	void Collider::operator()(Collider *collider) {
		if(onCollide) {
			onCollide(collider->owner);
		}
	}

	void collide(SquareCollider &square, SphereCollider &sphere) {
		collide(sphere, square);
	}

	void collide(SphereCollider &sphere, SquareCollider &square) {

	}

	void Collider::move(glm::vec2 const &deplac) {
		reference+= deplac;
	}

	const glm::vec2 &Collider::getReference() const {
		return reference;
	}


}