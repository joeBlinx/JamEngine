//
// Created by stiven on 18-02-27.
//

#ifndef INC_2DENGINE_ENTITY_HPP
#define INC_2DENGINE_ENTITY_HPP

#include <2dEngine/sprite.hpp>

namespace JamEngine {
	class Entity {
		Sprite sprite;
		int priority = 0;


	protected:
		// Position of the center of the entity
		std::string layer = "default";
		glm::vec2 pos{0, 0};
		// Size of the entity
		glm::vec2 size{1, 1};
		float angle = 0;

	public:
		Entity() = default;
		Entity(float posX, float posY, float sizeX, float sizeY);

		// Overridable gameplay methods
		Entity(glm::vec2 const & pos);
		virtual void collide(Entity &other) ;
		virtual void update() ;

		// Display
		void setSpriteSheet(std::string const & name, float timeChange);
		virtual void display(float delta);
		//TODO: add debug
		// Getters
		const std::string &getLayer() const;
		const glm::vec2 &getPos() const;

		void setPriority(int newPriority);

		int getPriority() const;

		virtual ~Entity() = default;


	};
}
#endif //INC_2DENGINE_ENTITY_HPP
