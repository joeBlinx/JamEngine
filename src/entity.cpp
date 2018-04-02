//
// Created by stiven on 18-02-27.
//

#include <iostream>
#include <2dEngine/spriteSheetManager.hpp>
#include <2dEngine/shapeManager.hpp>
#include <2dEngine/progShader/programManager.hpp>
#include <2dEngine/gameState.hpp>
#include "entity.hpp"
#include "collider/squareCollider.hpp"
#include <2dEngine/collider/collider.hpp>

namespace JamEngine{

	Entity::Entity(float posX, float posY, float sizeX, float sizeY){
		pos = glm::vec2(posX, posY);
		size = glm::vec2(sizeX, sizeY);
	}


	void Entity::setSpriteSheet(std::string const &name, float timeChange) {
		sprite = Sprite(SpriteSheetManager::get(name), timeChange);
	}

	void Entity::display() {

		auto info = sprite.getInfoSprite();
		ShapeManager::use(0);
		transformStorage transformStorage1;
		transformStorage1.tran = pos;
		transformStorage1.scale = size;
		transformStorage1.angle = angle;
		ProgramManager::update(0, "transform", transform(transformStorage1),
										"scale", normalizedScreenSpace(GameState::windowWidth(), GameState::windowHeight()),
		"hasTexture", (bool)sprite);
		if(sprite){
			ProgramManager::update(0, "orig", info.orig,
											"textureSize", info.size);
		}

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}


	void Entity::debug() {
		transformStorage transformStorage1;
		transformStorage1.tran = pos;
		transformStorage1.scale = size;
		transformStorage1.angle = angle;
		ProgramManager::update(1, "scale", normalizedScreenSpace(GameState::windowWidth(), GameState::windowHeight()));

		ShapeManager::use(0);
		for(auto &sphereCollider : sphereColliders){
			transformStorage1.tran = sphereCollider.getReference();
			transformStorage1.scale = glm::vec2(sphereCollider.getDiameter());
			ProgramManager::update(1, "isSquare", false,
			                       "transform", transform(transformStorage1),
			                       "diameter", sphereCollider.getDiameter()
			);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		}
		//TODO: for square
		ShapeManager::use(1);
		for(auto &squareCollider : squareColliders){
			transformStorage1.tran = squareCollider.getReference();
			transformStorage1.scale = squareCollider.getSize();
			ProgramManager::update(1, "isSquare", true,
			                       "transform", transform(transformStorage1, -0.5f, -0.5f)
			);
			glDrawArrays(GL_LINE_STRIP, 0, 5);

		}


	}

	const std::string &Entity::getLayer() const {
		return layer;
	}

	void Entity::setPriority(int newPriority) {

		static bool alreadyDefine = false;
		if(alreadyDefine){
			std::cerr << "priority is already define" << std::endl;
			return;
		}
		priority = newPriority;

	}

	int Entity::getPriority() const {
		return priority;
	}


	Entity::Entity(glm::vec2 const &pos):pos(pos) {
	}

	const glm::vec2 &Entity::getPos() const {
		return pos;
	}

	void Entity::update(float delta) {
		if(sprite){
			sprite.update(delta);
		}
	}

	template <class T, class ... Args, class U = T>
	void forCollider(std::vector<T>& colliders, void (U::*function)(Args ...), Args && ... args){
		for(auto & collider : colliders){
			(collider.*function)(std::forward<Args>(args)...);
		}
	}

	void Entity::collide(Entity *other) {
		for (auto &otherCollider : other->sphereColliders){
			forCollider(sphereColliders, &SphereCollider::collide, otherCollider);
			forCollider(squareColliders, &SquareCollider::collide, otherCollider);
		}

		for (auto &otherCollider : other->squareColliders){
			forCollider(sphereColliders, &SphereCollider::collide, otherCollider);
			forCollider(squareColliders, &SquareCollider::collide, otherCollider);
		}
	}

	void Entity::move(float x, float y) {
		move(glm::vec2{x , y});
	}

	void Entity::move(glm::vec2 const &deplacment) {
		pos += deplacment;
		forCollider(sphereColliders, &Collider::move, deplacment);
		forCollider(squareColliders, &Collider::move, deplacment);
	}

	void Entity::addSphereCollider(glm::vec2 center, float radius, Collider::collideFunction function) {
		center.x += pos.x;
		center.y += pos.y;
		SphereCollider collider{this, center, radius};
		collider.onCollideEvent(std::move(function));
		sphereColliders.emplace_back(std::move(collider));
	}

	void Entity::addSquareCollider(glm::vec2 upperLeftCorner, glm::vec2 size, Collider::collideFunction function) {
		upperLeftCorner += pos - size/2.0f;
		SquareCollider collider(this, upperLeftCorner, size);
		collider.onCollideEvent(std::move(function));
		squareColliders.emplace_back(std::move(collider));
	}
}