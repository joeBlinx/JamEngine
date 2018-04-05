//
// Created by stiven on 18-02-27.
//

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <2dEngine/keyEventHandler.hpp>
#include <2dEngine/eventManager.hpp>
#include <2dEngine/window.hpp>
#include <2dEngine/windowSettings.hpp>
#include <2dEngine/scene.hpp>
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
			gameState.input();
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

	void GameState::input() {
		SDL_Event ev;
		while(SDL_PollEvent(&ev)){
			switch(ev.type){
				case SDL_KEYDOWN:
					if(ev.key.keysym.sym == SDLK_ESCAPE){
						gameOver();
					}
					KeyEventHandler::executePressedFunction(ev.key.keysym.sym);
					break;
				case SDL_KEYUP:
					KeyEventHandler::executeReleasedFunction(ev.key.keysym.sym);
					break;
				case SDL_QUIT:
					gameOver();
					break;

				default:break;
			}
		}

	}

	void GameState::update() {
		Scene::update(gameState.delta);

	}

	void GameState::display() {
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
}
