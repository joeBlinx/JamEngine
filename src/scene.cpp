//
// Created by stiven on 18-02-27.
//

#include "scene.hpp"

namespace JamEngine {
	Scene scene;

	void Scene::update() {
		checkCollision();
		for(auto & entity : entities){
			entity->update();
		}
	}

	void Scene::checkCollision() {

		for(int i = 0 ; i < (int)(entities.size()-1) ; i++) {
			for (int j = i + 1; j < entities.size(); j++) {
				entities[i]->collide(*entities[j]);
			}
		}
	}

	void Scene::add(Entity *entity) {
		entities.push_back(entity);
	}
}
