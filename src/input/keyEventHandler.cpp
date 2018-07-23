//
// Created by stiven on 18-01-20.
//

#include "2dEngine/input/keyEventHandler.hpp"
namespace JamEngine {
	KeyEventHandler KeyEventHandler::eventHandler;


	template <class T, class U>
	void addKey(std::map<U, std::vector<T>> & map, U &&key, T &function){
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

	void KeyEventHandler::addAxisFunction(axis key, KeyEventHandler::axisFunction function) {
		addKey(eventHandler.functionAxis, std::move(key), function);
	}

	void  KeyEventHandler::executeAxisFunction(axis key, float delta) {
		for (auto& function : eventHandler.functionAxis[key]){
			function(delta);
		}
	}
}