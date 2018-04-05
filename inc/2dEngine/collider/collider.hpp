//
// Created by Stiven on 01-Apr-18.
//

#ifndef INC_2DENGINE_COLLIDER_HPP
#define INC_2DENGINE_COLLIDER_HPP

#include <functional>
#include <glm/vec2.hpp>
namespace JamEngine {
	class Entity;
	class SquareCollider;
	class SphereCollider;
	class Collider {
	public:
		using collideFunction = std::function<void(Entity *)>;
	private:

		collideFunction onCollide;
		Entity * owner = nullptr;
		glm::vec2 reference;

	protected:

		static void callCollideFunction(Collider & collider, Collider& collider2);
	public:

		const glm::vec2 &getReference() const;
		Collider(Entity *entity, glm::vec2 const &referencePoint);
		void onCollideEvent(collideFunction function);
		virtual void collide(SquareCollider & collider) = 0;
		virtual void collide(SphereCollider & collider) = 0;

		void move(glm::vec2 const & deplac);


		void operator()(Collider &collider);

		friend void collision(SquareCollider &square, SphereCollider &sphere);
		friend void collision(SphereCollider &sphere, SquareCollider &square);
	};
}

#endif //INC_2DENGINE_COLLIDER_HPP
