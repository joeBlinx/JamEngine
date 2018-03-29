//
// Created by Stiven on 29-Mar-18.
//

#include "2dEngine/progShader/programManager.hpp"
#define M_PI 3.14159

namespace JamEngine{
	ProgramManager ProgramManager::programManager;

	glm::mat3 transform(transformStorage const &store, float offsetX,
						float offsetY) { //use evocative name to help you navigate in your code
		float cos0 = std::cos(store.angle * (float) M_PI / 180);
		float sin0 = std::sin(store.angle * (float) M_PI / 180);


		glm::mat3 truc{store.scale.x * cos0, -store.scale.x * sin0, 0.0f,
					   store.scale.y * sin0, store.scale.y * cos0, 0.0f,
					   -offsetX * (store.scale.x * cos0 + store.scale.y * sin0) + store.tran.x,
					   -offsetY * (-store.scale.x * sin0 +
								   store.scale.y * cos0) +
					   store.tran.y, 1.0f
		};
		return truc;
	}

	int ProgramManager::get(std::string &&key) {
		return programManager.keys[std::move(key)];
	}

	glish::UniContainer &ProgramManager::get(int id) {
		return programManager.ids[id];
	}

	int ProgramManager::addProgram(std::string &&key, glish::UniContainer &&program) {
		return programManager.add(std::move(key), std::move(program));
	}

	void ProgramManager::init() {
		glish::UniContainer defaultProg{
			glish::shaderFile{GL_VERTEX_SHADER, "shader/basic/vert.glsl"},
			glish::shaderFile{GL_FRAGMENT_SHADER, "shader/basic/frag.glsl"}
		};
		defaultProg.add<glm::vec2>("orig");
		defaultProg.add<glm::vec2>("textureSize");
		defaultProg.add<glm::mat3>("transform");
		defaultProg.add<glm::mat3>("scale");
		defaultProg.add<int>("texture2D");

		programManager.addProgram("default", std::move(defaultProg));
	}
}