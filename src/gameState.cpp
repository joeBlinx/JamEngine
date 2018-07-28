//
// Created by stiven on 18-02-27.
//

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <2dEngine/input/InputEventHandler.hpp>
#include <2dEngine/eventManager.hpp>
#include <2dEngine/window.hpp>
#include <2dEngine/windowSettings.hpp>
#include <2dEngine/scene.hpp>
#include <2dEngine/camera.hpp>
#include <2dEngine/progShader/programManager.hpp>
#include <utils/log.hpp>
#include "gameState.hpp"

namespace JamEngine {
	GameState GameState::gameState;

	void GameState::loop(Window &window) {
		gameState.width = &(window.getSettings().width);
		gameState.height = &(window.getSettings().height);
		while(!gameState.endGame) {
			glClear(GL_COLOR_BUFFER_BIT);
			int start = SDL_GetTicks();
			int end;

			EventManager::execute(gameState.delta);
			gameState.input(window);
			gameState.update();
			gameState.display();

			SDL_GL_SwapWindow(window);
			end = SDL_GetTicks();
			int sub = end - start;
			if (sub < gameState.delta*1000) {
				SDL_Delay(gameState.delta*1000- sub);
			}
		}
	}

	void GameState::input(Window &window) {
		SDL_Event ev;
		while(SDL_PollEvent(&ev)){
			switch(ev.type){
				case SDL_KEYDOWN:
					if(ev.key.keysym.sym == SDLK_ESCAPE){
						gameOver();
					}
					InputEventHandler::executePressedFunction(ev.key.keysym.sym);
					break;
				case SDL_KEYUP:
					InputEventHandler::executeReleasedFunction(ev.key.keysym.sym);
					break;
				case SDL_MOUSEBUTTONUP:
					InputEventHandler::executeReleasedFunction(ev.button.button);
					break;
				case SDL_MOUSEBUTTONDOWN:
					InputEventHandler::executePressedFunction(ev.button.button);
					break;
				case SDL_CONTROLLERBUTTONDOWN:
					if(window.hasController()) {
						InputEventHandler::executePressedFunction(ev.cbutton.button);
					}
					break;
				case SDL_CONTROLLERBUTTONUP:
					if(window.hasController()) {
						InputEventHandler::executeReleasedFunction(ev.cbutton.button);
					}
					break;
				case SDL_MOUSEWHEEL:
					if(ev.wheel.y > 0){
						InputEventHandler::executePressedFunction(JAMENGINE_WHEEL_UP);
					}else if (ev.wheel.y < 0){
						InputEventHandler::executePressedFunction(JAMENGINE_WHEEL_DOWN);
					}
					break;
				case SDL_QUIT:
					gameOver();
					break;

				default:break;
			}

		}
		if (window.hasController()) {
				axisInput(window);
		}
		mouseInput(window);

	}

	void GameState::update() {
		Scene::update(gameState.delta);

	}

	void GameState::display() {
		glm::mat4 cam;
		if(Camera::getCurrent()){
			cam = Camera::getCurrent()->getCamView();
		}
		ProgramManager::updateAllProg("camera", cam);
		for(auto &ent : Scene::getEntities()){
			ent->display();
		}
		if(debugMode){
			debug();
		}
	}

	void GameState::debug() {
		for(auto &ent : Scene::getEntities()){
			ent->debug();
		}
	}

	void GameState::gameOver() {
		gameState.endGame = true;
	}

	float GameState::deltaTime() {
		return gameState.delta;
	}

	void GameState::enableDebug() {
		gameState.debugMode = true;
	}

	int GameState::windowWidth() {
		return *gameState.width;
	}

	int GameState::windowHeight() {
		return *gameState.height;
	}

	void GameState::sendAxis(axis axis, SDL_GameController * controller){
		int value = SDL_GameControllerGetAxis(controller, static_cast<SDL_GameControllerAxis>(axis));
		float valuetoSend = value/32767.;

		InputEventHandler::executeAxisFunction(axis, valuetoSend);
	}
	void GameState::axisInput(Window &window) {
		SDL_GameController * controller = window.getController();
		sendAxis(axis::GAME_CONTROLLER_RIGHTY, controller);
		sendAxis(axis::GAME_CONTROLLER_RIGHTX, controller);
		sendAxis(axis::GAME_CONTROLLER_LEFTY, controller);
		sendAxis(axis::GAME_CONTROLLER_LEFTX, controller);
		sendAxis(axis::GAME_CONTROLLER_TRIGGER_LEFT, controller);
		sendAxis(axis::GAME_CONTROLLER_TRIGGER_RIGHT, controller);

	}

	void GameState::mouseInput(Window &window) {
		int x, y;
		float sendX, sendY;
		SDL_GetMouseState(&x, &y);
		sendX = (((float)x/window.getSettings().width) -0.5f) *2.0f;
		sendY = - (((float)y/window.getSettings().height) - 0.5f)*2.0f ;

		InputEventHandler::executeMouseFunction(sendX, sendY);
	}
}
