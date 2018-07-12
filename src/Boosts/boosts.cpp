//
// Created by capi1500 on 13/07/18.
//

#include <vector>
#include "boosts.hpp"

std::map<std::string, sf::Time>& Boosts::getBoosts(){
	return boosts;
}

void Boosts::addBoost(std::string name, sf::Time time){
	boosts[name] = time;
}

void Boosts::pass(sf::Time elapsedTime){
	std::vector<std::map<std::string, sf::Time>::iterator> names;
	for(auto boost = boosts.begin(); boost != boosts.end(); boost++){
		boost->second -= elapsedTime;
		if(boost->second <= sf::microseconds(0)){
			names.push_back(boost);
		}
	}
	for(auto i : names){
		boosts.erase(i);
	}
}