//
// Created by stiven on 18-03-09.
//
#include "shape.hpp"
namespace JamEngine{

	void Shape::bind() const{
		vao.bind();
	}

	void Shape::setShape(std::vector<glm::vec2> const &vertices) {
		vao.addVbo(0, vertices);
	}

	void Shape::setUv(const std::vector<glm::vec2> &uvs) {
		vao.addVbo(1, uvs);
	}

	void Shape::setIndices(const std::vector<int> &indices) {
		vao.addIndices(indices);
	}
}