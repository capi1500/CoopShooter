//
// Created by capi1500 on 10/07/18.
//

#include "soundManager.hpp"
#include <src/Sound/sound.hpp>

void SoundManager::addSound(std::string name, std::string path){
	sounds[name] = new Sound(path);
}

void SoundManager::playSound(std::string name){
	sounds[name]->play();
}

void SoundManager::pauseSound(std::string name){
	sounds[name]->pause();
}

SoundManager::SoundManager(Game& gameRef) : game(gameRef){
}