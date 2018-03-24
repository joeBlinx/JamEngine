//
// Created by stiven on 18-02-27.
//

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <2dEngine/keyEventHandler.hpp>
#include <2dEngine/eventManager.hpp>
#include "gameState.hpp"
#include "scene.hpp"
namespace JamEngine {
	GameState GameState::gameState;

	void GameState::loop(SDL_Window *window) {
		while(!gameState.endGame) {

			int start = SDL_GetTicks();
			int end;
			glClear(GL_COLOR_BUFFER_BIT);
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
		scene.update();

	}

	void GameState::display() {

	}

	void GameState::gameOver() {
		gameState.endGame = true;
	}
}
