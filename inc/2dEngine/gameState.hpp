//
// Created by stiven on 18-02-27.
//

#ifndef INC_2DENGINE_GAMESTATE_HPP
#define INC_2DENGINE_GAMESTATE_HPP

#include <functional>
#include <2dEngine/input/InputEventHandler.hpp>
#include <SDL2/SDL.h>
#include <glish3/gl_glew.hpp>
#include <glish3/glfunction.hpp>
#include <2dEngine.h>

namespace JamEngine {
	struct Window;
	class GameState {

		static GameState gameState;
		bool endGame = false;
		float delta = 0.017f;
		bool debugMode = false;
		int const *  width = nullptr;
		int const *  height = nullptr;


		GameState(GameState&&) = delete;
		GameState(GameState const &) = delete;
		GameState&operator=(GameState&&) = delete;
		GameState&operator=(GameState const &) = delete;

		void input(Window &window);
		void axisInput(Window &window);
		void update();
		void debug();
		void display();
	public:
		GameState() = default;

		template<class ...Ts>
		static void loop(Window &window, Ts &&... update);
		static void gameOver();
		static float deltaTime();
		static void enableDebug();
		static int windowWidth();
		static int windowHeight();

		void sendAxis(axis axis, SDL_GameController *controller);

		void mouseInput(Window &window);
	};

	template<class ...Ts>
	void GameState::loop(Window &window, Ts &&... update) {
		gameState.width = &(window.getSettings().width);
		gameState.height = &(window.getSettings().height);
		while(!gameState.endGame) {
			glishClear(GL_COLOR_BUFFER_BIT);
			int start = SDL_GetTicks();
			int end;

			EventManager::execute(gameState.delta);
			gameState.input(window);

			gameState.update();
			(update.update(), ...);

			gameState.display();
			(update.display(), ...);

			SDL_GL_SwapWindow(window);
			end = SDL_GetTicks();
			int sub = end - start;
			if (sub < gameState.delta*1000) {
				SDL_Delay(gameState.delta*1000- sub);
			}
		}
	}

}



#endif //INC_2DENGINE_GAMESTATE_HPP
