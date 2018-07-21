//
// Created by Stiven on 01-Apr-18.
//

#include "2dEngine/collider/collider.hpp"
#include <2dEngine/collider/sphereCollider.hpp>
#include <2dEngine/collider/squareCollider.hpp>
#include <iostream>
#include <algorithm>

namespace JamEngine{

	Collider::Collider(Entity *entity, glm::vec2 const &referencePoint) : owner(entity),
																		  reference(referencePoint){

	}

	void Collider::onCollideEvent(Collider::collideFunction function) {
		onCollide = std::move(function);
	}




	void Collider::operator()(Collider &collider) {
		if(onCollide) {
			onCollide(collider.owner);
		}
	}

	void collision(SquareCollider &square, SphereCollider &sphere) {
		collision(sphere, square);
	}

	void collision(SphereCollider &sphere, SquareCollider &square) {
		float squarex = square.getReference().x - square.getSize().x;
		float squarey = square.getReference().y - square.getSize().y;


		float DeltaX = sphere.getReference().x- std::max(squarex, std::min(sphere.getReference().x, squarex + square.getSize().x*2));
		float DeltaY = sphere.getReference().y - std::max(squarey, std::min(sphere.getReference().y, squarey + square.getSize().y*2));

		 if((DeltaX * DeltaX + DeltaY * DeltaY) < (sphere.getDiameter()	 * sphere.getDiameter())){
			Collider::callCollideFunction(sphere, square);
		 }
	}

	void Collider::move(glm::vec2 const &deplac) {
		reference+= deplac;
	}

	const glm::vec2 &Collider::getReference() const {
		return reference;
	}

	void Collider::callCollideFunction(Collider &collider, Collider& collider2) {
		collider2(collider);
		collider(collider2);
	}


}