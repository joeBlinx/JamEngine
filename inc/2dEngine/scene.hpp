//
// Created by stiven on 18-02-27.
//

#ifndef INC_2DENGINE_SCENE_HPP
#define INC_2DENGINE_SCENE_HPP

#include <2dEngine/entity.hpp>
#include <vector>
#include <set>

namespace JamEngine {
	struct compare{

		bool operator()(Entity *a, Entity * b){
			return a->getPriority() < b->getPriority();
		}
	};
	class Scene {
		std::multiset<Entity *, compare > entities;


		std::set<Entity *> deadEntities;
		std::set<Entity *> removeEntities;

		std::vector<std::string> layers;
		Scene(Scene&&) = delete;
		Scene(Scene const&) = delete;
		Scene&operator= (Scene&&) = delete;
		Scene&operator= (Scene const&) = delete;

		void destroyEntities();
		void removeWithoutDestorying();
	public:
		Scene();
		void init(std::string && layerFile);
		void update(float delta);
		void checkCollision();
		void add(Entity * entity);
		std::multiset<Entity *, compare > const & getEntities();
		void destroy(Entity *entity);
		void remove(Entity *entity);
		void clear();
		~Scene();

		void clearNoDelete();
	};
	extern Scene scene;
}

#endif //INC_2DENGINE_SCENE_HPP
