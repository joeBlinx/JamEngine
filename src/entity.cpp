//
// Created by stiven on 18-02-27.
//

#include <iostream>
#include <2dEngine/spriteSheetManager.hpp>
#include <2dEngine/shapeManager.hpp>
#include <2dEngine/progShader/programManager.hpp>
#include <2dEngine/gameState.hpp>
#include "entity.hpp"

namespace JamEngine{

	Entity::Entity(float posX, float posY, float sizeX, float sizeY){
		pos = glm::vec2(posX, posY);
		size = glm::vec2(sizeX, sizeY);
	}

	void Entity::collide([[maybe_unused]]Entity &other) {

	}

	void Entity::setSpriteSheet(std::string const &name, float timeChange) {
		sprite = Sprite(SpriteSheetManager::get(name), timeChange);
	}

	void Entity::display(float delta) {

		auto info = sprite.getInfoSprite();
		ShapeManager::use(0);
		ProgramManager::use(0);
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
		ShapeManager::use(1);
		ProgramManager::use(0);
		transformStorage transformStorage1;
		transformStorage1.tran = pos;
		transformStorage1.scale = size;
		transformStorage1.angle = angle;
		ProgramManager::update(0, "transform", transform(transformStorage1),
									  "scale", normalizedScreenSpace(GameState::windowWidth(), GameState::windowHeight()),
									  "hasTexture", false);
		glDrawArrays(GL_LINE_STRIP, 0, 5);

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
}