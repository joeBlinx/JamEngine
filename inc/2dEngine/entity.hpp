//
// Created by stiven on 18-02-27.
//

#ifndef INC_2DENGINE_ENTITY_HPP
#define INC_2DENGINE_ENTITY_HPP

namespace JamEngine {
	class Entity {

	public:
		virtual void collide(Entity &other) = 0;
		virtual void update() = 0;
	};
}

#endif //INC_2DENGINE_ENTITY_HPP
