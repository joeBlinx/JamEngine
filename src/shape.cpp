//
// Created by stiven on 18-03-09.
//
#ifdef WIN32
#include <windef.h>
#endif
#include "shape.hpp"
namespace JamEngine{

	void Shape::bind() {
		vao.bind();
	}

	void Shape::setShape(const std::vector<float> &vertices) {
		vao.addVbo(glish3::Vbo{GL_ARRAY_BUFFER,
						 vertices.data(), vertices.size(),
						 glish3::vbo_settings{2, 0, 0, 0}});
	}

	void Shape::setUv(const std::vector<float> &uvs) {
		vao.addVbo(glish3::Vbo{GL_ARRAY_BUFFER,
							   uvs.data(), uvs.size(),
						glish3::vbo_settings{2, 1, 0, 0}});
	}

	void Shape::setIndices(const std::vector<int> &indices) {
//		vao.addIndices(indices);
	}

	void Shape::addVertex(glm::vec2 const &vertex) {
		vertices.push_back(vertex);
	}

	void Shape::addUv(glm::vec2 const &uv) {
		uvs.push_back(uv);
	}
}