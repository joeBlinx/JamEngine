//
// Created by stiven on 18-01-20.
//

#ifndef ALLPROJECT_KEYEVENTHANDLER_HPP
#define ALLPROJECT_KEYEVENTHANDLER_HPP

#include <string>
#include <functional>
#include <map>
#include <2dEngine/input/keyHandler.hpp>

namespace JamEngine {


	enum class axis{
		GAME_CONTROLLER_INVALID = -1,
		GAME_CONTROLLER_LEFTX,
		GAME_CONTROLLER_LEFTY,
		GAME_CONTROLLER_RIGHTX,
		GAME_CONTROLLER_RIGHTY,
		GAME_CONTROLLER_TRIGGER_LEFT,
		GAME_CONTROLLER_TRIGGER_RIGHT,
		GAME_CONTROLLER_AXIS_MAX
	};

	struct KeyEventHandler {

		using mapFunction = std::map<std::string, std::vector<std::function<void()>>>;
		using eventFunction = std::function <void()>;


		using axisFunction = std::function<void(float)>;
		using mapAxisFunction = std::map<axis,  std::vector<axisFunction>>;
	private:
		KeyHandler keyHandler;
		mapFunction functionPressed;
		mapFunction functionReleased;

		mapAxisFunction functionAxis;
		static KeyEventHandler eventHandler;
		KeyEventHandler() = default;

		void executeFunction(int key, mapFunction &map);
	public:
		static void init(std::string && configFile);
		static void addKeyEventPressed(std::string &&key, eventFunction function);

		static void executePressedFunction(int key);
		static void addKeyEventReleased(std::string &&key, eventFunction function);

		static void executeReleasedFunction(int key);

		static void addAxisFunction(axis key, axisFunction function);

		static void executeAxisFunction(axis key, float delta);
	};

}
#endif //ALLPROJECT_KEYEVENTHANDLER_HPP
