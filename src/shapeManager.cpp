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
	std::vector<glm::vec2> debugSquare{
			{-1, -1},
			{-1, 1},
			{1, 1},
			{1, -1},
			{-1, -1}
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

		Shape debug;
		debug.setShape(debugSquare);
		addShape("debug", std::move(debug));
	}

	ShapeManager::~ShapeManager() {

	}

	int ShapeManager::get(std::string &&key) {
		return shapeManager.keys[std::move(key)];
	}


	int ShapeManager::addShape(std::string &&key, Shape &&shape) {
		return shapeManager.add(std::move(key), std::move(shape));
	}

	void ShapeManager::quit() {
		shapeManager.ids.clear();
	}

	void ShapeManager::use(int id) {
		if(id != shapeManager.lastId) {
			shapeManager[id].bind();
			shapeManager.lastId = id;
		}
	}
}