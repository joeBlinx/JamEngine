//
// Created by stiven on 18-02-27.
//

#ifndef INC_2DENGINE_ENTITY_HPP
#define INC_2DENGINE_ENTITY_HPP

#include <2dEngine/sprite.hpp>
#include <2dEngine/collider/sphereCollider.hpp>
#include <2dEngine/collider/squareCollider.hpp>

namespace JamEngine {
	class Entity {

		Sprite sprite;
		int priority = 0;
		int program = 0;
		int shape = 0;
		std::vector<SphereCollider> sphereColliders;
		std::vector<SquareCollider> squareColliders;
		glm::vec2 pos{0, 0};
		// Size of the entity
		glm::vec2 size{1, 1};
		// Position of the center of the entity
		std::string layer = "default";
		bool layerDefine = false;
		float angle = 0;

	protected:
		void setLayer(std::string && newLayer);

	public:
		Entity() = default;
		Entity(float posX, float posY, float sizeX, float sizeY);

		// Overridable gameplay methods
		Entity(glm::vec2 const & pos);
		virtual void update(float delta);

		void collide(Entity * other);
		// Display
		void setSpriteSheet(std::string const & name, float timeChange);
		virtual void display();
		void debug();
		//TODO: add debug
		// Getters
		const std::string &getLayer() const;
		const glm::vec2 &getPos() const;

		void move(float x, float y);
		void move(glm::vec2 const & deplacment);

		void addSphereCollider(glm::vec2 center, float radius,
		                       Collider::collideFunction function = Collider::collideFunction{});
		void addSquareCollider(glm::vec2 upperLeftCorner, glm::vec2 size,
		                       Collider::collideFunction function = Collider::collideFunction{}
		);
		void setPriority(int newPriority);

		int getPriority() const;

		virtual ~Entity() = 0;


	};
}
#endif //INC_2DENGINE_ENTITY_HPP
