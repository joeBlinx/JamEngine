//
// Created by stiven on 18-02-27.
//
#include <2dEngine/window.hpp>
#include <2dEngine/windowSettings.hpp>
#include <iostream>
#include <2dEngine/gameState.hpp>
#include <2dEngine/keyEventHandler.hpp>

using namespace JamEngine;

int main(){

	JamEngine::windowSettings settings{"JamEngine",1366, 768};
	JamEngine::KeyEventHandler::init("config.ini");
	JamEngine::KeyEventHandler::addKeyEventPressed("jump", []{std::cout << "coucou\n" ;});
	JamEngine::KeyEventHandler::addKeyEventReleased("move", []{std::cout << "move\n" ;});
	Window t{settings};
	gameState.loop(t);

}