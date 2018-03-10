//
// Created by stiven on 18-03-03.
//

#ifndef TRANSFORMOULE_SHAPEMANAGER_HPP
#define TRANSFORMOULE_SHAPEMANAGER_HPP

#include <glish/Vao.hpp>

namespace JamEngine {
	class ShapeManager {
		glish::Vao<2>  *vao = nullptr;

		static ShapeManager shapeManager;
	public:

		ShapeManager();
		static const glish::Vao<2> & getShape();
		static void init();
		~ShapeManager();

	};
}


#endif //TRANSFORMOULE_SHAPEMANAGER_HPP
