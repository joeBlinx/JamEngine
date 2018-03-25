//
// Created by stiven on 18-03-09.
//

#ifndef INC_2DENGINE_SHAPE_HPP
#define INC_2DENGINE_SHAPE_HPP

#include <glish/Vao.hpp>

namespace JamEngine {
	class Shape {
		glish::Vao<2> vao;

		Shape(Shape const &) = delete;
		Shape&operator=(Shape const &) = delete;
	public:
		Shape(Shape &&) = default;
		Shape&operator=(Shape &&) = default;

		void bind() const;

		void setShape(std::vector<glm::vec2> const &vertices);

		void setUv(const std::vector<glm::vec2> &uvs);

		void setIndices(const std::vector<int> &indices);

	};
}
#endif //INC_2DENGINE_SHAPE_HPP
