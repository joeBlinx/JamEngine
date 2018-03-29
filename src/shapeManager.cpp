//
// Created by stiven on 18-03-03.
//

#include "2dEngine/shapeManager.hpp"
namespace JamEngine{

	std::vector<glm::vec2> square{
			{-1, 1},
			{1, 1},
			{-1, -1},
			{1, -1}
	};
	std::vector<glm::vec2> uv{
			{0, 0},
			{1, 0},
			{0, 1},
			{1, 1}
	};

	ShapeManager ShapeManager::shapeManager;

	ShapeManager::ShapeManager() {

	}


	void ShapeManager::init() {
		Shape a;
		a.setShape(square);
		a.setUv(uv);
		addShape("default", std::move(a));
	}

	ShapeManager::~ShapeManager() {

	}

	int ShapeManager::get(std::string &&key) {
		return shapeManager.keys[std::move(key)];
	}

	Shape const &ShapeManager::get(int id) {
		return shapeManager.ids[id];
	}

	int ShapeManager::addShape(std::string &&key, Shape &&shape) {
		return shapeManager.add(std::move(key), std::move(shape));
	}
}