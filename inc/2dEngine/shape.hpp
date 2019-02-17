//
// Created by stiven on 18-03-09.
//

#ifndef INC_2DENGINE_SHAPE_HPP
#define INC_2DENGINE_SHAPE_HPP

#include <glish3/Vao.hpp>
#include <vector>
#include <glm/glm.hpp>
namespace JamEngine {
	class Shape {
		glish3::Vao vao;

		std::vector<glm::vec2> vertices;
		std::vector<glm::vec2> uvs;

		Shape(Shape const &) = delete;
		Shape&operator=(Shape const &) = delete;
	public:
		Shape() = default;
		Shape(Shape &&) = default;
		Shape&operator=(Shape &&) = default;

		void bind() ;

		void setShape(const std::vector<float> &vertices);

		void setUv(const std::vector<float> &uvs);

		void setIndices(const std::vector<int> &indices);

		void addVertex(glm::vec2 const & vertex);

		void addUv(glm::vec2 const & uv);

	};
}
#endif //INC_2DENGINE_SHAPE_HPP
