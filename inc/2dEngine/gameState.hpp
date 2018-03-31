//
// Created by stiven on 18-02-27.
//

#ifndef INC_2DENGINE_GAMESTATE_HPP
#define INC_2DENGINE_GAMESTATE_HPP

namespace JamEngine {
	class GameState {

		static GameState gameState;
		bool endGame = false;
		float delta = 0.017f;

		GameState(GameState&&) = delete;
		GameState(GameState const &) = delete;
		GameState&operator=(GameState&&) = delete;
		GameState&operator=(GameState const &) = delete;

		void input();
		void update();

		void display();
	public:
		GameState() = default;
		static void loop(SDL_Window *window);
		static void gameOver();
		static float deltaTime();

	};

}



#endif //INC_2DENGINE_GAMESTATE_HPP
