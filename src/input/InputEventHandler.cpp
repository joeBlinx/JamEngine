//
// Created by stiven on 18-01-20.
//

#include "2dEngine/input/InputEventHandler.hpp"
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
	void InputEventHandler::init(std::string &&configFile) {
		keyHandler.mapKey(std::move(configFile));
	}

	void InputEventHandler::addInputEventPressed(std::string &&key, std::function<void()> function) {
		addKey(functionPressed, std::move(key), function);
	}

	void InputEventHandler::addInputEventReleased(std::string &&key, InputEventHandler::eventFunction function) {
		addKey(functionReleased, std::move(key), function);
	}

	void InputEventHandler::addAxisFunction(axis key, InputEventHandler::axisFunction function) {
		addKey(functionAxis, std::move(key), function);
	}

	void InputEventHandler::addMouseFunction(mouseFunction function) {
		functionMouse.push_back(function);
	}

	void InputEventHandler::executePressedFunction(int key) {
		executeFunction(key, functionPressed);

	}

	void InputEventHandler::executeReleasedFunction(int key) {
		executeFunction(key, functionReleased);
	}
	void  InputEventHandler::executeAxisFunction(axis key, float delta) {
		for (auto& function : functionAxis[key]){
			function(delta);
		}
	}

	void InputEventHandler::executeMouseFunction(float x, float y) {
		for (auto& function : functionMouse){
			function(x, y);
		}

	}
	InputEventHandler &InputEventHandler::getHandler(std::string &&name) {
		//return eventHandlers[std::move(name)];
		return eventHandler;
	}
}