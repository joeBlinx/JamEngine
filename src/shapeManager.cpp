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

	const glish::Vao<2> & ShapeManager::getShape() {
		return *shapeManager.vao;
	}

	void ShapeManager::init() {
		shapeManager.vao = new glish::Vao<2>;
		shapeManager.vao->addVbo(0, square);
		shapeManager.vao->addVbo(1, uv);
	}

	ShapeManager::~ShapeManager() {
		delete shapeManager.vao;
	}
}