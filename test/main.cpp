//
// Created by stiven on 18-03-09.
//
#ifdef WIN32
#define SDL_MAIN_HANDLED
#ifdef NDEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
#endif
#include <2dEngine/window.hpp>
#include <2dEngine/windowSettings.hpp>
#include <2dEngine/gameState.hpp>
#include <2dEngine/progShader/programManager.hpp>
#include <2dEngine/shapeManager.hpp>
#include <2dEngine/entity.hpp>
#include <2dEngine/scene.hpp>
#include <2dEngine/spriteSheetManager.hpp>
#include <glm/glm.hpp>
#include <2dEngine/input/InputEventHandler.hpp>
#include <2dEngine/camera.hpp>
#include <2dEngine/ui/AbstractUI.hpp>
//#include <utils/log.hpp>

using namespace JamEngine;

//using namespace utils;
struct Foo:Entity{
	using Entity::Entity;
};

struct Sonic : Entity
{

	bool forward = false;
	float speed = 200.0f;

	Sonic(float posX, float posY, float sizeX, float sizeY):

	Entity(posX, posY, sizeX, sizeY)
	{
		setSpriteSheet("sonic", 2*GameState::deltaTime());
		GET_INPUTEVENTHANDLER("default").addInputEventReleased("forward", [this]
		{
			forward = false;
		});
		GET_INPUTEVENTHANDLER("default").addInputEventPressed("forward", [this]
		{
			forward = true;
		});
	}
	void update(float delta) override{
		Entity::update(delta);
		if(forward)
		{
			move(delta*speed, 0);
		}
	}
};
struct Test
{
	int prog;
	float * life;

	Test(float & life):life(&life)
	{
		glish3::Shader vertex =
				glish3::Shader::createShaderFromFile(GL_VERTEX_SHADER, "../shader/basic/testUiVert.glsl");
		glish3::Shader fragment =
				glish3::Shader::createShaderFromFile(GL_FRAGMENT_SHADER, "../shader/basic/testUIFrag.glsl");
		glish3::ProgramGL defaultProg{
				vertex, fragment
		};
//
		prog = ProgramManager::addProgram("test", std::move(defaultProg));
	}
	void update(){

	};
	void display(int w, int h)const
	{
		float a [2] ;
		a[0] = 0.5f;
		a[1] = 0.5f;
		ShapeManager::use(0);
		ProgramManager::use(prog);
		ProgramManager::update(prog, "size", a,
				"life", life);
		glishDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
};
int main(int, char **) {


	const float i1 = 50;
	windowSettings settings{"test", 1366, 768};
	Window window{settings};
	glish3::init("../log", "2dEngine Test");
	SpriteSheetManager::init("config.ini");
	GET_INPUTEVENTHANDLER("default").init("key.ini");
	Scene::init("layer.ini");


	float i2 = 0.5;
	Camera cam(glm::vec2(0, 0), -i2, i2, -i2, i2);
    auto camCurrent = Camera::addCamera(&cam);
	Camera::changeCamera(camCurrent);

	auto  a = new Sonic{50, 0, i1, i1};
	auto  c = new Foo{50, 0, i1, i1};


	c->setSpriteSheet("sonic", 2 * GameState::deltaTime());

	Test test(i2);
	EventManager::addEvent(500, [&i2](float duration)
	{
		i2 -= GameState::deltaTime();
		if(i2 < 0)
		{
			i2 = 1.0f;
		}
	});
	UI<Test> ui(settings.width, settings.height,
			test);


	Scene::add(a);
	//Scene::add(c);
//	GameState::enableDebug();
	GameState::loop(window, ui);

	return 0;
}