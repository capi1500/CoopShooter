//
// Created by capi1500 on 10/07/18.
//

#include "soundManager.hpp"
#include <src/Sound/sound.hpp>

std::map<std::string, Sound*>& SoundManager::getSounds(){
	return sounds;
}

std::map<std::string, std::string>& SoundManager::getPaths(){
	return paths;
}

void SoundManager::addSound(std::string name, std::string path){
	sounds[name] = new Sound(path);
	paths[name] = path;
}

void SoundManager::playSound(std::string name){
	sounds[name]->play();
}

void SoundManager::pauseSound(std::string name){
	sounds[name]->pause();
}

void SoundManager::clear(){
	for(auto& i : sounds){
		i.second;
	}
	paths.clear();
}

SoundManager::SoundManager(Game& gameRef) : game(gameRef){
}