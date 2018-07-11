//
// Created by capi1500 on 6/28/18.
//

#ifndef PLATFORM_SOUND_HPP
#define PLATFORM_SOUND_HPP

#include <SFML/Audio.hpp>

class Sound{
	private:
		sf::SoundBuffer buffer;
		sf::Sound sound;
	public:
		void play();
		void pause();
		void setVolume(float volume);
		void setLoop(bool loop);
		bool isPlaying();
		
		Sound(std::string path);
};

#endif //PLATFORM_SOUND_HPP
