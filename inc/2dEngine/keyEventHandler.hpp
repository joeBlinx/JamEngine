//
// Created by stiven on 18-01-20.
//

#ifndef ALLPROJECT_KEYEVENTHANDLER_HPP
#define ALLPROJECT_KEYEVENTHANDLER_HPP

#include <string>
#include <functional>
#include <map>
#include <2dEngine/keyHandler.hpp>

namespace JamEngine {
	struct KeyEventHandler {

		using mapFunction = std::map<std::string, std::vector<std::function<void()>>>;
		using eventFunction = std::function <void()>;
	private:
		KeyHandler keyHandler;
		mapFunction functionPressed;
		mapFunction functionReleased;

		static KeyEventHandler eventHandler;
		KeyEventHandler() = default;

		void executeFunction(int key, mapFunction &map);
	public:
		static void init(std::string && configFile);
		static void addKeyEventPressed(std::string &&key, eventFunction function);

		static void executePressedFunction(int key);
		static void addKeyEventReleased(std::string &&key, eventFunction function);

		static void executeReleasedFunction(int key);
	};

}
#endif //ALLPROJECT_KEYEVENTHANDLER_HPP
