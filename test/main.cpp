//
// Created by stiven on 18-02-27.
//
#include <2dEngine/window.hpp>
#include <2dEngine/windowSettings.hpp>
#include <iostream>
#include <2dEngine/gameState.hpp>
#include <2dEngine/keyEventHandler.hpp>
#include <2dEngine/entity.hpp>
#include <2dEngine/scene.hpp>
#include <2dEngine/eventManager.hpp>
#include <2dEngine/spriteSheetManager.hpp>
#include <SDL2/SDL_mixer.h>
#include <2dEngine/sound.hpp>

using namespace JamEngine;

struct Test : JamEngine::Entity{
	int g = 0;
	void collide([[maybe_unused]] Entity &other) override {
		//std::cout << "i 'v been hit by " << g << std::endl;
	}

	void update() override {
		static int i = 0;
		if (!(i++%100)){
			//std::cout << "an other test\n";
		}
	}
};
int main(){

	Test t;t.g=5;
	Test g;g.g=3;
	JamEngine::scene.add(&t);
	JamEngine::scene.add(&g);
	JamEngine::windowSettings settings{"JamEngine",1366, 768};
	JamEngine::KeyEventHandler::init("config.ini");
	JamEngine::KeyEventHandler::addKeyEventPressed("jump", []{std::cout << "coucou\n" ;});
	JamEngine::KeyEventHandler::addKeyEventReleased("move", []{std::cout << "move\n" ;});
	/*EventManager::addEvent(3, [](float delta){
		std::cout << "Hey, i'm the first event of this awesome eventManager, I've been here for " << delta << " second\n";
	});*/
	SpriteSheetManager::init("texture.ini");
	SpriteSheetManager::get("sonic");
	Window d{settings};
	Sound::init("sound.ini");

	JamEngine::KeyEventHandler::addKeyEventReleased("son", []{Sound::play("sound");});
	GameState::loop(d);
	return 0;
}