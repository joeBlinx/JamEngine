//
// Created by stiven on 18-01-20.
//

#include "2dEngine/input/keyEventHandler.hpp"
namespace JamEngine {
	InputEventHandler InputEventHandler::eventHandler;


	template <class T, class U>
	void addKey(std::map<U, std::vector<T>> & map, U &&key, T &function){
		auto &vecFunction = map[std::move(key)];
		vecFunction.push_back(function);
	}

	void InputEventHandler::executeFunction(int key, InputEventHandler::mapFunction & map){

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
	void InputEventHandler::addKeyEventPressed(std::string &&key, std::function<void()> function) {
		addKey(eventHandler.functionPressed, std::move(key), function);
	}

	void InputEventHandler::init(std::string &&configFile) {
		eventHandler.keyHandler.mapKey(std::move(configFile));
	}

	void InputEventHandler::executePressedFunction(int key) {
		eventHandler.executeFunction(key, eventHandler.functionPressed);

	}

	void InputEventHandler::addKeyEventReleased(std::string &&key, InputEventHandler::eventFunction function) {
		addKey(eventHandler.functionReleased, std::move(key), function);
	}

	void InputEventHandler::executeReleasedFunction(int key) {
		eventHandler.executeFunction(key, eventHandler.functionReleased);
	}

	void InputEventHandler::addAxisFunction(axis key, InputEventHandler::axisFunction function) {
		addKey(eventHandler.functionAxis, std::move(key), function);
	}

	void  InputEventHandler::executeAxisFunction(axis key, float delta) {
		for (auto& function : eventHandler.functionAxis[key]){
			function(delta);
		}
	}
}