//
// Created by stiven on 18-02-27.
//
#include <2dEngine/window.hpp>
#include <2dEngine/windowSettings.hpp>
#include <iostream>
#include <2dEngine/gameState.hpp>

using namespace JamEngine;

int main(){

	std::cout <<" coucou" << std::endl;
	JamEngine::windowSettings settings{"JamEngine",1366, 768};
	Window t{settings};
	gameState.loop(t);

}