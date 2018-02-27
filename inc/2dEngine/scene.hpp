//
// Created by stiven on 18-02-27.
//

#ifndef INC_2DENGINE_SCENE_HPP
#define INC_2DENGINE_SCENE_HPP

#include <2dEngine/entity.hpp>
#include <vector>
namespace JamEngine {
	class Scene {
		std::vector<Entity * > entities;

		Scene(Scene&&) = delete;
		Scene(Scene const&) = delete;
		Scene&operator= (Scene&&) = delete;
		Scene&operator= (Scene const&) = delete;
	public:
		Scene() = default;
		void update();
		void checkCollision();
		void add(Entity * entity);


	};
	extern Scene scene;
}


#endif //INC_2DENGINE_SCENE_HPP
