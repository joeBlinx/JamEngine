//
// Created by Stiven on 29-Mar-18.
//

#ifndef INC_2DENGINE_PROGRAMMANAGER_HPP
#define INC_2DENGINE_PROGRAMMANAGER_HPP

#include <glish3/programGL.hpp>
#include <2dEngine/assetsList.h>
#include <glm/vec2.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>

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
				1.0f / width, 0.0f, 0.f,
				0.0f, 1.0f / height, 0.0f,
				0.0f, 0.0f, 1.0f
		);

		return mat;
	}
	class ProgramManager  : public AssetsList<glish3::ProgramGL>{
		static ProgramManager programManager;
		int lastProg = -1;
		static void initCommonUni();
	public:

		static void use(int id);
		static int get(std::string && key);
		static int addProgram(std::string &&key, glish3::ProgramGL &&program);

		static void init();
		static void quit();
		template <class T>
		static void update(glish3::ProgramGL & prog, std::string const & uni, T * data)
		{
			prog[uni] = data;
		}
		template <class T, class ...Ts>
				static void update(int i, std::string const & uni, T * data, Ts &&...  args){
			use(i);
			update(programManager[i], uni, data);
			if constexpr (sizeof...(Ts) > 0)
			{
				update(i, std::forward<Ts>(args)...);
			}

		}
		template <class ...Ts >
				static void updateAllProg(Ts && ...args){
					for(size_t i = 0; i < programManager.ids.size(); i++)
			{

				update(i, std::forward<Ts>(args)...);
			}
		}
		static void initDefaultProg(const std::string &path);

		static void initDebugProg(const std::string &path);
	};
}


#endif //INC_2DENGINE_PROGRAMMANAGER_HPP
