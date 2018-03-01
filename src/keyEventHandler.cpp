//
// Created by stiven on 18-01-20.
//

#include "keyEventHandler.hpp"
namespace JamEngine {
	KeyEventHandler KeyEventHandler::eventHandler;

	void addKey(KeyEventHandler::mapFunction & map, std::string &&key, KeyEventHandler::eventFunction &function){
		auto &vecFunction = map[std::move(key)];
		vecFunction.push_back(function);
	}

	void KeyEventHandler::executeFunction(int key, KeyEventHandler::mapFunction & map){

		for(auto &[keyPressed, function] : map){
			auto &[value1, value2] = keyHandler[keyPressed];
			if(value1 == key || value2 == key){
				for(auto &f : function){
					f();
				}
				break;
			}
		}

	}
	void KeyEventHandler::addKeyEventPressed(std::string &&key, std::function<void()> function) {
		addKey(eventHandler.functionPressed, std::move(key), function);
	}

	void KeyEventHandler::init(std::string &&configFile) {
		eventHandler.keyHandler.mapKey(std::move(configFile));
	}

	void KeyEventHandler::executePressedFunction(int key) {
		eventHandler.executeFunction(key, eventHandler.functionPressed);

	}

	void KeyEventHandler::addKeyEventReleased(std::string &&key, KeyEventHandler::eventFunction function) {
		addKey(eventHandler.functionReleased, std::move(key), function);
	}

	void KeyEventHandler::executeReleasedFunction(int key) {
		eventHandler.executeFunction(key, eventHandler.functionReleased);
	}
}