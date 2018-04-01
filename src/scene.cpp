//
// Created by stiven on 18-02-27.
//

#include <fstream>
#include <iostream>
#include "scene.hpp"

//TODO : refacto and reorganise
namespace JamEngine {
	Scene scene;

	void Scene::init(std::string &&layerFile) {
		std::ifstream file{std::move(layerFile)};
		if(!file.is_open()){
			std::cerr << "file : " << layerFile << " not found";
			return;
		}
		std::string layer;
		while(file >> layer){
			layers.push_back(std::move(layer));
		}
	}

	void Scene::update(float delta) {
		checkCollision();
		for(auto & entity : entities){
			entity->update(delta);
		}
		destroyEntities();
		removeWithoutDestorying();
	}
	void Scene::checkCollision() {
		auto end = entities.end();
		for(auto it = entities.begin(); it != end ; it++){
			auto j = it;
			j++;
			for(j ; j != end ;j++ ){
				(*it)->collide(*j);
			}
		}
	}
	void Scene::add(Entity *entity) {
		size_t i ;
		for(i = 0; i  < layers.size(); i++){
			if(layers[i] == entity->getLayer()){
				break;
			}
		}
		entity->setPriority(i);
		entities.insert(entity);
	}
	std::multiset<Entity *, compare > const &Scene::getEntities() {
		return entities;
	}


	Scene::Scene() {
		layers.push_back("default");
	}
	Scene::~Scene() {

		for(auto & ent : entities){
				delete ent;
		}
	}
	void Scene::destroy(Entity *entity) {
		deadEntities.insert(entity);
	}
	void Scene::destroyEntities() {
		for(auto ent : deadEntities){
			auto it = entities.begin();
			for(;it != entities.end();it++ ){
				if(*it == ent){
					break;
				}
			}
			if(it!= entities.end()){
					delete ent;
					entities.erase(it);
			}
		}
		deadEntities.clear();
	}

	void Scene::remove(Entity *entity) {
		removeEntities.insert(entity);

	}

	void Scene::removeWithoutDestorying() {
		for(auto ent : removeEntities){
			auto it = entities.begin();
			for(;it != entities.end();it++ ){
				if(*it == ent){
					break;
				}
			}
			if(it!= entities.end()){
				entities.erase(it);
			}
		}
		removeEntities.clear();
	}

	void Scene::clear() {
		for(auto & ent : entities){
				remove(ent);

		}
	}
	void Scene::clearNoDelete() {
		entities.clear();
	}
}
