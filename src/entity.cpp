//
// Created by stiven on 18-02-27.
//

#include <iostream>
#include <2dEngine/spriteSheetManager.hpp>
#include "entity.hpp"

namespace JamEngine{

	Entity::Entity(float posX, float posY, float sizeX, float sizeY){
		pos = glm::vec2(posX, posY);
		size = glm::vec2(sizeX, sizeY);
		graphicsSize = size;
	}

	void Entity::collide([[maybe_unused]]Entity &other) {

	}

	void Entity::setSpriteSheet(std::string const &name, float timeChange) {
		sprite = Sprite{SpriteSheetManager::get(name), timeChange};
	}

	void Entity::display(float delta) {
		auto info = sprite.update(delta);
		ShapeManager::getShape().bind();
		ProgramManager::use(info.orig, info.size, getGraphicsSize(), pos, angle);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	const std::string &Entity::getLayer() const {
		return layer;
	}

	void Entity::setPriority(int newPriority) {

		static bool alreadyDefine = false;
		if(alreadyDefine){
			std::cerr << "priority is already define" << std::endl;
		}
		priority = newPriority;

	}

	int Entity::getPriority() const {
		return priority;
	}

	Entity::Entity(glm::vec2 const &pos):pos(pos) {
	}

	void Entity::displayDebug(float delta) {

	}

	const glm::vec2 &Entity::getPos() const {
		return pos;
	}
}