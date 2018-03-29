//
// Created by Stiven on 29-Mar-18.
//

#ifndef INC_2DENGINE_PROGRAMMANAGER_HPP
#define INC_2DENGINE_PROGRAMMANAGER_HPP

#include <glish/utils/uniContainer.hpp>
#include <2dEngine/assetsList.h>

namespace JamEngine {
	struct transformStorage {
		glm::vec2 tran = glm::vec2(0.0f);
		glm::vec2 scale = glm::vec2(1.0f);
		float angle = 0.0f;
	};

	glm::mat3 transform(transformStorage const &store, float offsetX = 0,
						float offsetY = 0);
	template<typename T>
	glm::mat3 normalizedScreenSpace(const T width, const T height) {
		glm::mat3 mat(
				2.0f / width, 0.0f, 0.f,
				0.0f, -2.0f / height, 0.0f,
				-1.0f, 1.0f, 1.0f
		);

		return mat;
	}
	class ProgramManager  : public AssetsList<glish::UniContainer>{
		static ProgramManager programManager;

	public:
		static int get(std::string && key);
		static glish::UniContainer & get(int id);
		static int addProgram(std::string && key ,glish::UniContainer && program);

		static void init();
	};
}


#endif //INC_2DENGINE_PROGRAMMANAGER_HPP
