//
// Created by darkblinx on 27/06/17.
//

#include <stdexcept>
#include <window.hpp>
#include <windowSettings.hpp>
#include <GL/glew.h>
#include <glish3/log/log.hpp>
#include <2dEngine/shapeManager.hpp>
#include <2dEngine/progShader/programManager.hpp>
#include <2dEngine/spriteSheetManager.hpp>
#include <2dEngine/log.hpp>

namespace JamEngine {
//	using namespace utils;
	Window::~Window() {
		ShapeManager::quit();
		ProgramManager::quit();
		SpriteSheetManager::quit();
		SDL_JoystickClose(m_joystick);
		SDL_GL_DeleteContext(m_context);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	Window::Window(windowSettings const & settings):settings(settings) {
		if (SDL_Init(SDL_INIT_EVERYTHING)) {
			printFatalError("error while initialize SDL2 " + std::string{SDL_GetError()});
			glish3::log.error("error while initialize SDL2 " + std::string{SDL_GetError()});

		}
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, settings.majorVersion);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, settings.minorVersion);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, settings.doubleBuffer);

		m_window = SDL_CreateWindow(settings.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, settings.width, settings.height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

		if(!m_window){
			std::string erreur {SDL_GetError()};
			SDL_Quit();
			printFatalError("error while initialize window "+erreur);
			glish3::log.error("error while initialize window "+erreur);
		}

		m_context = SDL_GL_CreateContext(m_window);
		glewExperimental = GL_TRUE;
		auto err = glewInit();
		if(err!= GLEW_OK){
			printFatalError(glewGetErrorString(err), "error while initialize glew");

		}
		glishClearColor(0.5, 0.5, 0.5, 1);
		glishEnable (GL_BLEND);
		glishBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		initJoystick();
		ShapeManager::init();
		ProgramManager::init();
	}

	SDL_Window *Window::getWindow() {
		return m_window;
	}

	const windowSettings &Window::getSettings() const {
		return settings;
	}

	void Window::initJoystick() {

		// Enumerate m_joysticksticks
		for (int i = 0; i < SDL_NumJoysticks(); ++i) {

			// Check to see if m_joystickstick supports SDL's game m_controller interface
			if (SDL_IsGameController(i)) {
				m_controller = SDL_GameControllerOpen(i);
				if (m_controller) {
//					print("Found a valid m_controller, named: \n",
//							  SDL_GameControllerName(m_controller), "\n");
					break;  // Break after first available m_controller
				} else {
//					printWarning("Could not open game m_controller \n", i,  SDL_GetError());
				}

				// Controller interface not supported, try to open as m_joystickstick
			} else {
//				printError("Joystick %i is not supported by the game m_controller interface", i);
				m_joystick = SDL_JoystickOpen(i);

				// Joystick is valid
				if (m_joystick) {
//					print(
//							  "Opened Joystick %i\n",
//							  "Name: %s\n",
//							  "Axes: %d\n",
//							  "Buttons: %d\n",
//							  "Balls: %d\n",
//							  i, SDL_JoystickName(m_joystick), SDL_JoystickNumAxes(m_joystick),
//							  SDL_JoystickNumButtons(m_joystick)<< SDL_JoystickNumBalls(m_joystick));


					// Joystick not valid
				} else {
//					printError("Could not open Joystick %i", i);
				}

				break;  // Break after first available m_joystickstick
			}
		}


	}

	bool Window::hasController() const {
		return (bool)m_controller;
	}

	SDL_GameController *Window::getController() const {
		return m_controller;
	}


}


//#include <utils/log.hpp>
