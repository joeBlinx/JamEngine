//
// Created by Stiven on 29-Mar-18.
//
#ifdef WIN32
#include <windef.h>
#endif
#include "2dEngine/progShader/programManager.hpp"
#ifdef WIN32
#define M_PI 3.14159
#endif

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

	int ProgramManager::addProgram(std::string &&key, glish3::ProgramGL &&program) {
		return programManager.add(std::move(key), std::move(program));
	}

	//TODO : don't forget to change path for release
	void ProgramManager::init() {
		std::string path = "../shader/basic/";
        initDefaultProg(path);

		initDebugProg(path);


		initCommonUni();
	}

	void ProgramManager::initDebugProg(const std::string &path) {
		glish3::Shader vertex =
				glish3::Shader::createShaderFromFile(GL_VERTEX_SHADER, (path + "vertDebug.glsl").c_str());
		glish3::Shader fragment =
				glish3::Shader::createShaderFromFile(GL_FRAGMENT_SHADER, (path + "fragDebug.glsl").c_str());
		glish3::ProgramGL debugProg{
				vertex, fragment
		};
		programManager.addProgram("debug", std::move(debugProg));
	}

	void ProgramManager::initDefaultProg(const std::string &path) {
		glish3::Shader vertex =
				glish3::Shader::createShaderFromFile(GL_VERTEX_SHADER, (path + "vert.glsl").c_str());
		glish3::Shader fragment =
				glish3::Shader::createShaderFromFile(GL_FRAGMENT_SHADER, (path + "frag.glsl").c_str());
		glish3::ProgramGL defaultProg{
				vertex, fragment
		};
//
		programManager.addProgram("default", std::move(defaultProg));
    }

    void ProgramManager::quit() {
		programManager.clear();

	}

	void ProgramManager::use(int id) {
		if(id != programManager.lastProg) {
			programManager[id].use();
			programManager.lastProg = id;
		}
	}

	void ProgramManager::initCommonUni() {

	}
}