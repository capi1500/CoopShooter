//
// Created by capi1500 on 13/07/18.
//

#ifndef COOPSHOOTER_COLLECTIBLE_HPP
#define COOPSHOOTER_COLLECTIBLE_HPP

#include <src/PhysicObject/physicObject.hpp>

struct CollectibleProperties : public PhysicObjectProperties{
	std::string what;
	sf::Time boostTime;
	int count;
	
	CollectibleProperties getCollectibleProperties();
	void setPhysicObjectProperties(PhysicObjectProperties physicObjectProperties);
	
	CollectibleProperties();
	CollectibleProperties(PhysicObjectProperties physicObjectProperties, std::string what, int counter = 0, sf::Time boostTime = sf::seconds(0));
};

class Collectible : public PhysicObject{
	protected:
		CollectibleProperties collectibleProperties;
	public:
		CollectibleProperties& getCollectibleProperties();
		
		void pass(sf::Time elapsedTime);
		bool canBeCollected();
		
		Collectible(Game& gameRef, CollectibleProperties collectibleProperties);
};

#endif //COOPSHOOTER_COLLECTIBLE_HPP
