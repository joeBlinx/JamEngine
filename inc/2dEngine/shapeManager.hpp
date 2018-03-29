//
// Created by stiven on 18-03-03.
//

#ifndef TRANSFORMOULE_SHAPEMANAGER_HPP
#define TRANSFORMOULE_SHAPEMANAGER_HPP

#include <glish/Vao.hpp>
#include <2dEngine/shape.hpp>
#include <2dEngine/assetsList.h>


namespace JamEngine {

	class ShapeManager : public AssetsList<Shape> {


		static ShapeManager shapeManager;
		ShapeManager();
	public:

		static int get(std::string&& key);
		static Shape const & get(int id);
		static int addShape(std::string &&key, Shape &&shape);

		static void init();
		~ShapeManager();

	};
}


#endif //TRANSFORMOULE_SHAPEMANAGER_HPP
