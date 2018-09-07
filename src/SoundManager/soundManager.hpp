//
// Created by capi1500 on 10/07/18.
//

#ifndef COOPSHOOTER_SOUNDMANAGER_HPP
#define COOPSHOOTER_SOUNDMANAGER_HPP

#include <vector>
#include <src/Sound/sound.hpp>
#include <map>

class Game;

class SoundManager{
	private:
		Game& game;
		std::map<std::string, Sound*> sounds;
		std::map<std::string, std::string> paths;
	public:
		std::map<std::string, Sound*>& getSounds();
		std::map<std::string, std::string>& getPaths();
		
		void addSound(std::string name, std::string path);
		
		void playSound(std::string name);
		void pauseSound(std::string name);
		void clear();
		
		SoundManager(Game& gameRef);
};

#endif //COOPSHOOTER_SOUNDMANAGER_HPP
