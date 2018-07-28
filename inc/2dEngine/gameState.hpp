//
// Created by stiven on 18-02-27.
//

#ifndef INC_2DENGINE_GAMESTATE_HPP
#define INC_2DENGINE_GAMESTATE_HPP

#include <functional>
#include <2dEngine/input/InputEventHandler.hpp>
#include <SDL2/SDL.h>

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

		static void loop(Window &window);
		static void gameOver();
		static float deltaTime();
		static void enableDebug();
		static int windowWidth();
		static int windowHeight();

		void sendAxis(axis axis, SDL_GameController *controller);

		void mouseInput(Window &window);
	};




}



#endif //INC_2DENGINE_GAMESTATE_HPP
