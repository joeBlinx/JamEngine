//
// Created by stiven on 18-03-02.
//

#ifndef INC_2DENGINE_SOUND_HPP
#define INC_2DENGINE_SOUND_HPP

#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>

namespace JamEngine {
	class Sound {

		std::map<std::string, Mix_Chunk *> sons;
		int chanelUsed = 0;
		static int volume ;
		static bool pause ;
		std::string folder;

		static Sound sound;
	public:
		Sound();
		static void init(std::string && initFile);
		static void play(std::string &&);
		static void pauseAll();
		static bool getPause();
		~Sound();

	};



}


#endif //INC_2DENGINE_SOUND_HPP
