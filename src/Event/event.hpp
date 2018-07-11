//
// Created by capi1500 on 11/07/18.
//

#ifndef COOPSHOOTER_EVENT_HPP
#define COOPSHOOTER_EVENT_HPP

#include <string>
#include <SFML/Audio.hpp>

struct Event{
	std::string object1;
	std::string object2;
	std::string what;
	sf::Vector2f position;
	Event();
	Event(std::string what, std::string object1Name = "", std::string object2Name = "", sf::Vector2f position = sf::Vector2f(0, 0));
};

#endif //COOPSHOOTER_EVENT_HPP
