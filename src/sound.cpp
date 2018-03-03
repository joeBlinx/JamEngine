//
// Created by stiven on 18-03-02.
//

#include "sound.hpp"
#include <exception>
#include <stdexcept>
#include <iostream>
#include <fstream>

namespace JamEngine{
	//
// Created by unnom on 20/03/16.
//

	Sound Sound::sound;

	bool Sound::pause = false;
	int Sound::volume = MIX_MAX_VOLUME/2;

	Sound::Sound(){
		if(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024)){
			throw std::runtime_error(Mix_GetError());
		}




		for(auto i : sons) {
			if(!i.second){
				throw std::runtime_error(Mix_GetError());
			}
		}


	}


	Sound::~Sound(){
		Mix_HaltChannel(-1);
		for(auto i : sons) {
			Mix_FreeChunk(i.second);
		}
		Mix_CloseAudio();

	}
	void Sound::play(std::string &&son) {
		int i;
		for (i = 0; i<sound.chanelUsed;i++) { //just right
			if (Mix_Playing(i))
				continue;
			break;
		}
		if(i==sound.chanelUsed){
			Mix_AllocateChannels(i+2);
			sound.chanelUsed++;
		}


		Mix_Volume(i, volume);
		Mix_PlayChannel(i,sound.sons[std::move(son)], 0);


	}


	void Sound::pauseAll() {
		pause = !pause;
		if(pause) {
			volume = 0;
		}else{
			volume = MIX_MAX_VOLUME/2;
		}

	}

	bool Sound::getPause() {
		return pause;
	}

	void Sound::init(std::string &&initFile) {

		std::ifstream file{initFile};
		if(!file.is_open()){
			std::cerr<< " file : "<< initFile << " not found" << std::endl;
			return;
		}

		file >> sound.folder;
		std::string key, path;

		while(file >> key >> path){
			sound.sons.emplace(std::pair{key, Mix_LoadWAV((sound.folder +"/"+ path).c_str())});
		}


		for(auto i : sound.sons) {
			if(!i.second){
				throw std::runtime_error(Mix_GetError());
			}
		}

	}

}