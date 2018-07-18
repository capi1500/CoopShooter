//
// Created by capi1500 on 11/07/18.
//

#ifndef COOPSHOOTER_PLAYER_HPP
#define COOPSHOOTER_PLAYER_HPP

#include <src/Entity/entity.hpp>

struct PlayerProperties : public EntityProperties{
	std::string textureBase;
	std::string textureHair;
	std::string textureBoots;
	std::string textureLegs;
	std::string textureGloves;
	std::string textureBody;
	std::string textureHandRight;
	std::string textureCloak;
	std::string textureBeard;
	PlayerProperties getPlayerProperties();
	void setEntityProperties(EntityProperties entityProperites);
	
	PlayerProperties();
	PlayerProperties(EntityProperties);
};

class Player : public Entity{
	protected:
		PlayerProperties playerProperties;
		sf::Sprite ammoBar;
	public:
		PlayerProperties& getPlayerProperties();
		void pass(sf::Time elapsedTime);
		void draw();
		void drawAmmo();
		void drawEquipment();
		
		Player(Game&, PlayerProperties);
};

#endif //COOPSHOOTER_PLAYER_HPP
