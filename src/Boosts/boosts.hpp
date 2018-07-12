//
// Created by capi1500 on 13/07/18.
//

#ifndef COOPSHOOTER_BOOSTS_HPP
#define COOPSHOOTER_BOOSTS_HPP

#include <string>
#include <SFML/System/Time.hpp>
#include <map>

class Boosts{
	private:
		std::map<std::string, sf::Time> boosts;
	public:
		std::map<std::string, sf::Time>& getBoosts();
		void addBoost(std::string name, sf::Time time);
		
		void pass(sf::Time elapsedTime);
};

#endif //COOPSHOOTER_BOOSTS_HPP
